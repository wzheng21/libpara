// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#include "para/base/time.h"

#include <thread>

#include "glog/logging.h"

namespace para {

void SleepForSeconds(double s) {
  if (s <= 0) {
    LOG(ERROR) << "Sleeping time is negative: " << s;
    return;
  }
  std::this_thread::sleep_for(Duration(s));
}

}  // namespace para
