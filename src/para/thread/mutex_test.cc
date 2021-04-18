#include "para/thread/mutex.h"

#include "gtest/gtest.h"

namespace para {

TEST(MutexLock, MutexLock) {
  {
    Mutex mu;
    MutexLock l(&mu);
  }

#if __cplusplus >= 201703L
  {
    Mutex m1, m2;
    SharedMutex m3;
    MutexLock l(&m1, &m2, &m3);
    std::cout << "testing scoped lock" << std::endl;
  }
#endif

}

}  // namespace para
