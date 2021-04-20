#include "para/thread/mutex.h"

#include "para/testing/testing.h"

namespace para {

TEST(Mutex, basic) {
#if __cplusplus >= 201703L
  {
    std::mutex m1, m2;
    shared_mutex m3;
    ScopedLock l(&m1, &m2, &m3);
  }
#else
  {
    std::mutex m;
    ScopedLock<std::mutex> l(&m);
  }
#endif
}

}  // namespace para
