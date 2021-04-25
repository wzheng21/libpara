// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#include "para/subprocess/subprocess.h"
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


}  // namespace para
