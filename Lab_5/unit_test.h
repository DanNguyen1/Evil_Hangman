#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "my_string.h"

Status test_init_default_returns_nonNULL(char* buffer, int length);
Status test_get_size_on_init_default_returns_0(char* buffer, int length);
Status test_get_capacity_on_init_default_returns_7(char* buffer, int length);
Status test_init_c_string_helloworld_returns_nonNULL(char* buffer, int length);
Status test_get_size_on_init_c_string_helloworld_returns_10(char* buffer, int length);
Status test_get_capacity_on_init_c_string_helloworld_returns_11(char* buffer, int length);

#endif
