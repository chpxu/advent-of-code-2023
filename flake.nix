{
  description = "Nix Flake for C/C++";
  inputs.nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
  inputs.flake-utils = {url = "github:numtide/flake-utils";};

  outputs = {
    self,
    nixpkgs,
    flake-utils,
  }:
    flake-utils.lib.eachDefaultSystem (system: let
      pkgs = import nixpkgs {inherit system;};
      llvm = pkgs.llvmPackages_latest;
      runner = pkgs.writeShellScriptBin "run" (builtins.readFile ./script.sh);
    in {
      devShells.default = pkgs.mkShell.override {stdenv = pkgs.clangStdenv;} rec {
        nativeBuildInputs = with pkgs; [pkg-config cmake];
        #.https://gist.github.com/fufexan/2e7020d05ff940c255d74d5c5e712815
        packages = with pkgs; [
          gnumake
          cmake
          bear

          # debugger
          llvm.lldb
          gdb

          # fix headers not found
          clang-tools
          boost

          # LSP and compiler
          llvm.libstdcxxClang

          # other tools
          cppcheck
          llvm.libllvm
          valgrind
          runner

          # stdlib for cpp
          llvm.libcxx
        ];
        shellHook = ''
          cat << EOF > .vscode/settings.json
          {
            "C_Cpp.default.cppStandard": "c++17",
            "C_Cpp.default.compilerPath": "${llvm.libstdcxxClang}/bin/clang++",
            "C_Cpp.default.cStandard": "c99"
          }
          EOF
        '';
      };
    });
}
