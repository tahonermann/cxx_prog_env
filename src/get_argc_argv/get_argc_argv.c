// Copyright (c) 2023, Tom Honermann
//
// This file is distributed under the MIT License. See the accompanying file
// LICENSE.txt or http://www.opensource.org/licenses/mit-license.php for terms
// and conditions.

#include <get_argc_argv.h>

static int argc = 0;
static char **argv = 0;

#if defined(_WIN32) /* { */
#error Use GetCommandLineW() and CommandLineToArgvW() on Windows

#elif defined(__linux__) /* } { */
static int init_args(int ac, char **av, char **envp) {
  argc = ac;
  argv = av;
}
__attribute__((section(".init_array"))) static void *init_args_ptr = &init_args;
#else /* } */

#error Unsupported or unrecognized platform
#endif

int _Get_argc(void) {
  return argc;
}

const char* const* _Get_argv(void) {
  return (const char* const*)argv;
}
