#pragma once

#include <filesystem>
#include <iostream>
#include "blobstore/hash.hpp"

namespace blobstore {

class store {
  std::filesystem::path root;
public:
  hash insert(std::istream& dstream);
};

}  // namespace blobstore