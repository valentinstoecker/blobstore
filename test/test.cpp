#include <blobstore/store.hpp>
#include <sstream>

using namespace blobstore;

void empty_hash() {
  hasher ctx;
  hash h = ctx.finalize();
  printf("%s\n", h.to_string().c_str());
  if (h.to_string() !=
      "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855") {
    printf("Hash is not empty!");
    exit(1);
  }
}

int main() {
  empty_hash();

  store s = store(".bs");
  std::string text = "Hello!\n";
  auto ss = std::stringstream(text);
  hash h = s.insert(ss);
  printf("%s\n", h.to_string().c_str());

  std::string text2 = "Bye!\n";
  auto ss2 = std::stringstream(text2);
  hash h2 = s.insert(ss2);
  printf("%s\n", h2.to_string().c_str());

  if (h == h2) {
    printf("Hashes are equal!");
    return 1;
  }

  std::string text3 = "data...\n";
  auto ss3_l = std::stringstream(text3);
  auto ss3_r = std::stringstream(text3);
  hash l = s.insert(ss3_l);
  hash r = s.insert(ss3_r);
  printf("l = %s\n", l.to_string().c_str());
  printf("r = %s\n", r.to_string().c_str());

  if (!(l == r)) {
    printf("Hash is impure!");
    return 1;
  }
}