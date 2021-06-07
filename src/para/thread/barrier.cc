// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#include "para/thread/barrier.h"

#include "glog/logging.h"

namespace para {

Barrier::Barrier(int initial_counts) : max_counts_(initial_counts), phase_not_arrived_(initial_counts), finished_waiting_(0) {
  CHECK_GT(initial_counts, 0);
}
Barrier::~Barrier() {}

void Barrier::Arrive() {
  std::lock_guard<std::mutex> lk(m_);
  --phase_not_arrived_;
  cv_.notify_all();
}

void Barrier::Wait() {
  std::unique_lock<std::mutex> lk(m_);
  cv_.wait(lk, [this]() {
    return phase_not_arrived_ == 0;
  });
  ++finished_waiting_;
  lk.unlock();
  {
    std::lock_guard<std::mutex> l(m_);
    if (finished_waiting_ == max_counts_) {
      phase_not_arrived_ = max_counts_;
      finished_waiting_ = 0;
    }
  }
}

void Barrier::ArriveAndWait() {
  Arrive();
  Wait();
}

void Barrier::ArriveAndDrop() {
  {
    std::lock_guard<std::mutex> lk(m_);
    --max_counts_;
  }
  Arrive();
}

}  // namespace para
