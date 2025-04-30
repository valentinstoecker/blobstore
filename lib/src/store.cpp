#include "blobstore/store.hpp"

#include <openssl/evp.h>

#include <format>
#include <fstream>

using namespace std;

#define BUFSIZE 4096

namespace blobstore {

namespace fs = std::filesystem;

fs::path temp_file() {
  auto tmp_dir = fs::temp_directory_path();
  fs::create_directories(tmp_dir);
  long n = random();
  return tmp_dir / format("{}", n);
}

store::store(const fs::path& path) {
  root = fs::absolute(path);
  fs::create_directories(root);
}

hash store::insert(istream& in) {
  char buf[BUFSIZE];
  hasher ctx;
  hash h;

  fs::path tmp_path = temp_file();
  ofstream out = ofstream(tmp_path, ios_base::out);

  do {
    in.read(buf, BUFSIZE);
    out.write(buf, in.gcount());
    ctx.update(buf, in.gcount());
  } while (0 < in.gcount());

  out.close();

  h = ctx.finalize();

  fs::rename(tmp_path, root / h.to_string());

  return h;
}
}  // namespace blobstore
