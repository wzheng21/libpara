// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#pragma once

#define NO_COPY_AND_ASSIGN(ClassName)              \
    ClassName(const ClassName&) = delete;          \
    ClassName& operator=(const ClassName&) = delete
