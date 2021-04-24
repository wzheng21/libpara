// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#include "para/base/status.h"
#include "para/testing/testing.h"

namespace para {

TEST(StatusTests, TestMacros) {
  EXPECT_OKAY(Status::Okay());
  EXPECT_ERROR(Status::Error("error message"));
}

}  // namespace para
