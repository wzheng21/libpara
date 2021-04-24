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
