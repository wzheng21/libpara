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
ThreadSafeDeque<T>& ThreadSafeDeque<T>::operator=(ThreadSafeDeque&& other) {
  SCOPED_LOCK_2(m_, other.m_);
  dq_ = std::move(other.dq_);
  return *this;
}

// Operations
template <typename T>
bool ThreadSafeDeque<T>::TryPopFront(T* val) {
  std::lock_guard<std::mutex> lk(m_);
  if (dq_.empty()) return false;
  *val = dq_.front();
  dq_.pop_front();
  return true;
}

template <typename T>
bool ThreadSafeDeque<T>::TryPopBack(T* val) {
  std::lock_guard<std::mutex> lk(m_);
  if (dq_.empty()) return false;
  *val = dq_.back();
  dq_.pop_back();
  return true;
}

template <typename T>
void ThreadSafeDeque<T>::PushFront(T&& val) {
  std::lock_guard<std::mutex> lk(m_);
  dq_.push_front(std::forward<T>(val));
}

template <typename T>
void ThreadSafeDeque<T>::PushBack(T&& val) {
  std::lock_guard<std::mutex> lk(m_);
  dq_.push_back(std::forward<T>(val));
}

template <typename T>
void ThreadSafeDeque<T>::Swap(ThreadSafeDeque* other) {
  SCOPED_LOCK_2(m_, other->m_);
  dq_.swap(other->dq_);
}

template <typename T>
bool ThreadSafeDeque<T>::Empty() const {
  std::lock_guard<std::mutex> lk(m_);
  return dq_.empty();
}

}  // namespace para
