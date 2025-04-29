{
  pkgs ? import <nixpkgs> { },
}:
with pkgs;
mkShell {
  buildInputs = [
    nixpkgs-fmt
  ];

  inputsFrom = [
    (pkgs.callPackage ./build.nix { })
  ];
}
