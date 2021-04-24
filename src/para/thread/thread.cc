#include "para/thread/thread.h"

namespace para {

// Constructors
jthread::jthread(jthread&& other) noexcept : t_(std::move(other.t_)) {}

template <typename Function, typename... Args>
jthread::jthread(Function&& f, Args&&... args)
    : t_(std::forward<Function>(f), std::forward<Args>(args)...) {}

// move operator
jthread& jthread::operator=(jthread&& other) noexcept {
  // from c++ concurrency in action page 29: check joinability before real operation
  if (joinable()) join();
  t_ = std::move(other.t_);
  return *this;
}

// destructor: join if possible
jthread::~jthread() {
  if (joinable()) join();
}

// observers
bool jthread::joinable() {
  return t_.joinable();
}

jthread::id jthread::get_id() const noexcept {
  return t_.get_id();
}

// static
unsigned int jthread::hardware_concurrency() noexcept {
  return std::thread::hardware_concurrency();
}

// operations
void jthread::join() {
  if (joinable()) t_.join();
}

void jthread::detach() {
  t_.detach();
}

void jthread::swap(jthread& other) noexcept {
  t_.swap(other.t_);
}
}  // namespace para