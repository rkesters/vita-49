
set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
CACHE STRING "")
project(vrt)
cmake_minimum_required(VERSION 3.10)

add_subdirectory(./vrt)