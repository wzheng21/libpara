#include "para/thread/mutex.h"

#include "para/testing/testing.h"

namespace para {

TEST(MutexLock, MutexLock) {
  {
    Mutex mu;
    MutexLock<Mutex> l(&mu);
  }

#if __cplusplus >= 201703L
  {
    LOG(INFO) << "testing scoped lock in 17+ standard";
    Mutex m1, m2;
    SharedMutex m3;
    MutexLock l(&m1, &m2, &m3);
  }
#endif

}

}  // namespace para
