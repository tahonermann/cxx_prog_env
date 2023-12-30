// Copyright (c) 2023, Tom Honermann
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <cassert>
#include <cstring>
#include <algorithm>
#include <text_encoding>


#if defined(__linux__) /* { */
#include <locale.h>
#include <langinfo.h>

namespace {
const char* get_environment_encoding() {
  return nl_langinfo_l(CODESET, newlocale(LC_CTYPE_MASK, "", (locale_t)0));
}
}

#elif defined(_WIN32) /* { */
#include <windows.h>

namespace {
const char* get_environment_encoding() {
  // FIXME: Obtain proper names for all code pages.
  UINT acp = GetACP();
  switch (acp) {
    case 1252:
      return "windows-1252";
    case 65001:
      return "utf-8";
  }
  return nullptr;
}
}

#else /* } */
#error Unsupported or unrecognized platform
#endif


constexpr text_encoding::text_encoding(std::string_view encoding) noexcept {
  assert(encoding.size() < sizeof(encname));
  std::copy_n(encoding.begin(), encoding.size(), encname);
  encname[encoding.size()] = '\0';
}

text_encoding text_encoding::environment() {
  return text_encoding(get_environment_encoding());
}

text_encoding text_encoding::wide_environment() {
  if constexpr (sizeof(wchar_t) == 2) {
    return text_encoding("UTF-16");
  } else if constexpr (sizeof(wchar_t) == 4) {
    return text_encoding("UTF-32");
  } else {
    assert(false && "Unknown wide environment encoding");
  }
}

constexpr bool operator==(const text_encoding& te1,
                          const text_encoding& te2) noexcept
{
  const char *p1 = te1.encname;
  const char *p2 = te2.encname;
  while (*p1 || *p2) {
    if (*p1++ != *p2++) {
      return false;
    }
  }
  return true;
}
