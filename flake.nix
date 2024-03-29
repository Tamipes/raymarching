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
            cp -r $TMP $out/src
          '';
          #mv $TMP/LightGBM/lightgbm $out/bin
          #ls $TMPDIR >> $out/bin/ls.txt

          cmakeFlags = [
            # "-DBUILD_SHARED_LIBS=ON"
            "-DBUILD_NIXOS=ON"
            "-DCMAKE_C_FLAGS=-D_GLFW_GLX_LIBRARY='\"${lib.getLib libGL}/lib/libGL.so.1\"'"
          ];
        }
      );
    in rec {
      defaultApp = flake-utils.lib.mkApp {
        drv = defaultPackage;
      };
      defaultPackage = damiRaymarch;
      devShell = pkgs.mkShell {
        # shellHook = ''
        # export LD_LIBRARY_PATH="/run/opengl-driver/lib:/run/opengl-driver-32/lib";
        # '';
          # cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -G Ninja -B build .
        shellHook = ''
          mkdir build
          cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -B build .
        '';
          # cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -B build .
        buildInputs = [
          # pkgs.clang
          # pkgs.cmake
          # pkgs.xorg.libX11
          # pkgs.xorg.libXrandr
          # pkgs.xorg.libXinerama
          # pkgs.xorg.libXcursor
          # pkgs.xorg.libXi
          # pkgs.libGL
          # pkgs.glfw
          pkgs.clang-tools_17
          damiRaymarch 
        ] ++ (with pkgs; [ cmake libGL ]) ++ (with pkgs.xorg; [ libX11 libXrandr libXinerama libXcursor libXi libXext ]);
      };
    }
  );
}
