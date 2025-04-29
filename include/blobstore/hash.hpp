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
  // move constructor and assignment operator
  hasher(hasher&& other) : ctx(other.ctx) { other.ctx = nullptr; }

  void init();
  void update(const char* data, size_t len);
  hash finalize();
};

}  // namespace blobstore
