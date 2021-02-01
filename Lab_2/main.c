#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

int main(int argc, char* argv[])
{
	MY_STRING hMy_string = NULL;

	MY_STRING hMy_string2 = NULL;

	hMy_string = my_string_init_c_string("hello");

	hMy_string2 = my_string_init_c_string("hello");

	int capacity = my_string_get_capacity(hMy_string);

	int size = my_string_get_size(hMy_string);

	printf("capacity: %d\n", capacity);

	printf("size: %d\n", size);

	printf("compare: %d\n", my_string_compare(hMy_string, hMy_string2));

	my_string_destroy(&hMy_string);

	my_string_destroy(&hMy_string2);

	return 0;
}
