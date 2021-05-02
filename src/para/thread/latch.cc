// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#include "para/thread/latch.h"

#include <mutex>

#include "glog/logging.h"

namespace para {

Latch::Latch(int initial_counts) : counts_(initial_counts) {
  CHECK_GT(initial_counts, 0) << "Latch counts must be positive";
}
  
void Latch::CountDown() {
  std::lock_guard<std::mutex> lk(m_);
  CHECK_GT(counts_, 0) << "When calling CountDown, counts_ must be positive";
  --counts_;
  cv_.notify_all();
}

void Latch::Wait() const {
  std::unique_lock<std::mutex> lk(m_);
  cv_.wait(lk, [this](){ return counts_ == 0; });
}

}  // namespace para
