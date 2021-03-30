#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "generic_vector.h"
#include "avl_tree.h"

#define MAX_WORD_SIZE 30

int main(void)
{
	GENERIC_VECTOR dictionary[30];
	GENERIC_VECTOR current_family = NULL;
	Node* new_word_family = NULL;
	MY_STRING hString = NULL;
	MY_STRING current_key = NULL;
	MY_STRING new_key = NULL;
	Node* root = NULL;

	FILE* dict_txt;
	int i;

	for(i = 0; i < MAX_WORD_SIZE; ++i)
	{
		dictionary[i] = generic_vector_init_default(my_string_assignment, my_string_destroy);
	}

	dict_txt = fopen("../dictionary.txt", "r");
	hString = my_string_init_default();

	while(my_string_extraction(hString, dict_txt))
	{
		generic_vector_push_back(dictionary[my_string_get_size(hString)], hString);
	}


	current_key = my_string_init_c_string("-------");

        new_key = my_string_init_default();

	for(i = 0; i < generic_vector_get_size(dictionary[7]); ++i)
	{
		get_word_key_value(current_key, new_key, generic_vector_at(dictionary[7], i), 'z');
		tree_insert(&root, generic_vector_at(dictionary[7], i), new_key);
	}
		
	printf("**inorder**\n");
	print_inorder_traversal(root);
	printf("\n**END inorder**\n");

	new_word_family = get_largest_family(root);

	generic_vector_assignment(&current_family, get_word_family(new_word_family));
	my_string_assignment(&current_key, get_key(new_word_family));

	tree_destroy(&root);

	printf("key of new largest family is: %s\n", my_string_c_str(current_key));
	printf("size of new largest family is: %d\n", generic_vector_get_size(current_family)); 

	for(i = 0; i < MAX_WORD_SIZE; ++i)
	{
		generic_vector_destroy(&(dictionary[i]));
	}

	fclose(dict_txt);

	generic_vector_destroy(&current_family);

	my_string_destroy(&hString);

	my_string_destroy(&current_key);

	my_string_destroy(&new_key);	

	return 0;
}
