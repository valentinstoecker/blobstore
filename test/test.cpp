#include <blobstore/store.hpp>
#include <sstream>

using namespace blobstore;

int main() {
  store s = store();
  std::string text = "Hello!\n";
  auto ss = std::stringstream(text);
  hash h = s.insert(ss);
  for (size_t i = 0; i < sizeof(hash::data); i++)
  {
    printf("%02x", h.data[i]);
  }
  
}