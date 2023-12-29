// Copyright (c) 2023, Tom Honermann
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <detail/iostring_ref>
#include <text_encoding>


namespace detail {

std::string iostring_ref::as_string() const {
  // FIXME: Add conversion to the ordinary character encoding.
  return { raw_data.begin(), raw_data.end() };
}

std::wstring iostring_ref::as_wstring() const {
  // FIXME: Add conversion to the wide character encoding.
}

std::u8string iostring_ref::as_u8string() const {
  // FIXME: Add conversion to UTF-8.
}

std::u16string iostring_ref::as_u16string() const {
  // FIXME: Add conversion to UTF-16.
}

std::u32string iostring_ref::as_u32string() const {
  // FIXME: Add conversion to UTF-32.
}

std::filesystem::path iostring_ref::as_path() const {
  // FIXME: Add conversion to a file path.
}

} // namespace detail
