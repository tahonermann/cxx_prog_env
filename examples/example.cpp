// Copyright (c) 2023, Tom Honermann
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <filesystem>
#include <iostream>
#include <program_arguments>


struct configuration {
  bool debug_mode;
  std::filesystem::path log_file;
};

auto config = [] {
  bool debug_mode = false;
  std::filesystem::path log_file;
  auto &args = program_arguments;
  // FIXME: program_arguments is implemented using transform_view and its
  // FIXME: iterator does not provide operator->.
  for (auto it = args.begin(); it != args.end(); ++it) {
    if ((*it).as_string() == "--debug-mode") {
      debug_mode = true;
    } else if ((*it).as_string() == "--log-file") {
      ++it;
      log_file = (*it).as_path();
    }
  }
  return configuration { debug_mode, log_file };
}();

int main() {
  std::cout << "Configuration:\n";
  std::cout << "  debug_mode: " << config.debug_mode << "\n";
  std::cout << "  log_file:   " << config.log_file << "\n";
}
