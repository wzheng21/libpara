// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#include "para/thread/semaphore.h"

#include <vector>

#include "para/thread/thread.h"
#include "para/base/time.h"
#include "para/testing/testing.h"

namespace para {

TEST(CountingSemaphore, Basic) {
  CountingSemaphore sem(3);
  std::vector<std::thread> ts;
  
  for (int i = 0; i < 9; ++i) {
    ts.emplace_back([&sem]{
      sem.Acquire();
      LOG(INFO) << this_thread_id() << " start sleeping for a sec";
      SleepForSeconds(1.);
      sem.Release();
    });
  }

  for (std::thread& t : ts) t.join();
}

TEST(BinarySemaphore, Basic) {
  BinarySemaphore sem;
  std::vector<std::thread> ts;
  std::vector<std::thread::id> ids;
  for (int i = 0; i < 3; ++i) {
    ts.emplace_back([&sem, &ids]{
      sem.Acquire();
      LOG(INFO) << this_thread_id() << " is added";
      ids.push_back(this_thread_id());
      sem.Release();
    });
  }

  for (std::thread& t : ts) t.join();
  for (const std::thread::id tid : ids) LOG(INFO) << "ID: " << tid;
}

}  // namespace para
