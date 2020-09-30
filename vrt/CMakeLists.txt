#set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
project(vrt)
cmake_minimum_required(VERSION 3.10)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../lib/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../lib/)

include_directories(include/vrt)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/lib/*.cc)
file(GLOB PRIVATE_HDR ${PROJECT_SOURCE_DIR}/lib/*.h)
file(GLOB HEADER ${PROJECT_SOURCE_DIR}/include/*.h)

set(Boost_USE_STATIC_LIBS ON)

find_package(Boost REQUIRED)

find_path(BOOST_FORMAT_INCLUDE_DIRS "boost/format.hpp" REQUIRED)


add_library(vrt SHARED STATIC ${SRC_FILES})

include_directories(${BOOST_FORMAT_INCLUDE_DIRS})

target_include_directories(vrt PRIVATE ${PROJECT_SOURCE_DIR}/lib/vrt)
target_include_directories(vrt PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(vrt PRIVATE ${Boost_LIBRARIES})


