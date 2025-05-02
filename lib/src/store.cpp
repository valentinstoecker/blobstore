#include "blobstore/store.hpp"

#include <openssl/evp.h>
#include <zlib.h>

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
  char in_buf[BUFSIZE];
  char z_buf[BUFSIZE];
  hasher ctx;
  hash h;

  fs::path tmp_path = temp_file();
  ofstream out = ofstream(tmp_path, ios_base::out);

  z_stream strm;
  strm.zalloc = Z_NULL;
  strm.zfree = Z_NULL;
  strm.opaque = Z_NULL;

  deflateInit(&strm, Z_DEFAULT_COMPRESSION);

  do {
    in.read(in_buf, BUFSIZE);
    strm.avail_in = in.gcount();
    strm.next_in = reinterpret_cast<Bytef*>(in_buf);
    do {
      strm.avail_out = BUFSIZE;
      strm.next_out = reinterpret_cast<Bytef*>(z_buf);
      deflate(&strm, Z_NO_FLUSH);
      out.write(z_buf, BUFSIZE - strm.avail_out);
      ctx.write(z_buf, BUFSIZE - strm.avail_out);
    } while (strm.avail_out == 0);
    // out.write(in_buf, in.gcount());
    // ctx.write(in_buf, in.gcount());
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
