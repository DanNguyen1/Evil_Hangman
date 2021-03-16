#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "generic_vector.h"

#define MAX_WORD_SIZE 30

int main(void)
{
	GENERIC_VECTOR dictionary[30];
	MY_STRING hString = NULL;
	FILE* dict_txt;
	int i;

	hString = my_string_init_default();

	for(i = 0; i < MAX_WORD_SIZE; ++i)
	{
		dictionary[i] = generic_vector_init_default(my_string_assignment, my_string_destroy);
	}

	dict_txt = fopen("../dictionary.txt", "r");

	while(my_string_extraction(hString, dict_txt))
	{
		generic_vector_push_back(dictionary[my_string_get_size(hString)], hString);
	}	

	for(i = 0; i < MAX_WORD_SIZE; ++i)
	{
		generic_vector_destroy(&(dictionary[i]));
	}

	fclose(dict_txt);

	my_string_destroy(&hString);

	return 0;
}
