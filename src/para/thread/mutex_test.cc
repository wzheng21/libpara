// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#include "para/thread/mutex.h"

#include "para/testing/testing.h"

namespace para {

TEST(Mutex, shared_mutex) {
  {
    shared_mutex m;
    std::lock_guard lk(m);
  }
}

}  // namespace para
