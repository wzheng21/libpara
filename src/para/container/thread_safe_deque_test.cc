// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#include "para/container/thread_safe_deque.h"
#include "para/thread/mutex.h"
#include "para/testing/testing.h"

namespace para {

TEST(ThreadSafeDeque, Basic) {
  ThreadSafeDeque<int> dq;
}

}  // namespace para
