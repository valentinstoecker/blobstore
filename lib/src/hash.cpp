#include "blobstore/hash.hpp"

namespace blobstore {

bool hash::operator==(hash& other) {
  for (size_t i = 0; i < sizeof(data); i++) {
    if (data[i] != other.data[i]) return false;
  }
  return true;
}

bool hash::operator!=(hash& other) { return !operator==(other); }

std::string hash::to_string() {
  std::string out;
  out.reserve(2 * sizeof(data) + 1);
  for (size_t i = 0; i < sizeof(data); i++) {
    char buf[3];
    snprintf((char*)&buf, sizeof(buf), "%02x", data[i]);
    out.append({buf[0], buf[1]});
  }
  return out;
}

hasher::hasher() : ctx(nullptr) {}

hasher::~hasher() {
  if (ctx) {
    EVP_MD_CTX_free(ctx);
  }
}

void hasher::init() {
  ctx = EVP_MD_CTX_new();
  if (!EVP_DigestInit(ctx, EVP_sha256())) {
    throw 1;
  }
}

void hasher::write(const char* data, size_t len) {
  if (!ctx) {
    init();
  }
  if (!EVP_DigestUpdate(ctx, data, len)) {
    throw 1;
  }
}

hash hasher::finalize() {
  if (!ctx) {
    init();
  }
  hash h;
  unsigned int len = 0;
  if (!EVP_DigestFinal_ex(ctx, h.data.data(), &len)) {
    throw 1;
  }
  return h;
}

}  // namespace blobstore
