#pragma once

#include <stdint.h>

#include <array>

namespace blobstore {
  
struct hash {
  std::array<uint8_t, 32> data;
};

}  // namespace blobstore
