// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#include "para/base/status.h"

#include <utility>

namespace para {

// static
Status Status::Error(std::string&& message) {
  Status s;
  s.message_ = std::forward<std::string>(message);
  return s;
}

// static
Status Status::Okay() {
  return Status();
}

void Status::Update(const Status& other) {
  if (other.okay()) return;
  message_ += " // ";
  message_ += other.ToString();
}

std::string Status::ToString() const {
  return message_.empty() ? "OK" : ("FAIL: " + message_);
}

std::ostream& operator<<(std::ostream& stream, const Status& s) {
  stream << s.ToString();
  return stream;
}
}  // namespace para
