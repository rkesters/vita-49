#set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake")
project(vrt VERSION 1.0.0)
cmake_minimum_required(VERSION 3.10)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../lib/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../lib/)

#include_directories(include/vrt)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/lib/*.cc)
file(GLOB PRIVATE_HDR ${PROJECT_SOURCE_DIR}/lib/*.h)
file(GLOB HEADER ${PROJECT_SOURCE_DIR}/include/vrt/*.h)

set(Boost_USE_STATIC_LIBS ON)

find_package(Boost REQUIRED)

find_path(BOOST_FORMAT_INCLUDE_DIRS "boost/format.hpp" REQUIRED)


add_library(vrt SHARED STATIC ${SRC_FILES})

include_directories(${BOOST_FORMAT_INCLUDE_DIRS})

MESSAGE(STATUS "CMAKE_CURRENT_SOURCE_DIR = ${CMAKE_CURRENT_SOURCE_DIR}")

target_include_directories(vrt PRIVATE ${PROJECT_SOURCE_DIR}/lib/vrt)
target_include_directories(vrt PUBLIC 
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include/vrt>)

#set_target_properties( vrt PROPERTIES PUBLIC_HEADER "include/vrt/rx.h" )
set_target_properties( vrt PROPERTIES PUBLIC_HEADER "${HEADER}" )

MESSAGE(STATUS "HEADER = ${HEADER}")

target_link_libraries(vrt PRIVATE ${Boost_LIBRARIES})

include(GNUInstallDirs)
set( version_config "${CMAKE_CURRENT_BINARY_DIR}/vrtConfigVersion.cmake" )
include( CMakePackageConfigHelpers )

write_basic_package_version_file( "${version_config}"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion )

MESSAGE(STATUS "CMAKE_INSTALL_INCLUDEDIR = ${CMAKE_INSTALL_INCLUDEDIR}")

install(TARGETS vrt EXPORT vrtConfig PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/vrt ) 
export( TARGETS vrt NAMESPACE vrt:: FILE vrtTargets.cmake )

install( EXPORT vrtConfig
  FILE vrtTargets.cmake
  NAMESPACE vrt::
  DESTINATION "share/vrt" )

install (  FILES vrtConfig.cmake "${version_config}"  DESTINATION "share/vrt" )
