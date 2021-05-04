// Copyright (c) 2021
// Authors: Weixiong (Victor) Zheng
// All rights reserved
//
// SPDX-License-Identifier: MIT

#include <chrono>

namespace para {

using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
using Duration = std::chrono::duration<double>;

inline Duration Seconds(double s) {
  return Duration(s);
}

// Revert a duration (seconds) to number of ticks
inline double ToSeconds(Duration d) {
  return d.count();
}

// Sleep for seconds for this thread
void SleepForSeconds(double s);
// TODO: add SleepUntil when needed

}  // namespace para
