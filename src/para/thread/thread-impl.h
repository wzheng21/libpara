#pragma once

#include "para/thread/thread.h"

namespace para {

#if __cplusplus <= 201703L

template <typename Function, typename... Args>
jthread::jthread(Function&& f, Args&&... args)
    : t_(std::forward<Function>(f), std::forward<Args>(args)...) {}

#endif

}  // namespace para
