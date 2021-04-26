// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#pragma once

#include <mutex>
#include <shared_mutex>

#include "para/base/types.h"

// Useful macros to provide thread-safety annotation in case of clang
// see http://clang.llvm.org/docs/ThreadSafetyAnalysis.html
#ifdef __clang__
#define GUARDED_BY(x) __attribute__((guarded_by(x)))
#else
// No effect for non-clang compiler
#define GUARDED_BY(x)
#endif

// Scoped lock for two mutexes
#if __cplusplus >= 201703L
#define SCOPED_LOCK_2(UNIQUE_MUTEX1, UNIQUE_MUTEX2)                   \
  do {                                                                \
    std::scoped_lock SCOPED_LOCK2_LOCK(UNIQUE_MUTEX1, UNIQUE_MUTEX2);\
  } while (false)
#else
#define SCOPED_LOCK_2(UNIQUE_MUTEX1, UNIQUE_MUTEX2)                    \
  do {                                                                 \
    std::lock(UNIQUE_MUTEX1, UNIQUE_MUTEX2);                           \
    std::lock_guard SCOPED_LOCK2_LOCK1(UNIQUE_MUTEX1, std::adopt_lock);\
    std::lock_guard SCOPED_LOCK2_LOCK2(UNIQUE_MUTEX2, std::adopt_lock);\
  } while (false)
#endif

namespace para {

#if __cplusplus >= 201703L
using shared_mutex = std::shared_mutex;
#else
using shared_mutex = std::shared_timed_mutex;
#endif

// RAII wrapper to std::call_once
class CallOnce {
 public:
  CallOnce() = default;
  template <typename Callable, typename... Args>
  void Init(Callable&& f, Args&&... args) {
    std::call_once(flag_, f(std::forward<Args>(args)...));
  }
 private:
  std::once_flag flag_;
};

};  // namespace para
