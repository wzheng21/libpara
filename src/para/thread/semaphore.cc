// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#include "para/thread/semaphore.h"
#include "para/thread/thread.h"

#include "glog/logging.h"

namespace para {

CountingSemaphore::CountingSemaphore(int max_available) 
    : max_available_(max_available), acquired_(0) {
  CHECK_GT(max_available, 0);
}
CountingSemaphore::~CountingSemaphore() {}

void CountingSemaphore::Acquire() {
  std::unique_lock<std::mutex> lk(m_);
  LOG(INFO) << "Thread ID: " << this_thread_id(); 
  LOG(INFO) << "Already acquired: " << acquired_ << ", max avail: " << max_available_;
  cv_.wait(lk, [this]() { return acquired_ < max_available_; });
  LOG(INFO) << "Thread ID: " << this_thread_id() << "acquired";
  ++acquired_;
}

void CountingSemaphore::Release() {
  std::unique_lock<std::mutex> lk(m_);
  if (acquired_ > 0) {
    LOG(INFO) << "Releasing at thread: " << this_thread_id();
    --acquired_;
    cv_.notify_all();
  }
}

}  // namespace para
