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
  string h_str = h.to_string();
  fs::path dir_name = root / h_str.substr(0, 2);
  fs::create_directories(dir_name);

  fs::rename(tmp_path, dir_name / h_str.substr(2));

  return h;
}
}  // namespace blobstore
