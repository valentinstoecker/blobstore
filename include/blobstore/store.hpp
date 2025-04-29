#pragma once

#include <filesystem>
#include <iostream>
#include "blobstore/hash.hpp"

namespace blobstore {

class store {
  std::filesystem::path root;

  hash insert(std::ostream& dstream);
};

}  // namespace blobstore