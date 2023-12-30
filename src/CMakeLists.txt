# Copyright (c) 2023, Tom Honermann
#
# This file is distributed under the MIT License. See the accompanying file
# LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
# and conditions.

include(CheckCXXSymbolExists)
include(CheckIncludeFileCXX)

check_cxx_symbol_exists(_Get_argc "stdlib.h" HAVE_GET_ARGC)
check_cxx_symbol_exists(_Get_argv "stdlib.h" HAVE_GET_ARGV)
if(NOT HAVE_GET_ARGC OR NOT HAVE_GET_ARGV)
  set(USE_POLYFILL_GET_ARGC_ARGV 1)
endif()

check_include_file_cxx("text_encoding" HAVE_INCLUDE_TEXT_ENCODING)
if(NOT HAVE_INCLUDE_TEXT_ENCODING)
  set(USE_POLYFILL_TEXT_ENCODING 1)
endif()

add_library(cxx_prog_env STATIC iostring_ref.cpp program_arguments.cpp)
target_compile_features(cxx_prog_env PUBLIC cxx_std_20)
target_include_directories(cxx_prog_env
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

if(USE_POLYFILL_GET_ARGC_ARGV AND NOT WIN32)
  message(STATUS "Using polyfill for missing WG14 N2948 stdlib.h features")
  target_compile_definitions(cxx_prog_env PRIVATE USE_POLYFILL_GET_ARGC_ARGV)
  target_include_directories(cxx_prog_env PRIVATE get_argc_argv/include)
  target_sources(cxx_prog_env PRIVATE get_argc_argv/get_argc_argv.c)
endif()

if(USE_POLYFILL_TEXT_ENCODING)
  message(STATUS "Using polyfill for missing WG21 P1885 text_encoding features")
  target_compile_definitions(cxx_prog_env PRIVATE USE_POLYFILL_TEXT_ENCODING)
  target_include_directories(cxx_prog_env PRIVATE text_encoding/include)
  target_sources(cxx_prog_env PRIVATE text_encoding/text_encoding.cpp)
endif()
