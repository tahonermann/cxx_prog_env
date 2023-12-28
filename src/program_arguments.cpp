// Copyright (c) 2023, Tom Honermann
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <cstring>
#include <program_arguments>
#include <span>
#if defined(USE_POLYFILL_GET_ARGC_ARGV)
#include <get_argc_argv>
#endif


namespace detail {

static iostring_ref args_transform(const char *arg) {
  return { std::span<const char>(arg, std::strlen(arg)) };
}

static args_view& get_args_view() {
  static args_view av{
    std::span<const char *const>(std::_Get_argv(), std::_Get_argc()),
    args_transform
  };
  return av;
}

decltype(std::declval<args_view>().begin()) program_arguments_view::begin() const {
  return get_args_view().begin();
}

decltype(std::declval<args_view>().begin()) program_arguments_view::end() const {
  return get_args_view().end();
}

} // namespace detail

const detail::program_arguments_view program_arguments;
