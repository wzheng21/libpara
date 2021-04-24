// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#pragma once

#include <thread>

namespace para {

#if __cplusplus > 201703L
using jthread = std::jthread;
#else

// Simple implementaion of joinable thread available in C++20.
// With this, thread will be used in RAII fashion
// see: https://en.cppreference.com/w/cpp/thread/jthread
class jthread {
 public:
  // member types
  using id = std::thread::id;
  using native_handle_type = std::thread::native_handle_type;

  jthread() noexcept = default;
  jthread(const jthread&) = delete;
  jthread(jthread&& other) noexcept;
  template <typename Function, typename... Args>
  explicit jthread(Function&& f, Args&&... args);
  ~jthread();

  // operators
  jthread& operator=(jthread&& other) noexcept;
  // observers
  bool joinable();
  id get_id() const noexcept;
  static unsigned int hardware_concurrency() noexcept;
  // operations
  void join();
  void detach();
  void swap(jthread& other) noexcept;

 private:
  std::thread t_;
};  // jthread

#endif
}  // namespace para

#include "para/thread/thread-impl.h"
