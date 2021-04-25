// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#include "para/subprocess/subprocess.h"
#include "para/subprocess/timed_subprocess.h"
#include "para/testing/testing.h"

namespace para {

TEST(Subprocess, StartAndWait) {
  SubprocessInput in;
  in.cmd = {"/usr/bin/echo", "happy"};
  SubprocessState o;
  ASSERT_OKAY(StartSubprocess(in, &o));
  ASSERT_OKAY(WaitSubprocess(o.pid));
}

TEST(Subprocess, NoExistingBinCall) {
  SubprocessInput in;
  in.cmd = {"/usr/bin/foo"};
  SubprocessState o;
  Status s = StartSubprocess(in, &o);
  ASSERT_ERROR(s);
  ASSERT_SUBSTR(s.message(), " Exec failed /usr/bin/foo: No such file or directory");
}

TEST(Subprocess, Timeout) {
  SubprocessInput in;
  in.cmd = {"/usr/bin/cat", "/etc/*"};
  in.timeout_s = .002;
  Status s = RunSubprocessOrTimeout(in);
  ASSERT_ERROR(s);
  ASSERT_SUBSTR(s.message(), "timeout");

  // Not timeout error
  in.timeout_s = 1;
  Status s2 = RunSubprocessOrTimeout(in);
  ASSERT_ERROR(s2);
  // TODO: pass the original error message to the top of the callchain
  ASSERT_SUBSTR(s2.message(), "Process failed with status: 256");
}

}  // namespace para
