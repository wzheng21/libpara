// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#pragma once

#include <atomic>
#include <condition_variable>
#include "para/base/types.h"
#include "para/thread/mutex.h"

namespace para {

class Barrier {
 public:
  explicit Barrier(int initial_counts);
  ~Barrier();
  Barrier() = delete;

  void Arrive();
  // Blocking until counts_ decremented to zero, then reset
  void Wait();
  void ArriveAndWait();
  void ArriveAndDrop();

 private:
  std::condition_variable cv_;
  std::mutex m_;
  int max_counts_ GUARDED_BY(m_);
  int phase_not_arrived_ GUARDED_BY(m_);
  int finished_waiting_ GUARDED_BY(m_);

  NO_COPY_AND_ASSIGN(Barrier);
};

}  // namespace para
