#pragma once

#include <stdint.h>

#include <string>
#include <array>

namespace blobstore {
  
struct hash {
  std::array<uint8_t, 32> data;

  std::string to_string();
};

}  // namespace blobstore
