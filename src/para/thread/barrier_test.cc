// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#include "para/thread/barrier.h"

#include "para/thread/thread.h"
#include "para/base/time.h"
#include "para/testing/testing.h"

namespace para {

TEST(Barrier, Basic) {
  Barrier sync_point(3);
  std::vector<JoinableThread> ts;
  for (int i = 1; i <= 3; ++i) {
    ts.emplace_back([i, &sync_point]() {
      LOG(INFO) << "Thread " << i << " sleeping for seconds: " << i;
      SleepForSeconds(static_cast<double>(i));
      LOG(INFO) << "Thread " << i << " waiting";
      sync_point.ArriveAndWait();
      LOG(INFO) << "Thread " << i << " sleeping for another seconds: " << i;
      SleepForSeconds(static_cast<double>(i));
      LOG(INFO) << "Thread " << i << " waiting";
      sync_point.ArriveAndWait();
      LOG(INFO) << "Thread " << i << " done";      
    });
  }
}

TEST(Barrier, Drop) {
  Barrier sync_point(3);
  std::vector<JoinableThread> ts;
  for (int i = 1; i <= 2; ++i) {
    ts.emplace_back([i, &sync_point]() {
      LOG(INFO) << "Thread " << i << " sleeping for seconds: " << i;
      SleepForSeconds(static_cast<double>(i));
      LOG(INFO) << "Thread " << i << " waiting";
      sync_point.ArriveAndWait();
      LOG(INFO) << "Thread " << i << " sleeping for another seconds: " << i;
      SleepForSeconds(static_cast<double>(i));
      LOG(INFO) << "Thread " << i << " waiting";
      sync_point.ArriveAndWait();
      LOG(INFO) << "Thread " << i << " done";      
    });
  }
  ts.emplace_back([&sync_point]() {
      LOG(INFO) << "Thread 3 sleeping for seconds: " << 3;
      SleepForSeconds(3.0);
      LOG(INFO) << "Thread 3 dropping";
      sync_point.ArriveAndDrop();
  });
}

}  // namespace para
