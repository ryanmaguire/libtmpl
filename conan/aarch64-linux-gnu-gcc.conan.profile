toolchain=/usr/aarch64-linux-gnu
target_host=aarch64-linux-gnu
cc_compiler=gcc
cxx_compiler=g++

[env]
CONAN_CMAKE_FIND_ROOT_PATH=$toolchain  # Optional, for CMake to find things in that folder
CHOST=$target_host
AR=$target_host-ar
AS=$target_host-as
RANLIB=$target_host-ranlib
CC=$target_host-$cc_compiler
CXX=$target_host-$cxx_compiler
STRIP=$target_host-strip
RC=$target_host-windres

[settings]
arch=armv8.3
arch_build=x86_64
compiler=gcc
compiler.libcxx=libstdc++
compiler.version=11
os=Linux
os_build=Linux
[options]
[build_requires]
[env]
