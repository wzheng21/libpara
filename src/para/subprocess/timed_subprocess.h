// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#include "para/base/status.h"
#include "para/subprocess/subprocess.h"

namespace para {

// Run subprocess call to finish or timeout, whichever comes first
Status RunSubprocessOrTimeout(const SubprocessInput& in);

}  // namespace para
