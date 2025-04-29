#include <blobstore/hash.hpp>

namespace blobstore {
std::string hash::to_string() {
  std::string out;
  out.reserve(2*sizeof(data) + 1);
  for (size_t i = 0; i < sizeof(data); i++) {
    char buf[3];
    snprintf((char*)&buf, sizeof(buf), "%02x", data[i]);
    out.append({buf[0], buf[1]});
  }
  return out;
}
}  // namespace blobstore
