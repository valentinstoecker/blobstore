#pragma once

#include <stdint.h>

#include <array>
#include <string>

namespace blobstore {

struct hash {
  std::array<uint8_t, 32> data;

  bool operator==(hash& other);
  bool operator!=(hash& other);

  std::string to_string();
};

}  // namespace blobstore
