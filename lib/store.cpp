#include "blobstore/store.hpp"

#include <openssl/evp.h>
#include <fstream>

using namespace std;

#define BUFSIZE 4096

namespace blobstore
{
  store::store(const filesystem::path& path) {
    root = filesystem::absolute(path);
    filesystem::create_directories(root);
  }

  hash store::insert(istream& dstream) {
    auto tmp_dir = filesystem::temp_directory_path();
    filesystem::create_directories(tmp_dir);
    auto tmp_path = tmp_dir / "test";
    auto file = ofstream(tmp_path, ios_base::out);
    printf("tmp path: %s\n", tmp_path.c_str());
    uint8_t buf[BUFSIZE];

    hash h;

    EVP_MD_CTX* ctx = EVP_MD_CTX_new();
    if(!EVP_DigestInit(ctx, EVP_sha256())) {
      printf("init failed");
      exit(1);
    };

    do {
      dstream.read((char*)buf, BUFSIZE);
      file.write((char*)buf, dstream.gcount());
      if (!EVP_DigestUpdate(ctx, buf, dstream.gcount())){
        printf("update failed");
        exit(1);
      };
    } while (0 < dstream.gcount());
  
    file.close();

    unsigned char* ptr = (unsigned char*)(&(h.data));
  
    if(!EVP_DigestFinal(ctx, ptr, NULL)) {
      printf("final failed");
      exit(1);
    };

    EVP_MD_CTX_free(ctx);

    filesystem::rename(tmp_dir / "test", root / h.to_string());

    return h;
  }
} // namespace blobstore
