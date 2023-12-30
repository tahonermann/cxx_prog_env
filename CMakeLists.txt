# Copyright (c) 2023, Tom Honermann
#
# This file is distributed under the MIT License. See the accompanying file
# LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
# and conditions.

cmake_minimum_required(VERSION 3.12)

project(
  cxx_prog_env
  VERSION 0.1
  LANGUAGES C CXX
)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

configure_package_config_file(
  cmake/cxx_prog_env-config.cmake.in
  ${CMAKE_CURRENT_BINARY_DIR}/cxx_prog_env-config.cmake
  PATH_VARS
  CMAKE_INSTALL_INCLUDEDIR
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cxx_prog_env
)

add_subdirectory(src)

install(
  TARGETS cxx_prog_env
  EXPORT cxx_prog_env
  RUNTIME
    COMPONENT Runtime
  LIBRARY
    COMPONENT Runtime
  ARCHIVE
    COMPONENT Development
  PUBLIC_HEADER
    COMPONENT Development
)
install(
  DIRECTORY include/
  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
  COMPONENT Development
)
install(
  DIRECTORY examples/
  DESTINATION examples
  COMPONENT Examples
)
install(
  EXPORT cxx_prog_env
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cxx_prog_env
  COMPONENT Development
)
install(
  FILES ${CMAKE_CURRENT_BINARY_DIR}/cxx_prog_env-config.cmake
  DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/cxx_prog_env
  COMPONENT Development
)

# The 'test-install' target is used to exercise installation and to validate
# that the examples build and run as expected in the installation location.
# This target explicitly performs a build since the 'install' target doesn't
# have a dependency on 'all'.
# FIXME: The default build type used for the '--build' step differs from the
# FIXME: default build type used for the '--install' step when using the
# FIXME: "Visual Studio 17 2022" generator. The generator expressions involving
# FIXME: $<CONFIG> below avoid this inconsistency by passing a '--config'
# FIXME: option ('-C' for ctest) when $<CONFIG> is not an empty string.
# FIXME: See https://gitlab.kitware.com/cmake/cmake/-/issues/25548.
add_custom_target(
  test-install
  COMMAND
    ${CMAKE_COMMAND}
      --build ${CMAKE_BINARY_DIR}
      $<$<BOOL:$<CONFIG>>:"--config"> $<$<BOOL:$<CONFIG>>:$<CONFIG>>
  COMMAND
    ${CMAKE_COMMAND}
      --install ${CMAKE_BINARY_DIR}
      $<$<BOOL:$<CONFIG>>:"--config"> $<$<BOOL:$<CONFIG>>:$<CONFIG>>
      --prefix install
  COMMAND
    ${CMAKE_COMMAND}
      -DCMAKE_PREFIX_PATH=${CMAKE_BINARY_DIR}/install/lib/cmake/cxx_prog_env
      -B ${CMAKE_BINARY_DIR}/install/examples/build
      -S ${CMAKE_BINARY_DIR}/install/examples
  COMMAND
    ${CMAKE_COMMAND}
      --build ${CMAKE_BINARY_DIR}/install/examples/build
      $<$<BOOL:$<CONFIG>>:"--config"> $<$<BOOL:$<CONFIG>>:$<CONFIG>>
  COMMAND
    ${CMAKE_COMMAND}
      -E chdir ${CMAKE_BINARY_DIR}/install/examples/build
      ${CMAKE_CTEST_COMMAND} $<$<BOOL:$<CONFIG>>:"-C"> $<$<BOOL:$<CONFIG>>:$<CONFIG>>
)
