// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#include "para/thread/thread.h"

#include "glog/logging.h"

namespace para {

std::thread::id this_thread_id() { return std::this_thread::get_id(); }

// Constructors
JoinableThread::JoinableThread(JoinableThread&& other) noexcept : t_(std::move(other.t_)) {}

// move operator
JoinableThread& JoinableThread::operator=(JoinableThread&& other) noexcept {
  // from c++ concurrency in action page 29: check joinability before real operation
  if (Joinable()) Join();
  t_ = std::move(other.t_);
  return *this;
}

// destructor: join if possible
JoinableThread::~JoinableThread() {
  if (Joinable()) Join();
}

// observers
bool JoinableThread::Joinable() {
  return t_.joinable();
}

JoinableThread::id JoinableThread::get_id() const noexcept {
  return t_.get_id();
}

// static
unsigned int JoinableThread::hardware_concurrency() noexcept {
  return std::thread::hardware_concurrency();
}

// operations
void JoinableThread::Join() {
  if (Joinable()) t_.join();
}

void JoinableThread::Detach() {
  t_.detach();
}

void JoinableThread::Swap(JoinableThread& other) noexcept {
  t_.swap(other.t_);
}

ThreadJoiner::ThreadJoiner(std::vector<std::thread>* threads) : threads_(threads) {
  CHECK(threads != nullptr);
}

ThreadJoiner::~ThreadJoiner() {
  for (std::thread& t : *threads_) {
    if (t.joinable()) t.join();
  }
}

void ThreadJoiner::SetThreads(std::vector<std::thread>* threads) {
  CHECK(threads != nullptr);
  threads_ = threads;
}
}  // namespace para
