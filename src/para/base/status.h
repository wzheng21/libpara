#pragma once

#include <string>

namespace para {

// Utility class to represent error status of function executions. We don't throw in para, we
// instead return the error to the call chain
class Status {
public:
  Status();
  ~Status();

  // Update current status with other status
  void Update(const Status& other);
  bool Ok() const { return message_.empty(); };
  const std::string& message() const { return message_; }

 private:
  std::string message_;

};

}  // namespace para