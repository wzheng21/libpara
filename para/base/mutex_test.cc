#include "para/base/mutex.h"
#include "gtest/gtest.h"

namespace para {

TEST(MutexLock, MutexLock) {
  {
    Mutex mu;
    MutexLock l(&mu);
  }
}

}  // namespace para

int main(int argc, char *argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
