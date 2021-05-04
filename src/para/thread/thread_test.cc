// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#include "para/thread/thread.h"
#include "para/base/time.h"

#include "para/testing/testing.h"

namespace para {

TEST(JoinableThread, Basic) {
  JoinableThread t1([](){ 
    LOG(INFO) << "Start to sleep ";
    SleepForSeconds(1.0);
    LOG(INFO) << "Wake up"; 
  });
  LOG(INFO) << "JoinableThread t1 id: " << t1.get_id();
  JoinableThread t2 = std::move(t1);
  LOG(INFO) << "JoinableThread t2 id: " << t2.get_id();
}

}  // namespace para
