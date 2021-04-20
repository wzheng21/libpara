#include "gtest/gtest.h"
#include "glog/logging.h"

// TODO: Improve the naive main function below
int main(int argc, char *argv[]) {
  google::InitGoogleLogging(argv[0]);
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}