// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#include <chrono>

#include "para/thread/latch.h"
#include "para/thread/thread.h"

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
  jthread t1(f);
  jthread t2(f);
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(500ms);
  LOG(INFO) << "Decrement latch 1";
  lt.CountDown();
  std::this_thread::sleep_for(500ms);
  LOG(INFO) << "Decrement latch 2";
  lt.CountDown();
}

}  // namespace para
