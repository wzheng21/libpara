// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#pragma once

#include <thread>
#include <vector>

#include "para/base/types.h"

namespace para {

// Convenience functions
std::thread::id this_thread_id();

// Simple implementaion of joinable thread available in C++20.
// With this, thread will be used in RAII fashion
// see: https://en.cppreference.com/w/cpp/thread/JoinableThread
class JoinableThread {
 public:
  // member types
  using id = std::thread::id;
  using native_handle_type = std::thread::native_handle_type;

  JoinableThread() noexcept = default;
  JoinableThread(const JoinableThread&) = delete;
  JoinableThread(JoinableThread&& other) noexcept;
  template <typename Function, typename... Args>
  explicit JoinableThread(Function&& f, Args&&... args);
  ~JoinableThread();

  // operators
  JoinableThread& operator=(JoinableThread&& other) noexcept;
  // observers
  bool Joinable();
  id get_id() const noexcept;
  static unsigned int hardware_concurrency() noexcept;
  // operations
  void Join();
  void Detach();
  void Swap(JoinableThread& other) noexcept;

 private:
  std::thread t_;
};  // JoinableThread

// Inspired by join_threads on Page 275 of C++ Concurrency in Action (2nd edition)
  // Note that threads_ must be initialized before the joiner
class ThreadJoiner {
 public:
  ThreadJoiner() = delete;
  explicit ThreadJoiner(std::vector<std::thread>* threads);
  ~ThreadJoiner();

 private:
  std::vector<std::thread>* threads_ = nullptr;
  NO_COPY_AND_ASSIGN(ThreadJoiner);
};

}  // namespace para

#include "para/thread/thread-impl.h"
