{
  inputs = {
    nixpkgs = {
      url = "github:nixos/nixpkgs/nixpkgs-unstable";
    };
    flake-utils = {
      url = "github:numtide/flake-utils";
    };
  };
  outputs = { nixpkgs, flake-utils, ... }: flake-utils.lib.eachDefaultSystem (system:
    let
      pkgs = import nixpkgs {
        inherit system;
      };
      damiRaymarch = (with pkgs; stdenv.mkDerivation {
        pname = "damiRaymarch";
        version = "0.0.1";
        src = ./.;
        nativeBuildInputs = [
          cmake
        ];
        patches = [ ./dependencies/glfw_x11.patch ];
        buildInputs = [
          xorg.libX11
          xorg.libX11.dev
          xorg.libXrandr
          xorg.libXinerama
          xorg.libXcursor
          xorg.libXi
          xorg.libXext
        ];
        propagatedBuildInputs = [
          libGL
        ];
        # buildPhase = "make -j $NIX_BUILD_CORES";
        installPhase = ''
          mkdir -p $out/bin
          find $TMP -type d -maxdepth 1 | grep source | xargs -I{} cp {}/build/Demo $out/bin/damiRaymarch
          find $TMP -type d -maxdepth 1 | grep source | xargs -I{} cp -r {}/resources $out/resources
        '';
        # cp -r $TMP $out/src

        cmakeFlags = [
          # "-DBUILD_SHARED_LIBS=ON"
          "-DBUILD_NIXOS=ON"
          "-DCMAKE_C_FLAGS=-D_GLFW_GLX_LIBRARY='\"${lib.getLib libGL}/lib/libGL.so.1\"'"
        ];
      }
      );
    in
    rec {
      defaultApp = flake-utils.lib.mkApp {
        drv = defaultPackage;
      };
      defaultPackage = damiRaymarch;
      devShell = pkgs.mkShell {
        shellHook = ''
          mkdir .build
          cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -B .build .
        '';
        packages = [ pkgs.clang-tools ];

        inputsFrom = [ damiRaymarch ];
        # buildInputs = [
        #   # LSP setup:
        #   pkgs.clang-tools_17
        #   pkgs.cmake-language-server

        #   damiRaymarch
        # ] ++ (with pkgs; [ cmake libGL ]) ++ (with pkgs.xorg; [ libX11 libXrandr libXinerama libXcursor libXi libXext ]);
      };
    }
  );
}
