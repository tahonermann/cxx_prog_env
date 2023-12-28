// Copyright (c) 2023, Tom Honermann
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#if !defined(CXX_PROG_ENV_SRC_GET_ARGC_ARGV_GET_ARGC_ARGV_H)
#define CXX_PROG_ENV_SRC_GET_ARGC_ARGV_GET_ARGC_ARGV_H

#if defined(__cplusplus)
extern "C" {
#endif

int _Get_argc(void);
const char* const* _Get_argv(void);

#if defined(__cplusplus)
}
#endif

#endif // CXX_PROG_ENV_SRC_GET_ARGC_ARGV_GET_ARGC_ARGV_H
