#set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")
cmake_policy(SET CMP0048 NEW)

project(vrt VERSION 1.0.0)

cmake_minimum_required(VERSION 3.10)

add_subdirectory(./vrt)

set( version_config "${CMAKE_CURRENT_BINARY_DIR}/vrtConfigVersion.cmake" )
include( CMakePackageConfigHelpers )

write_basic_package_version_file( "${version_config}"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion )
install(TARGETS vrt EXPORT vrtConfig PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/vrt ) 
export( TARGETS vrt NAMESPACE vrt:: FILE vrtTargets.cmake )

install( EXPORT vrtConfig
  FILE vrtTargets.cmake
  NAMESPACE vrt::
  DESTINATION "share/vrt" )
install (  FILES vrtConfig.cmake "${version_config}"  DESTINATION "share/vrt" )
