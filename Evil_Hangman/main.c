#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "status.h"
#include "my_string.h"
#include "generic_vector.h"
#include "avl_tree.h"

#define MAX_WORD_SIZE 30

int get_word_length(void);
int get_num_guesses(void);
int get_guess(MY_STRING guessed_letters, char *guess, GENERIC_VECTOR current_family);
Boolean get_running_total(void);
Status generate_first_key(MY_STRING key, int word_length);
void input(MY_STRING read);
void print_guessed_letters(MY_STRING guessed_letters);
void clear_keyboard_buffer(void);

int main(void)
{
	GENERIC_VECTOR dictionary[30]; //dictionary
	GENERIC_VECTOR current_family = NULL; //current family of words
	Node* new_word_family = NULL; //node to get data for new family
	MY_STRING hString = NULL; //My_string object for initial dictionary creation
	MY_STRING current_key = NULL; //current key for get_word_key_value
	MY_STRING new_key = NULL; //new key from get_word_key_value
	MY_STRING guessed_letters = NULL;
	Node* root = NULL; //AVL tree;
	FILE* dict_txt;
	int i;
	int word_length;
	int num_guesses;
	int check;
	Boolean running_total;
	char play_again;
	char guess;

	// dictionary creation
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

	// main game loop
	do
	{
		word_length = get_word_length();
		while (generic_vector_get_size(dictionary[word_length]) <= 0)
		{
			printf("Sorry, there are no words in the dictionary with this length.\n");
			word_length = get_word_length();
		}

		num_guesses = get_num_guesses();

		running_total = get_running_total();

		clear_keyboard_buffer();

		printf("\n");

		current_key = my_string_init_default();
		
		// game initialization
		if(!generate_first_key(current_key, word_length))
		{
			printf("Unable to generate first key, memory problem?\n");
			exit(1);
		}
		
		new_key = my_string_init_default();

		generic_vector_assignment(&current_family, dictionary[word_length]);

		guessed_letters = my_string_init_default();

		// guess loop
		while (num_guesses > 0)
		{
			printf("You have %d guesses left.\n", num_guesses);
			printf("Used letters:");
			print_guessed_letters(guessed_letters);
			printf("\n");
			printf("Word: %s\n", my_string_c_str(current_key));

			printf("Enter guess: ");
			check = get_guess(guessed_letters, &guess, current_family);
			
			if (check == 1)
			{
				for(i = 0; i < generic_vector_get_size(current_family); ++i)
				{
					get_word_key_value(current_key, new_key, generic_vector_at(current_family, i), guess);
					tree_insert(&root, generic_vector_at(current_family, i), new_key);
				}

				if (running_total)
				{
					print_inorder_traversal(root);
				}

				new_word_family = get_largest_family(root);

				if (my_string_compare(current_key, get_key(new_word_family)) == 0)
				{
					printf("I'm sorry, there were no %c's in this word.\n", guess);
					num_guesses--;
				}

				generic_vector_assignment(&current_family, get_word_family(new_word_family));
				my_string_assignment(&current_key, get_key(new_word_family));
			
				if (running_total)
				{
					printf("The computer has %d possibilities remaining.\n", generic_vector_get_size(current_family));
				}

				tree_destroy(&root);
			}

			else if (check == 2)
			{
				printf("You have already guessed every letter.\n");
				if (running_total)
				{
					printf("The computer has %d possibilities remaning. \n", generic_vector_get_size(current_family));
				}
			}
			
			else if (check < 0)
			{
				printf("Sorry, that word is incorrect.\n");
				num_guesses--;
			}
			else if (check == 0)
			{
				printf("That is the correct word!\n");
				break;
			}

			printf("\n");

		}

		if (num_guesses > 0)
		{
			printf("Congratulations!\n");
		}

		generic_vector_destroy(&current_family); //might cause problems, does not check for every element........

		my_string_destroy(&current_key);

		my_string_destroy(&new_key);

		my_string_destroy(&guessed_letters);
		
		//play again prompt
		printf("Would you like to play again? (y\\n)\n");
		scanf(" %c", &play_again);

	} while (play_again == 'y');

	//clean-up     
	for(i = 0; i < MAX_WORD_SIZE; ++i)
        {
                generic_vector_destroy(&(dictionary[i]));
        }

	my_string_destroy(&hString);

	fclose(dict_txt);

	return 0;
}

int get_word_length(void)
{
	int word_length;

	printf("Please choose a word length from 0 to 29:\n");
	scanf("%d", &word_length);


	while(word_length < 0 || word_length > 29)
	{
		printf("Please choose a word length from 0 to 29:\n");
		scanf("%d", &word_length);
	}

	return word_length;
}

int get_num_guesses(void)
{
	int num_guesses;

        printf("How many guesses would you like to have?\n");
        scanf("%d", &num_guesses);


	while (num_guesses <= 0)
	{
		printf("How many guesses would you like to have?\n");
		scanf("%d", &num_guesses);
	}

        return num_guesses;
}

int get_guess(MY_STRING guessed_letters, char *guess, GENERIC_VECTOR current_family)
{
	MY_STRING read = my_string_init_default();
	MY_STRING compare = NULL;
	int i;
	char ch;
	
	input(read);

	if (my_string_get_size(read) == 1 && my_string_get_size(guessed_letters) < 26)
	{
		i = 0;
		while(i < my_string_get_size(guessed_letters))
		{
			if (*(my_string_at(read, 0)) == *(my_string_at(guessed_letters, i)))
			{	
				printf("You have already guessed that letter. Please enter another letter:\n");
				my_string_pop_back(read);
                		scanf(" %c", &ch);
				my_string_push_back(read, ch);
				i = 0;
			}
			else
			{
				++i;
			}
		}

		my_string_push_back(guessed_letters, *(my_string_at(read, 0)));
		*guess = *(my_string_at(read, 0));
		my_string_destroy(&read);
		return 1;
	}

	else if (my_string_get_size(read) == 1 && my_string_get_size(guessed_letters) >= 26)
	{
		return 2;

	}

	else
	{
		if (generic_vector_get_size(current_family) == 1)
		{
			compare = generic_vector_at(current_family, 0);
			if (my_string_compare(read, compare) == 0)
			{
				my_string_destroy(&read);
				return 0;
			}
			else
			{
				my_string_destroy(&read);
				return -1;
			}
		}
		else
		{
			my_string_destroy(&read);
			return -1;
		}
	}
}


Boolean get_running_total(void)
{
	char ans;

	printf("Would you like to print a running total of words left? (y\\n)\n");
	scanf(" %c", &ans);

	while (ans != 'y' && ans != 'n')
	{
		printf("Would you like to print a running total of words left? (y\\n)\n");
		scanf(" %c", &ans);
	}

	return (ans == 'y' ? TRUE : FALSE);
}

Status generate_first_key(MY_STRING key, int word_length)
{
	int i;

	if (key == NULL)
	{
		return FAILURE;
	}
	
	for(i = 0; i < word_length; ++i)
	{
		if(!my_string_push_back(key, '-'))
		{
			return FAILURE;
		}
	}

	return SUCCESS;
}

void input(MY_STRING read)
{
	char ch;

	do
        {
                scanf("%c", &ch);
                if (ch == '\n') {
                        break;
                }
                my_string_push_back(read, ch);
        } while (ch != '\n');
}

void print_guessed_letters(MY_STRING guessed_letters)
{
	int i;

	printf(" ");

	for(i = 0; i < my_string_get_size(guessed_letters); ++i)
	{
		printf("%c ", *(my_string_at(guessed_letters, i)));
	}
}

void clear_keyboard_buffer(void)
{
	char c;
	int noc;
	noc = scanf("%c", &c);
	while (noc == 1 && c != '\n')
	{
		noc = scanf("%c", &c);
	}
}

//***MISC STUFF FROM TESTING FOR REFERENCE***
//
        /*
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
	*/
