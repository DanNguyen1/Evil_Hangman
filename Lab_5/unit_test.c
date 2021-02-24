#include <stdio.h>
#include "unit_test.h"
int main(void)
{
	Status (*tests[])(char*, unsigned long) =
	{
		test_init_default_returns_nonNULL,
		test_get_size_on_init_default_returns_0,
		test_get_capacity_on_init_default_returns_7,
		test_init_c_string_helloworld_returns_nonNULL,
		test_get_size_on_init_c_string_helloworld_returns_10,
		test_get_capacity_on_init_c_string_helloworld_returns_11,
		test_compare_two_strings_returns_0,
		test_compare_two_strings_returns_less_than_0,
		test_compare_two_strings_returns_greater_than_0,
		test_destroy_does_not_leave_dangling_pointer,
		test_my_string_extraction_successfully_extracts,
		test_my_string_insertion_successfully_inserts,
		test_my_string_extraction_extracts_correct_word,
		test_my_string_push_back_returns_SUCCESS,
		test_my_string_push_back_doubles_capacity,
		test_my_string_push_back_copies_old_string_and_adds_new_char,
		test_my_string_pop_back_returns_SUCCESS,
		test_my_string_pop_back_returns_FAILURE_for_empty_string,
		test_my_string_pop_back_decreases_size_by_1,
		test_my_string_pop_back_has_correct_string_after_pop
	};
	int number_of_functions = sizeof(tests) / sizeof(tests[0]);
	int i;
	char buffer[500];
	int success_count = 0;
	int failure_count = 0;
	
	for(i=0; i<number_of_functions; i++)
	{
		if(tests[i](buffer, 500) == FAILURE)
		{
			printf("FAILED: Test %d failed miserably\n", i);
			printf("\t%s\n", buffer);
			failure_count++;
		}
		else
		{
			// printf("PASS: Test %d passed\n", i);
			// printf("\t%s\n", buffer);
			success_count++;
		}
	}
	printf("Total number of tests: %d\n", number_of_functions);
	printf("%d/%d Pass, %d/%d Failure\n", success_count,
	number_of_functions, failure_count, number_of_functions);

	return 0;
}
