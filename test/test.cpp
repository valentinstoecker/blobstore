#include <blobstore/store.hpp>
#include <sstream>

using namespace blobstore;

int main() {
  store s = store(".bs");
  std::string text = "Hello!\n";
  auto ss = std::stringstream(text);
  hash h = s.insert(ss);
  printf("%s\n", h.to_string().c_str());

  std::string text2 = "Bye!\n";
  auto ss2 = std::stringstream(text2);
  hash h2 = s.insert(ss2);
  printf("%s\n", h2.to_string().c_str());
}