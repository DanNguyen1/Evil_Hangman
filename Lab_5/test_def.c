#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "unit_test.h"

Status test_init_default_returns_nonNULL(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();

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

Status test_get_size_on_init_default_returns_0(char* buffer, int length)
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

Status test_get_capacity_on_init_default_returns_7(char* buffer, int length)
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

Status test_init_c_string_helloworld_returns_nonNULL(char* buffer, int length)
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
Status test_get_size_on_init_c_string_helloworld_returns_10(char* buffer, int length)
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

Status test_get_capacity_on_init_c_string_helloworld_returns_11(char* buffer, int length)
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


