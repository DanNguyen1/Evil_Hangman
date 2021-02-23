#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "my_string.h"

Status test_init_default_returns_nonNULL(char* buffer, unsigned long length);
Status test_get_size_on_init_default_returns_0(char* buffer, unsigned long length);
Status test_get_capacity_on_init_default_returns_7(char* buffer, unsigned long length);
Status test_init_c_string_helloworld_returns_nonNULL(char* buffer, unsigned long length);
Status test_get_size_on_init_c_string_helloworld_returns_10(char* buffer, unsigned long length);
Status test_get_capacity_on_init_c_string_helloworld_returns_11(char* buffer, unsigned long length);
Status test_compare_two_strings_returns_0(char* buffer, unsigned long length);
Status test_compare_two_strings_returns_less_than_0(char* buffer, unsigned long length);
Status test_compare_two_strings_returns_greater_than_0(char* buffer, unsigned long length);
Status test_destroy_does_not_leave_dangling_pointer(char* buffer, unsigned long length);
Status test_my_string_extraction_successfully_extracts(char* buffer, unsigned long length);
Status test_my_string_insertion_successfully_inserts(char* buffer, unsigned long length);
Status test_my_string_extraction_extracts_correct_word(char* buffer, unsigned long length);

#endif
