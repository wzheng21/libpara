// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#include "para/container/thread_safe_deque.h"

#include <atomic>

#include "para/thread/mutex.h"
#include "para/thread/thread.h"
#include "para/testing/testing.h"

namespace para {

TEST(ThreadSafeDeque, Basic) {
  ThreadSafeDeque<int> dq;
  std::atomic<int> num_true{0};
  std::atomic<int> tot{0};
  const auto t = [&dq, &tot, &num_true](int start) {
    for (int i = start + 1; i < start + 6; ++i) {
      dq.PushBack(i);
    }
    while (!dq.Empty()) {
      int r;
      const bool popped = dq.TryPopBack(&r);
      if (popped) {
        ++num_true;
        tot += r;
      }
    }
  };
  {
    jthread t1(t, 0);
    jthread t2(t, 5);
  }
  ASSERT_EQ(num_true, 10);
  ASSERT_EQ(tot, 55);
}

}  // namespace para
