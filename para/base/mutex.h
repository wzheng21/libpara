// Copyright 2021
// Authors: Weixiong (Victor) Zheng

#pragma once

#include <mutex>
#include <shared_mutex>

// Useful macros to provide thread-safety annotation
#define GUARDED_BY(x) __attribute__((guarded_by(x)))

namespace para {

// Aliases
using Mutex = std::mutex;

#if __cplusplus >= 201703L
using SharedMutex = std::shared_mutex;
#else
using SharedMutex = std::shared_timed_mutex;
#endif

#if __cplusplus >= 201703L
template <typename... MutexTypes>
using MutexLock = std::scoped_lock<MutexTypes...>;
#else
template <typename MutexType>
using MutexLock = std::lock_guard<MutexType>;
#endif

// Class template to wrap up both
template <template <typename> class LockType, typename MutexType>
class GenericLock {
 public:
  GenericLock() = default;
};

template <typename MutexType>
using UniqueLock = GenericLock<std::unique_lock, MutexType>;
template <typename MutexType>
using SharedLock = GenericLock<std::shared_lock, MutexType>;

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