#pragma once

#include "para/thread/mutex.h"

namespace para {

template <typename... MutexTypes>
ScopedLock<MutexTypes...>::ScopedLock(MutexTypes*... m)
    : lk_(*m...) {}

}  // namespace para
