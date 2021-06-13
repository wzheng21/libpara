// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#include "para/thread/thread_pool.h"
#include "para/base/time.h"
#include "para/testing/testing.h"

#include "glog/logging.h"

namespace para {

TEST(SimpleThreadPool, Basic) {
  SimpleThreadPool pool(2);
  for (int i = 1; i <= 5; ++i) {
    pool.Submit([i](){
      LOG(INFO) << i << " second sleeping, Thread " << i;
      SleepForSeconds(1.);
      LOG(INFO) << "Wake up, Thread " << i;
    });
  }
}

}  // namespace para
