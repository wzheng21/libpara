// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#include "para/thread/thread_pool.h"

#include <algorithm>

#include "glog/logging.h"

namespace para {
  
SimpleThreadPool::SimpleThreadPool(unsigned int max_n_threads) : done_(false) {
  const unsigned int pool_size = std::min(max_n_threads, std::thread::hardware_concurrency());
  for (unsigned int i = 0; i < pool_size; ++i) {
    threads_.emplace_back(&SimpleThreadPool::Work, this);
  }
  joiner_.SetThreads(&threads_);
}

SimpleThreadPool::~SimpleThreadPool() {
  done_ = true;
}

void SimpleThreadPool::Work() {
  while (!done_) {
    Closure f;
    if (closures_.TryPopFront(&f)) {
      f();
    } else {
      std::this_thread::yield();
    }
  }
}

void SimpleThreadPool::Submit(const Closure& f) {
  closures_.PushBack(f);
}

}  // namespace para
