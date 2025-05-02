#pragma once

#include <openssl/evp.h>
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

struct hasher {
  EVP_MD_CTX* ctx;

 public:
  hasher();
  ~hasher();

  // delete copy constructor and assignment operator
  hasher(const hasher&) = delete;
  hasher& operator=(const hasher&) = delete;

  // delete move constructor and assignment operator
  hasher(hasher&&) = delete;
  hasher& operator=(hasher&&) = delete;

  void init();
  void write(const char* data, size_t len);
  hash finalize();
};

}  // namespace blobstore
