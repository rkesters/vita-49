#set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
cmake_policy(SET CMP0048 NEW)

project(vrt VERSION 1.0.0)

cmake_minimum_required(VERSION 3.10)

add_subdirectory(./vrt)
