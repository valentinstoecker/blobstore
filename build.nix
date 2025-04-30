{
  stdenv,
  cmake,
  gcc,
  lib,
  openssl,
}:
let
  fs = lib.fileset;
in
stdenv.mkDerivation {
  pname = "blobstore";
  version = "0.1.0";

  src = fs.toSource {
    root = ./.;
    fileset = fs.unions [
      ./lib
      ./test
      ./CMakeLists.txt
    ];
  };

  buildInputs = [
    openssl
  ];

  nativeBuildInputs = [
    cmake
    gcc
  ];

  doCheck = true;
}
