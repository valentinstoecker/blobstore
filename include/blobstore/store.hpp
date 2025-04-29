#pragma once

#include <filesystem>
#include <iostream>

#include "blobstore/hash.hpp"

namespace blobstore {

class store {
  std::filesystem::path root;

 public:
  store(const std::filesystem::path& path);

  hash insert(std::istream& dstream);
};

}  // namespace blobstore