#include "gtest/gtest.h"
#include "glog/logging.h"

#include <signal.h>
#include <sys/prctl.h>

// TODO: Improve the naive main function below
int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  testing::InitGoogleTest(&argc, argv);
  if (prctl(PR_SET_PDEATHSIG, SIGKILL) < 0) {
    PLOG(ERROR) << "prctl(PR_SET_PDEATHSIG, SIGKILL) failed";
  }
  return RUN_ALL_TESTS();
}