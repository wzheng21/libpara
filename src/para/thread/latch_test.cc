// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#include <chrono>

#include "para/thread/latch.h"
#include "para/thread/thread.h"
#include "para/base/time.h"
#include "para/testing/testing.h"

namespace para {

TEST(Latch, Basic) {
  Latch lt(2);
  const auto f = [&lt](){
    LOG(INFO) << "Thread ID: " << std::this_thread::get_id();
    LOG(INFO) << "Wait ...";
    lt.Wait();
    LOG(INFO) << "Wait is over at " << std::this_thread::get_id();
  };
  JoinableThread t1(f);
  JoinableThread t2(f);
  using namespace std::chrono_literals;
  SleepForSeconds(0.5);
  LOG(INFO) << "Decrement latch 1";
  lt.CountDown();
  SleepForSeconds(0.5);
  LOG(INFO) << "Decrement latch 2";
  lt.CountDown();
}

TEST(Latch, WaitInOneThread) {
  Latch lt(2);
  const auto f = [&lt]() {
    LOG(INFO) << "Thread ID: " << this_thread_id() << ", sleep for a second";
    SleepForSeconds(1.);
    lt.CountDown();
  };
  JoinableThread t1(f);
  JoinableThread t2(f);
  LOG(INFO) << "Thread ID: " << this_thread_id() << ", waiting";
  lt.Wait();
  LOG(INFO) << "Thread ID: " << this_thread_id() << ", waiting is done";
}

TEST(Latch, ArriveAndWait) {
  Latch lt(3);
  std::vector<JoinableThread> ts;
  for (int i = 1; i <=3; ++i) {
    ts.emplace_back([&lt, i]() {
      LOG(INFO) << "Thread ID: " << this_thread_id() << ", start to sleep for seconds: " << i;
      SleepForSeconds(static_cast<double>(i));
      LOG(INFO) << "Thread ID: " << this_thread_id() << ", woke up and now wait";
      lt.ArriveAndWait();
      LOG(INFO) << "Thread ID: " << this_thread_id() << ", waiting is done";
    });
  }
}

}  // namespace para
