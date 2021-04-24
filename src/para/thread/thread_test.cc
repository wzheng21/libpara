#include "para/thread/thread.h"

#include "para/testing/testing.h"

namespace para {

TEST(jthread, Basic) {
  jthread t1([](){ 
    LOG(INFO) << "Start to sleep ";
    using namespace std::chrono_literals;
    std::this_thread::sleep_for(1s);
    LOG(INFO) << "Wake up"; 
  });
  LOG(INFO) << "jthread t1 id: " << t1.get_id();
  jthread t2 = std::move(t1);
  LOG(INFO) << "jthread t2 id: " << t2.get_id();
}

}  // namespace para