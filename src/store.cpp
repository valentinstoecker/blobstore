#include "blobstore/store.hpp"

using namespace std;

namespace blobstore
{
  hash store::insert(ostream& dstream) {
    auto tmp_dir = filesystem::temp_directory_path();
    filesystem::create_directories(tmp_dir);
    return hash();
  }
} // namespace blobstore
