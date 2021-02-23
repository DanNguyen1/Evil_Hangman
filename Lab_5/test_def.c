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


