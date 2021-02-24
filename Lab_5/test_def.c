#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unit_test.h"

Status test_init_default_returns_nonNULL(char* buffer, unsigned long length)
{
	MY_STRING hString = my_string_init_default();

	if(hString == NULL)
	{
		strncpy(buffer, "test_init_default_returns_nonNULL\n"
				"my_string_init_default returns NULL", length);
		return FAILURE;
	}

	else
	{
		my_string_destroy(&hString);
		strncpy(buffer, "\ttest_init_default_returns_nonNULL\n", length);
		return SUCCESS;
	}	
}

Status test_get_size_on_init_default_returns_0(char* buffer, unsigned long length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_default();

	if(my_string_get_size(hString) != 0)
	{
		status = FAILURE;
		printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
		strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
				"Did not receive 0 from get_size after init_default\n", length);
	}

	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_get_size_on_init_default_returns_0\n" , length);
	}

	my_string_destroy(&hString);
	return status;
}

Status test_get_capacity_on_init_default_returns_7(char* buffer, unsigned long length)
{
        MY_STRING hString = NULL;
        Status status;
        hString = my_string_init_default();

        if(my_string_get_capacity(hString) != 7)
        {
                status = FAILURE;
                printf("Expected a capacity of 7 but got %d\n", my_string_get_capacity(hString));
		strncpy(buffer, "test_get_capacity_on_init_default_returns_0\n"
				"Did not recieve 7 from get_capacity after init default\n", length);
	}

	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_get_capacity_on_init_default_returns_7\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status test_init_c_string_helloworld_returns_nonNULL(char* buffer, unsigned long length)
{
        MY_STRING hString = NULL;
        hString = my_string_init_c_string("helloworld");

        if(hString == NULL)
        {
                strncpy(buffer, "test_init_c_string_helloworld_returns_nonNULL\n"
                                "my_string_init_c_string returns NULL", length);
                return FAILURE;
        }

        else
        {
                my_string_destroy(&hString);
                strncpy(buffer, "\ttest_init_c_string_helloworld_returns_nonNULL\n", length);
                return SUCCESS;
        }

}
Status test_get_size_on_init_c_string_helloworld_returns_10(char* buffer, unsigned long length)
{
        MY_STRING hString = NULL;
        Status status;
        hString = my_string_init_c_string("helloworld");

        if(my_string_get_size(hString) != 10)
        {
                status = FAILURE;
                printf("Expected a size of 10 but got %d\n", my_string_get_size(hString));
                strncpy(buffer, "test_get_size_on_init_c_string_helloworld_returns_10\n"
                                "Did not receive 10 from get_size after init_c_string\n", length);
        }

        else
        {
                status = SUCCESS;
                strncpy(buffer, "test_get_size_on_init_c_string_helloworld_returns_10\n" , length);
        }

        my_string_destroy(&hString);
        return status;
}

Status test_get_capacity_on_init_c_string_helloworld_returns_11(char* buffer, unsigned long length)
{
        MY_STRING hString = NULL;
        Status status;
        hString = my_string_init_c_string("helloworld");

        if(my_string_get_capacity(hString) != 11)
        {
                status = FAILURE;
                printf("Expected a capacity of 11 but got %d\n", my_string_get_capacity(hString));
                strncpy(buffer, "test_get_size_on_init_c_string_helloworld_returns_14\n"
                                "Did not receive 11 from get_capacity after init_c_string\n", length);
        }

        else
        {
                status = SUCCESS;
                strncpy(buffer, "test_get_capacity_on_init_c_string_helloworld_returns_11\n" , length);
        }

        my_string_destroy(&hString);
        return status;
}

Status test_compare_two_strings_returns_0(char* buffer, unsigned long length)
{
	MY_STRING hLString = NULL;
	MY_STRING hRString = NULL;
	Status status;

	hLString = my_string_init_c_string("abba");
	hRString = my_string_init_c_string("abba");

	if (my_string_compare(hLString, hRString) != 0)
	{
		status = FAILURE;
		printf("Expected to return 0 but got %d\n", my_string_compare(hLString, hRString));
		strncpy(buffer, "test_compare_two_strings_return_0\n"
				"Did not return 0 from string_compare after comparing two of the same strings\n", length);
	}

	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_compare_two_strings_returns_0\n", length);
	}

	my_string_destroy(&hLString);
	my_string_destroy(&hRString);
	return status;
}	

Status test_compare_two_strings_returns_less_than_0(char* buffer, unsigned long length)
{
        MY_STRING hLString = NULL;
        MY_STRING hRString = NULL;
        Status status;

        hLString = my_string_init_c_string("abba");
        hRString = my_string_init_c_string("habba");

        if (my_string_compare(hLString, hRString) >= 0)
        {
                status = FAILURE;
                printf("Expected to return integer less than 0 but got %d\n", my_string_compare(hLString, hRString));
                strncpy(buffer, "test_compare_two_strings_return_less_than_0\n"
                                "Did not return less than 0 from string_compare after comparing\n", length);
        }

        else
        {
                status = SUCCESS;
                strncpy(buffer, "test_compare_two_strings_returns_less_than_0\n", length);
        }

        my_string_destroy(&hLString);
        my_string_destroy(&hRString);
        return status;
}

Status test_compare_two_strings_returns_greater_than_0(char* buffer, unsigned long length)
{
        MY_STRING hLString = NULL;
        MY_STRING hRString = NULL;
        Status status;

        hLString = my_string_init_c_string("habba");
        hRString = my_string_init_c_string("abba");

        if (my_string_compare(hLString, hRString) <= 0)
        {
                status = FAILURE;
                printf("Expected to return integer greater but got %d\n", my_string_compare(hLString, hRString));
                strncpy(buffer, "test_compare_two_strings_return_greater_than_0\n"
                                "Did not return greater than 0 from string_compare after comparing\n", length);
        }

        else
        {
                status = SUCCESS;
                strncpy(buffer, "test_compare_two_strings_returns_greater_than_0\n", length);
        }

        my_string_destroy(&hLString);
        my_string_destroy(&hRString);
        return status;
}

Status test_destroy_does_not_leave_dangling_pointer(char* buffer, unsigned long length)
{
	MY_STRING hString = NULL;
	Status status;

	hString = my_string_init_default();

	my_string_destroy(&hString);

	if (hString != NULL)
	{
		status = FAILURE;
		printf("Expected to set hString to null after destroying contents\n");
		strncpy(buffer, "test_destroy_does_not_leave_dangling_ponter\n"
				"Did not set handle to string object to NULL after destroying contents\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_destroy_does_not_leave_dangling_ponter\n", length);
	}

	return status;
}

Status test_my_string_extraction_successfully_extracts(char* buffer, unsigned long length)
{
	MY_STRING hString = NULL;
	FILE* fp;
	Status status;

	hString = my_string_init_default();
	fp = fopen("simple.txt", "r");

	status = my_string_extraction(hString, fp);

	if (status == FAILURE)
	{
		printf("Expected to extract word into string of object, but extraction failed\n");
		strncpy(buffer, "test_my_string_extraction_successfully_extracts\n"
				"Did not successfully extract a word and returned failure\n", length);
	}

	else if (my_string_empty(hString))
	{
		status = FAILURE;
		printf("Expected to extract word into string of object, but string is empty\n");
		strncpy(buffer, "test_my_string_extraction_successfully_extracts\n"
				"Did not successfully extract a word from a file and place into string of object\n", length);
	}
	else
	{
		strncpy(buffer, "test_my_string_extraction_successfully_extracts\n", length);
	}

	fclose(fp);
	my_string_destroy(&hString);
	return status;
	
}

Status test_my_string_insertion_successfully_inserts(char* buffer, unsigned long length)
{
	MY_STRING hString = NULL;
	FILE* fp;
	Status status;

	hString = my_string_init_c_string("hello");
	fp = fopen("simple.txt", "w");

	status = my_string_insertion(hString, fp);

	if (status == FAILURE)
	{
		printf("Expected to write(insert) word \"hello\" into file, but insertion failed\n");
		strncpy(buffer, "test_my_string_insertion_successfully_inserts\n"
				"Did not successfully write(insert) word \"hello\" into file\n", length);
	}
	else
	{
		strncpy(buffer, "test_my_string_insertion_successfully_inserts\n", length);
	}

	fclose(fp);
	my_string_destroy(&hString);
	return status;
}

Status test_my_string_extraction_extracts_correct_word(char* buffer, unsigned long length)
{
	MY_STRING hString = NULL;
	FILE* fp;
	Status status;
	char* string;
	int compare;

	hString = my_string_init_default();
	fp = fopen("../dictionary.txt", "r");

	while(my_string_extraction(hString, fp))
	{
		if(my_string_get_size(hString) == 29)
		{
			break;
		}
	}

	string = my_string_c_str(hString);

	compare = strcmp(string, "floccinaucinihilipilification");

	if (compare != 0)
	{
		status = FAILURE;
		printf("Expected to read word \"floccinaucinihilipilification\" into string object, but did not read right word\n");
		strncpy(buffer, "test_my_string_extraction_extracts_correct_word\n"
				"Did not successfully extract correct word \"floccinaucinihilipilification\" into object\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_my_string_extraction_extractions_correct_word\n", length);
	}

	fclose(fp);
	my_string_destroy(&hString);
	return status;
}

Status test_my_string_push_back_returns_SUCCESS(char* buffer, unsigned long length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	Status status;

	status = my_string_push_back(hString, '@');

	if (status == FAILURE)
	{
		printf("Expected to return SUCCESS (function worked) after calling my_string_push_back\n");
		strncpy(buffer, "test_my_string_push_back_returns_SUCCESS\n"
				"Did not successfully push back and returned FAILURE\n", length);
	}

	else
	{
		strncpy(buffer, "test_my_string_push_back_returns_SUCCESS\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status test_my_string_push_back_doubles_capacity(char* buffer, unsigned long length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	Status status;

	my_string_push_back(hString, '@');

	if (my_string_get_capacity(hString) != 14)
	{
		status = FAILURE;
		printf("Expected to update capacity to 14 after push back, but did not update capacity correctly\n");
		strncpy(buffer, "test_my_string_push_back_doubles_capacity\n"
				"Did not correctly update capacity after calling push back\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_my_string_push_back_doubles_capacity\n", length);
	}

	my_string_destroy(&hString);
	return status;

}

Status test_my_string_push_back_copies_old_string_and_adds_new_char(char* buffer, unsigned long length){
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("righto");
	char* string;
	int compare;
	Status status;

	my_string_push_back(hString, 'n');

	string = my_string_c_str(hString);

	compare = strcmp(string, "righton");

	if(compare != 0)
	{
		status = FAILURE;
		printf("Expected to update string from \"righto\" to \"righton\" but did not update the string correctly after push back\n");
		strncpy(buffer, "test_my_string_push_back_copies_old_string_and_adds_new_char\n"
				"Did not correctly add a new character to the end of string\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_my_string_push_back_copies_old_string_and_adds_new_char\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status test_my_string_pop_back_returns_SUCCESS(char* buffer, unsigned long length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("hello");
	Status status;

	status = my_string_pop_back(hString);

	if (status != SUCCESS)
	{
		printf("Expected to return SUCCESS (function worked) after calling my_string_pop_back\n");
                strncpy(buffer, "test_my_string_pop_back_returns_SUCCESS\n"
                                "Did not successfully pop back and returned FAILURE\n", length);
	}
	else
	{
		strncpy(buffer, "test_my_string_pop_back_returns_SUCCESS\n", length);
	}

	my_string_destroy(&hString);
	return status;
}


Status test_my_string_pop_back_returns_FAILURE_for_empty_string(char* buffer, unsigned long length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	Status status;

	status = my_string_pop_back(hString);

	if (status != FAILURE)
	{
		status = FAILURE;
		printf("Expected to return FAILURE (function failed) after attempting to pop back empty string\n");
		strncpy(buffer, "test_my_string_pop_back_returns_FAILURE_for_empty_string\n"
				"Did not return FAILURE and exit function after attempting to pop empty string\n", length);
	}

	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_my_string_pop_back_returns_FAILURE_for_empty_string\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status test_my_string_pop_back_decreases_size_by_1(char* buffer, unsigned long length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("hello");
	Status status;

	my_string_pop_back(hString);

	if(my_string_get_size(hString) != 4)
	{
		status = FAILURE;
		printf("Expected to get size 4 after my_string_pop_back\n");
		strncpy(buffer, "test_my_string_pop_back_decreases_size_by_1\n"
				"Did not correctly adjust size after pop back\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_my_string_pop_back_decreases_size_by_1\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status test_my_string_pop_back_has_correct_string_after_pop(char* buffer, unsigned long length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("hellos");
	char* string;
	int compare;
	Status status;

	my_string_pop_back(hString);

	string = my_string_c_str(hString);

	compare = strcmp(string, "hello");

	if (compare != 0)
	{
		status = FAILURE;
		printf("Expected to get string \"hello\" after pop back, but did not get correct string\n");
		strncpy(buffer, "test_my_string_pop_back_has_correct_string_after_pop\n"
				"Did not correctly get correct string after pop back\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_my_string_pop_back_has_correct_string_after_pop\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status test_my_string_at_returns_correct_char_from_string(char* buffer, unsigned long length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("qwerty");
	Status status;

	if (*my_string_at(hString, 4) != 't')
	{
		status = FAILURE;
		printf("Expected to get char \'t\' after finding at, but got different char\n");
		strncpy(buffer, "test_my_string_at_returns_correct_char_from_string\n"
				"Did not get correct char after function call my_string_at\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_my_string_at_returns_correct_char_from_string\n", length);
	}

	my_string_destroy(&hString);
	return status;	
}

Status test_my_string_c_str_returns_correct_c_string(char* buffer, unsigned long length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("hello");
	char* string;
	int compare;
	Status status;

	string = my_string_c_str(hString);

	compare = strcmp(string, "hello");

	if (compare != 0)
	{
		status = FAILURE;
		printf("Expected to get string \"hello\" and return as c-string but returned different string\n");
		strncpy(buffer, "test_my_string_c_str_returns_correct_c_string\n"
				"Did not return correct string after calling function my_string_c_str\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_my_string_c_str_returns_correct_c_string\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status test_my_string_concat_returns_correct_concat_c_string(char* buffer, unsigned long length)
{
	//for some reason, strcmp (from string.h) does not work when comparing concated string but my_string_compare does
	MY_STRING hResult = NULL;
	MY_STRING hAppend = NULL;
	MY_STRING hString = NULL;
	char* string;
	int compare;
	Status status;

	hResult =  my_string_init_c_string("hi");
	hAppend = my_string_init_c_string("hello");
	hString = my_string_init_c_string("hihello");

	my_string_concat(hResult, hAppend);

	compare = my_string_compare(hResult, hString);

	if (compare != 0)
	{
		status = FAILURE;
		string = my_string_c_str(hResult);
		printf("Expected to get string \"hihello\" after concat but got following string instead: ");
		printf("%s\n", string);
		strncpy(buffer, "test_my_string_concat_returns_correct_concat_c_string\n"
				"Did not returns correct string after concatenating two strings together\n", length);
	}

	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_my_string_concat_returns_correct_concat_c_string\n", length);
	}

	my_string_destroy(&hResult);
	my_string_destroy(&hAppend);
	my_string_destroy(&hString);
	return status;
}

Status test_my_string_concat_returns_correct_size_after_concat(char* buffer, unsigned long length)
{
	MY_STRING hResult = NULL;
	MY_STRING hAppend = NULL;
	Status status;
	
	hResult = my_string_init_c_string("hi");
	hAppend = my_string_init_c_string("hello");

	my_string_concat(hResult, hAppend);

	if (my_string_get_size(hResult) != 7)
	{
		status = FAILURE;
		printf("Expected to get size 7 after concatenating two strings but got different size\n");
		strncpy(buffer, "test_my_string_concat_returns_correct_size_after_concat\n"
				"Did not have correct size after concatenating two string\n", length);
	}

	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_my_string_concat_returns_correct_size_after_concat\n", length);
	}

	my_string_destroy(&hResult);
	my_string_destroy(&hAppend);
	return status;
}

Status test_my_string_empty_returns_TRUE_for_empty_string(char* buffer, unsigned long length)
{
	MY_STRING hString = NULL;
	Status status;

	hString = my_string_init_default();

	if (!my_string_empty(hString))
	{
		status = FAILURE;
		printf("Expected to return TRUE after checking an empty string but got something else\n");
		strncpy(buffer, "test_my_string_empty_returns_TRUE_for_empty_string\n"
				"Did not return TRUE after checking an empty string\n", length);
	}

	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_my_string_empty_returns_TRUE_for_empty_string\n", length);
	}

	my_string_destroy(&hString);
	return status;
}


