#include "para/base/status.h"

namespace para {

Status::Status() {}
Status::~Status() {}

void Status::Update(const Status& other) {
  message_ += " // ";
  message_ += other.message();
}
}  // namespace para