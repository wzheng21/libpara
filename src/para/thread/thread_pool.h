// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#include <atomic>
#include <functional>
#include <thread>
#include <vector>

#include "para/thread/thread.h"
#include "para/container/thread_safe_deque.h"

namespace para {

using Closure = std::function<void()>;

class SimpleThreadPool {
 public:
  SimpleThreadPool(unsigned int max_n_threads);
  SimpleThreadPool() = delete;
  ~SimpleThreadPool();

  void Submit(const Closure& f);

 private:
  std::vector<std::thread> threads_;
  ThreadJoiner joiner_;
  ThreadSafeDeque<Closure> closures_;

  std::atomic<bool> done_;

  void Work();
};

}  // namespace para
