// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#pragma once

#include <cmath>
#include <string>
#include <vector>

#include "para/base/status.h"
#include <unistd.h>

namespace para {

// Class to manage environment building and retrieving
class EnvVars {
 public:
  EnvVars() = default;

  // When the variable is like a flag, add it directly
  void AddVar(std::string&& var);

  // Add a environment variable pair (key-value)
  template <typename VarType>
  void AddVar(const std::string& env_name, const VarType& var) {
    AddVar(env_name + "=" + std::to_string(var));
  }

  std::vector<const char*> c_env_vars() const;

 private:
  std::vector<std::string> vars_;
};

struct SubprocessInput {
  std::vector<std::string> cmd;
  EnvVars envs;
  // Will only be consumed by subprocess call with timeout functionality enabled.
  // see timed_subprocess.h
  double timeout_s = NAN;
};

struct SubprocessState {
  pid_t pid;
};

Status StartSubprocess(const SubprocessInput& in, SubprocessState* state);
// Given a pid, wait for it until finished
Status WaitSubprocess(pid_t pid);
}  // namespace para
