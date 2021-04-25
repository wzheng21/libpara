// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#include "para/subprocess/subprocess.h"

#include <sys/wait.h>
#include <sys/types.h>

namespace para {

void EnvVars::AddVar(std::string&& var) {
  vars_.push_back(std::forward<std::string>(var));
}

std::vector<const char*> EnvVars::c_env_vars() const {
  std::vector<const char*> r;
  r.push_back(nullptr);
  for (const std::string& v : vars_) r.push_back(v.c_str());
  return r;
}

// See https://linux.die.net/man/2/execve for calling subprocess
// Watch https://www.youtube.com/watch?v=Mqb2dVRe0uo for pipe handling
// TODO: Could be nice to have a helper class to handle pipe in RAII way
Status StartSubprocess(const SubprocessInput& in, SubprocessState* state) {
  // File descriptors needs to be created before forking
  int file_descriptors[2];
  if (pipe(file_descriptors) < 0) {
    return Status::Error("Failed to opening pipe");
  }
  const pid_t child = fork();
  Status s;
  if (child < 0) {
    s.Update(Status::Error("fork() failed"));
    return s;
  }
  if (child == 0) {
    std::vector<const char*> c_cmd;
    for (const std::string& arg : in.cmd) c_cmd.push_back(arg.c_str());
    const std::vector<const char*> c_env_vars = in.envs.c_env_vars();
    execve(c_cmd[0], const_cast<char* const*>(c_cmd.data()), const_cast<char* const*>(c_env_vars.data()));    
    // Shouldn't reach the section below if execve succeeds.
    // close the read fd
    close(file_descriptors[0]);
    // get the error message
    char message[1000];
    snprintf(message, sizeof(message), "Exec failed %s: %s\n", c_cmd[0], strerror(errno));
    // write to the pipe and exit
    ssize_t unused = write(file_descriptors[1], message, strlen(message));
    close(file_descriptors[1]);
    _exit(EXIT_FAILURE);
  } else {
    state->pid = child;
    // close write file descriptor
    close(file_descriptors[1]);
    char in_buffer[1000];
    ssize_t n = read(file_descriptors[0], in_buffer, sizeof(in_buffer));
    if (n > 0) {
      std::string err_message(in_buffer, n);
      LOG(ERROR) << "Child process error message: " << err_message;
      s.Update(Status::Error(std::move(err_message)));
    }
    close(file_descriptors[0]);
  }
  return s;
}

Status WaitSubprocess(pid_t pid) {
  pid_t p;
  int proc_status;
  do {
    p = waitpid(pid, &proc_status, 0);
  } while (p < 0 && errno == EINTR);
  if (p < 0) {
    // TODO: add errno interpretation
    return Status::Error("waitpid failed");
  }
  Status s;
  if (proc_status != 0) {
    s.Update(Status::Error("Process failed with status: " + std::to_string(proc_status)));
  }
  return s;
}

}  // namespace para