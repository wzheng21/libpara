// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#pragma once

#include "para/thread/mutex.h"

namespace para {

// Simplified implementation of counting semaphore. Note that counting_semaphore
// will be available in STL from C++20
class CountingSemaphore {
 public:
  explicit CountingSemaphore(int max_avalable);
  CountingSemaphore() = delete;
  ~CountingSemaphore();

  void Acquire();
  void Release();
 private:
  std::mutex m_;
  std::condition_variable cv_;
  const int max_available_ GUARDED_BY(m_);
  int acquired_ GUARDED_BY(m_);
};

}  // namespace para
