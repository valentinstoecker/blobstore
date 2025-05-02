{
  description = "A very basic flake";

  inputs = {
    nixpkgs.url = "github:nixos/nixpkgs?ref=nixos-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs =
    {
      self,
      nixpkgs,
      flake-utils,
    }:

    (flake-utils.lib.eachDefaultSystem (
      system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
        blobstore = pkgs.callPackage ./build.nix { };
      in
      {
        packages.default = blobstore;
        packages.blobstore = blobstore;
        devShell = pkgs.mkShell {
          buildInputs = [
            pkgs.nixpkgs-fmt
          ];

          inputsFrom = [
            blobstore
          ];
        };

        hydraJobs = {
          blobstore = self.x86_64-linux.packages.blobstore;
        };
      }
    ));
}
