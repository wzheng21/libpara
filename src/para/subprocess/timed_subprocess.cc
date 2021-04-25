// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#include "para/subprocess/timed_subprocess.h"

#include <cmath>
#include <chrono>
#include <future>

#include <signal.h>

namespace para {

Status RunSubprocessOrTimeout(const SubprocessInput& in) {
  // This is a very naive implementation. The logic is here:
  // 1. Start a subprocess
  // 2. Start a future which inside waits the subprocess
  // 3. Wait the future for specified time
  // 4. Check futures_status, if ready, then return. If not ready, step 5
  // 5. Terminate the subprocess and then return
  
  // Step 0 validation
  if (std::isnan(in.timeout_s)) {
    return Status::Error("timeout_s not specified");
  } else if (in.timeout_s <= 0) {
    return Status::Error("timeout_s must be positive");
  }
  // Step 1
  SubprocessState o;
  Status s = StartSubprocess(in, &o);
  if (!s.okay()) return s;
  // Step 2
  std::future<Status> f = std::async(std::launch::async, [&o]{
    LOG(ERROR) << "Waiting for pid: " << o.pid;
    return WaitSubprocess(o.pid);
  });
  // Step 3
  // TODO: use double for duration instead of relying on using integers with smaller units
  const std::future_status fs = f.wait_for(std::chrono::milliseconds(1000 * static_cast<int64_t>(in.timeout_s)));
  // Step 4/5
  switch (fs) {
    case std::future_status::deferred:
      // shouldn't reach here
      s.Update(Status::Error("Unknown deferred function call in future"));
      break;
    case std::future_status::timeout:
      LOG(ERROR) << "Subprocess timeout";
      kill(o.pid, SIGKILL);
      s. Update(Status::Error("cmd timeout"));
      break;
    case std::future_status::ready:
      s.Update(f.get());
      break;
  }
  return s;
}

}  // namespace para
