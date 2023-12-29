# Copyright (c) 2023, Tom Honermann
#
# This file is distributed under the MIT License. See the accompanying file
# LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
# and conditions.

cmake_minimum_required(VERSION 3.12)

project(
  cxx_prog_env_example
  LANGUAGES CXX
)

include(CTest)

find_package(cxx_prog_env REQUIRED)

add_executable(example example.cpp)
target_link_libraries(example PRIVATE cxx_prog_env)

add_test(
  NAME example-with-no-options
  COMMAND example
)
add_test(
  NAME example-without-config-options
  COMMAND example arg1 arg2 arg3
)
add_test(
  NAME example-with-config-options
  COMMAND example arg1 --debug-mode arg2 --log-file /path/to/log.txt arg3
)
