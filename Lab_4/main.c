#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

int test1(void);
int test2(void);
int test3(void);

int main(void)
{
	printf("\n");
	printf("TEST 1 BEGIN\n");
	int test_1 = test1();

	if (test_1 == 0)
	{
		printf("Test failed.\n");
		exit(1);
	}
	else if (test_1 == 1)
	{
		printf("Test passed.\n");
		printf("TEST 1 FINISHED\n\n\n\n\n");
	}

	printf("TEST 2 BEGIN\n");
	int test_2 = test2();

	if (test_2 == 0)
	{
		printf("Test failed.\n");
		exit(1);
	}
	else if (test_2 == 1)
	{
		printf("Test passed.\n");
		printf("TEST 2 FINISHED\n\n\n\n\n");
	}

	printf("TEST 3 BEGIN\n");
	int test_3 = test3();

	if (test_3 == 0)
	{
		printf("Test failed.\n");
		exit(1);
	}
	else if (test_2 == 1)
	{
		printf("Test passed.\n");
		printf("TEST 3 FINISHED\n\n");
	}

	printf("ALL TESTS COMPLETE\n");

	return 0;
}

int test1(void)
{
	MY_STRING hMy_string = NULL;
	MY_STRING hMy_string2 = NULL;

	printf("initializing a my_string object with default values...\n\n");

	hMy_string = my_string_init_default();
	if (hMy_string == NULL)
	{
		return 0;
	}

	printf("printing default values of my_string object...\n");
	printf("size: %d\n", my_string_get_size(hMy_string));
	printf("capacity: %d\n\n", my_string_get_capacity(hMy_string));

	printf("destroying My_string object...\n\n");

	my_string_destroy(&hMy_string);

	printf("reinitilizating two my_string objects with words \"hi\" and \"hello\"...\n\n");

	hMy_string = my_string_init_c_string("hi");
	if (hMy_string == NULL)
	{
		return 0;
	}
	hMy_string2 = my_string_init_c_string("hello");
	if (hMy_string2 == NULL)
	{
		return 0;
	}

	printf("getting the size and capacity of the first My_string object...\n");

	printf("size of pMy_string->data: %d\n", my_string_get_size(hMy_string));

	printf("capacity of pMy_string->data: %d\n\n", my_string_get_capacity(hMy_string));

	printf("getting the difference of size between the two My_string object's strings...\n");

	printf("compare: %d\n\n", my_string_compare(hMy_string, hMy_string2));

	my_string_destroy(&hMy_string);
	my_string_destroy(&hMy_string2);
	hMy_string = NULL;
	hMy_string2 = NULL;

	return 1;
}

int test2(void)
{
	MY_STRING hMy_string = NULL;
	hMy_string = my_string_init_default();
	FILE* fp;

	fp = fopen("simple.txt", "r");

	printf("extracting string from file...\n\n");

	if (!(my_string_extraction(hMy_string, fp)))
	{
		return 0;
	}

	printf("placing string into stdout...\n");

	if (!(my_string_insertion(hMy_string, stdout)))
	{
		return 0;
	}

	printf("\n\n");

	my_string_destroy(&hMy_string);
	hMy_string = NULL;
	fclose(fp);

	return 1;
}

int test3(void)
{
	MY_STRING hMy_string = NULL;
	MY_STRING hMy_string2 = NULL;
	int i;

	printf("initializing two My_string objects with c-strings \"hi\" and \"hello\"...\n\n");

	hMy_string = my_string_init_c_string("hi");
	hMy_string2 = my_string_init_c_string("hello");

	printf("size before push back: %d\n", my_string_get_size(hMy_string));
	printf("capacity before push back: %d\n", my_string_get_capacity(hMy_string));
	printf("word before pushback: %s\n", my_string_c_str(hMy_string));
	printf("adding letter h to end of string...\n\n");
	my_string_push_back(hMy_string, 'h');

	printf("size after push back: %d\n", my_string_get_size(hMy_string));
	printf("capacity after push back: %d\n", my_string_get_capacity(hMy_string));
	printf("word after pushback: %s\n\n", my_string_c_str(hMy_string));
	
	printf("removing \'h\'...\n\n");
	my_string_pop_back(hMy_string);

	printf("concating \"hello\" to \"hi\"...\n");
	if (!(my_string_concat(hMy_string, hMy_string2)))
	{
		return 0;
	}
	printf("printing concat word...\n");
	printf("%s\n\n", my_string_c_str(hMy_string));

	printf("removing all letters from string using pop back...\n");
	for (i = 0; i < (int)my_string_get_size; ++i)
	{
		my_string_pop_back(hMy_string);
	}
	printf("making sure all letters from string are removed...\n");
	if (my_string_empty(hMy_string))
	{
		printf("string is empty!\n\n");
	}

	my_string_destroy(&hMy_string);
	my_string_destroy(&hMy_string2);

	hMy_string = NULL;
	hMy_string2 = NULL;

	return 1;
}

