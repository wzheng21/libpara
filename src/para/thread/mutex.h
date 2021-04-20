// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng

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

// A wrapper class with the eventual goal of enabling scoped_lock in C++2014
// TODO: Add support for scoped_lock for <C++17
template <typename... MutexTypes>
class ScopedLock {
 public:
  ScopedLock() = delete;
  explicit ScopedLock(MutexTypes*... m);
  ~ScopedLock() {}
  NO_COPY_AND_ASSIGN(ScopedLock);
 private:
#if __cplusplus >= 201703L
  std::scoped_lock<MutexTypes...> lk_;
#else
  static_assert(sizeof...(MutexTypes) == 1);
  std::lock_guard<MutexTypes...> lk_;
#endif
};

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

#include "para/thread/mutex-impl.h"
