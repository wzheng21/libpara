// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#pragma once

#include <condition_variable>
#include <deque>
#include <mutex>

#include "para/thread/mutex.h"

namespace para {

// Lock-based thread-safety deque that provides thread-safe read-write APIs
// This should be efficient only for trivially constructible types
template <typename T>
class ThreadSafeDeque {
 public:
  ThreadSafeDeque() = default;
  ~ThreadSafeDeque() {}
  ThreadSafeDeque(const ThreadSafeDeque& other);
  ThreadSafeDeque(ThreadSafeDeque&& other);

  ThreadSafeDeque& operator=(const ThreadSafeDeque& othre);
  ThreadSafeDeque& operator=(ThreadSafeDeque&& othre);

  bool TryPopFront(T* val);
  bool TryPopBack(T* val);
  void PushBack(T&& val);
  void PushFront(T&& val);
  void PushBack(const T& val);
  void PushFront(const T& val);
  void Swap(ThreadSafeDeque* other);
  bool Empty() const;
  // The following two APIs will try to pop. If the deque is empty, both will
  // wait until internal deque is not empty to pop
  void WaitAndPopFront(T* val);
  void WaitAndPopBack(T* val);

 private:
  mutable std::mutex m_;
  std::deque<T> dq_ GUARDED_BY(m_);
  std::condition_variable cv_;
};

}  // namespace para

#include "para/container/thread_safe_deque-impl.h"
