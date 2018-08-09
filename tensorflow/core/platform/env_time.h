/* Copyright 2015 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#ifndef TENSORFLOW_CORE_PLATFORM_ENV_TIME_H_
#define TENSORFLOW_CORE_PLATFORM_ENV_TIME_H_

#include <stdint.h>

#include "tensorflow/core/platform/types.h"
#include <thread>
#include <sstream>
#include <iostream>

namespace tensorflow {

/// \brief An interface used by the tensorflow implementation to
/// access timer related operations.
class EnvTime {
 public:
  EnvTime();
  virtual ~EnvTime() = default;

  /// \brief Returns a default impl suitable for the current operating
  /// system.
  ///
  /// The result of Default() belongs to this library and must never be deleted.
  static EnvTime* Default();

  /// \brief Returns the number of micro-seconds since the Unix epoch.
  virtual uint64 NowMicros() = 0;

  /// \brief Returns the number of seconds since the Unix epoch.
  virtual uint64 NowSeconds() { return NowMicros() / 1000000L; }

  virtual void PrintTime(
      std::string prof_name,
      uint64 ts,
      uint64 time,
      bool print_tid = false,
      std::string extra = "") {
    std::stringstream ss;
    ss << "tf-profile, prof_name " << prof_name;
    if (print_tid) {
      std::thread::id id = std::this_thread::get_id();
      ss << ", id " << id;
    }
    ss << ", ts " << ts << ", time " << time;
    if (extra != "") {
      ss << ", " << extra;
    }
    ss << std::endl;
    std::cerr << ss.str();
  }
};

}  // namespace tensorflow

#endif  // TENSORFLOW_CORE_PLATFORM_ENV_TIME_H_
