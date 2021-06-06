// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#pragma once

#include <atomic>
#include <condition_variable>
#include "para/base/types.h"

namespace para {

// This is a simplified lock-based implementation of std::latch (C++20)
class Latch {
 public:
  Latch() = delete;
  ~Latch() = default;
  explicit Latch(int initial_counts);

  void CountDown();
  void Wait() const;
  // Decrements the counter and blocks until it reaches zero
  void ArriveAndWait();

 private:
  mutable std::mutex m_;
  int counts_;
  mutable std::condition_variable cv_;
  NO_COPY_AND_ASSIGN(Latch);
};

}  // namespace para
