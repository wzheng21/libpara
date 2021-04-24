// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#pragma once

#include <ostream>
#include <string>
#include "glog/logging.h"

namespace para {

// Utility class to represent error status of function executions. We don't throw in para, we
// instead return the error to the call chain
class Status {
public:
  Status() = default;
  ~Status() = default;

  // Static function to construct a non-okay instance of Status for reporting
  static Status Error(std::string&& message);
  // Static function to construct a okay instance of Status for reporting
  static Status Okay();

  // Update current status with other status. If other status is okay, then nothing will be updated
  void Update(const Status& other);
  bool okay() const { return message_.empty(); };
  const std::string& message() const { return message_; }
  std::string ToString() const;

 private:
  std::string message_;
};

std::ostream& operator<<(std::ostream& stream, const Status& s);

}  // namespace para

// Macros easier for error checking
#define CHECK_OKAY(s)                                                  \
  do {                                                                 \
    const Status& UNIQUE_CHECK_OKAY_STATUS = (s);                      \
    CHECK(UNIQUE_CHECK_OKAY_STATUS.okay()) << UNIQUE_CHECK_OKAY_STATUS;\
  } while (false)
