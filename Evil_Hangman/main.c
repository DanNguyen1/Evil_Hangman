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

	printf("word size is 0\n"
			"\texpected 0 words and got %d words\n", generic_vector_get_size(dictionary[0]));
        printf("word size is 1\n"
                        "\texpected 0 words and got %d words\n", generic_vector_get_size(dictionary[1]));
        printf("word size is 2\n"
                        "\texpected 94 words and got %d words\n", generic_vector_get_size(dictionary[2]));
	printf("\tThe 0 word is %s\n", my_string_c_str(generic_vector_at(dictionary[2], 0)));
	printf("\tThe 93 word is %s\n", my_string_c_str(generic_vector_at(dictionary[2], 93)));
        printf("word size is 3\n"
                        "\texpected 962 words and got %d words\n", generic_vector_get_size(dictionary[3]));
	printf("\tThe 0 word is %s\n", my_string_c_str(generic_vector_at(dictionary[3], 0)));
	printf("\tThe 961 word is %s\n", my_string_c_str(generic_vector_at(dictionary[3], 961)));
        printf("word size is 4\n"
                        "\texpected 3862 words and got %d words\n", generic_vector_get_size(dictionary[4]));
	printf("\tThe 0 word is %s\n", my_string_c_str(generic_vector_at(dictionary[4], 0)));
        printf("\tThe 3861 word is %s\n", my_string_c_str(generic_vector_at(dictionary[4], 3861)));
        printf("word size is 5\n"
                        "\texpected 8548 words and got %d words\n", generic_vector_get_size(dictionary[5]));
	printf("\tThe 0 word is %s\n", my_string_c_str(generic_vector_at(dictionary[5], 0)));
        printf("\tThe 8547 word is %s\n", my_string_c_str(generic_vector_at(dictionary[5], 8547)));
        printf("word size is 6\n"
                        "\texpected 14383 words and got %d words\n", generic_vector_get_size(dictionary[6]));
	printf("\tThe 0 word is %s\n", my_string_c_str(generic_vector_at(dictionary[6], 0)));
        printf("\tThe 14382 word is %s\n", my_string_c_str(generic_vector_at(dictionary[6], 14382)));

	MY_STRING word = my_string_init_c_string("hihello");

	MY_STRING current_key = my_string_init_c_string("-------");

	MY_STRING new_key = my_string_init_c_string("-------");

	get_word_key_value(current_key, new_key, word, 'h');

	my_string_assignment(&current_key, new_key);

	get_word_key_value(current_key, new_key, word, 'l');

	printf("%s\n", my_string_c_str(new_key));


	for(i = 0; i < MAX_WORD_SIZE; ++i)
	{
		generic_vector_destroy(&(dictionary[i]));
	}

	fclose(dict_txt);

	my_string_destroy(&hString);

	my_string_destroy(&word);

	my_string_destroy(&current_key);

	my_string_destroy(&new_key);
		

	return 0;
}
