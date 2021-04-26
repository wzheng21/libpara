// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#pragma once

#include "para/container/thread_safe_deque.h"

namespace para {

// Constructors
template <typename T>
ThreadSafeDeque<T>::ThreadSafeDeque(const ThreadSafeDeque& other) {
  SCOPED_LOCK_2(m_, other.m_);
  dq_ = other.dq_;
}

template <typename T>
ThreadSafeDeque<T>::ThreadSafeDeque(ThreadSafeDeque&& other) {
  SCOPED_LOCK_2(m_, other.m_);
  dq_ = std::move(other.dq_);
}

// Operators
template <typename T>
ThreadSafeDeque<T>& ThreadSafeDeque<T>::operator=(const ThreadSafeDeque& other) {
  SCOPED_LOCK_2(m_, other.m_);
  dq_ = other.dq_;
  return *this;
}

template <typename T>
ThreadSafeDeque<T>& ThreadSafeDeque<T>::operator=(const ThreadSafeDeque& other) {
  SCOPED_LOCK_2(m_, other.m_);
  dq_ = std::move(other.dq_);
  return *this;
}

// Operations

}  // namespace para
