#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "status.h"
#include "my_string.h"
#include "generic_vector.h"
#include "avl_tree.h"

#define MAX_WORD_SIZE 30

//type to check what player has inputted, and what the condition of the game is
typedef enum input_type
{
	letter, //basic letter
	all_letters_guessed, //if all letters are guessed and player tries to guess another letter
	incorrect_word, 
	correct_word 
} Input_type;

int get_word_length(void);
int get_num_guesses(void);
Input_type get_guess(MY_STRING guessed_letters, char* guess, GENERIC_VECTOR current_family);
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
	Input_type check;
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

	//partitioning dicitonary into generic vectors......
	while(my_string_extraction(hString, dict_txt))
	{
		generic_vector_push_back(dictionary[my_string_get_size(hString)], hString);
	}

	// main game loop
	do
	{
		//inital prompts (word length, number of guesses, debugging mode)
		word_length = get_word_length();
		while (generic_vector_get_size(dictionary[word_length]) <= 0)
		{
			clear_keyboard_buffer();
			printf("Sorry, there are no words in the dictionary with this length.\n");
			word_length = get_word_length();
		}

		num_guesses = get_num_guesses();

		running_total = get_running_total();

		clear_keyboard_buffer();

		printf("\n");

		current_key = my_string_init_default();
		
		// game initializations
		if(!generate_first_key(current_key, word_length))
		{
			printf("Unable to generate first key, memory problem?\n");
			exit(1);
		}
		
		new_key = my_string_init_default();

		generic_vector_assignment(&current_family, dictionary[word_length]);

		guessed_letters = my_string_init_default();

		// guessing loop
		while (num_guesses > 0)
		{
			printf("You have %d guesses left.\n", num_guesses);
			printf("Used letters:");
			print_guessed_letters(guessed_letters);
			printf("\n");
			printf("Word: %s\n", my_string_c_str(current_key));

			printf("Enter guess: ");
			check = get_guess(guessed_letters, &guess, current_family); //check is used to determine type of input player input and the condition of the input
			
			// guessing a letter
			if (check == letter)
			{
				for(i = 0; i < generic_vector_get_size(current_family); ++i)
				{
					get_word_key_value(current_key, new_key, generic_vector_at(current_family, i), guess);
					tree_insert(&root, generic_vector_at(current_family, i), new_key);
				}

				if (running_total) //print out list of keys if requested to at beginning of game
				{
					print_inorder_traversal(root);
				}

				new_word_family = get_largest_family(root); //get node for largest family

				if (my_string_compare(current_key, get_key(new_word_family)) == 0) //subtract number of guesses if key hasnt changed
				{
					printf("I'm sorry, there were no %c's in this word.\n", guess);
					num_guesses--;
				}

				generic_vector_assignment(&current_family, get_word_family(new_word_family)); //assign new family generic vector
				my_string_assignment(&current_key, get_key(new_word_family)); //assign new key
			
				if (running_total) //print out size of new family (current possibilties) if requested to at beginning of game
				{
					printf("The computer has %d possibilities remaining.\n", generic_vector_get_size(current_family));
				}

				tree_destroy(&root); //destroy current tree and get ready for next guess
			}

			// guessing a letter, but all letters are guessed
			else if (check == all_letters_guessed)
			{
				//does not subtract number of guesses, prompts another guess
				printf("You have already guessed every letter.\n");
				if (running_total)
				{
					printf("The computer has %d possibilities remaning. \n", generic_vector_get_size(current_family));
				}
			}
			
			//guessing a word, word family is greater than 1
			else if (check == incorrect_word)
			{
				printf("Sorry, that word is incorrect.\n");
				if (running_total)
				{
					printf("The computer has %d possibilities remaining. \n", generic_vector_get_size(current_family));
				}
				num_guesses--;
			}

			//guessing a word, word family only has 1 option and is correct word
			else if (check == correct_word)
			{
				printf("That is the correct word!\n");
				break;
			}

			printf("\n");

		}

		//player wins by guessing correct word
		if (num_guesses > 0)
		{
			printf("Congratulations!\n");
		}

		//player loses
		else
		{
			printf("The word was: %s\n", my_string_c_str(generic_vector_at(current_family, 0)));
		}

		//clean up for next game/end game
		generic_vector_destroy(&current_family); 

		my_string_destroy(&current_key);

		my_string_destroy(&new_key);

		my_string_destroy(&guessed_letters);
		
		//play again prompt
		printf("Would you like to play again? (y\\n)\n");
		scanf(" %c", &play_again);

	} while (play_again == 'y');

	//final clean-up for end game
	for(i = 0; i < MAX_WORD_SIZE; ++i)
        {
                generic_vector_destroy(&(dictionary[i]));
        }

	my_string_destroy(&hString);

	fclose(dict_txt);

	return 0;
}


/**
 * get the player's desired word length at beginning of game
 *
 * @return
 * 	return the player's desired word length, given that it is a valid length
 */
int get_word_length(void)
{
	int word_length;

	printf("Please choose a word length from 0 to 29:\n");
	scanf("%d", &word_length);


	while(word_length < 0 || word_length > 29)
	{
		clear_keyboard_buffer();
		printf("Please choose a word length from 0 to 29:\n");
		scanf("%d", &word_length);
	}

	return word_length;
}


/**
 * get player's desired number of guesses at beginning of game
 *
 * @return
 * 	return the player's desired number of guesses, given that it is a valid number
 */
int get_num_guesses(void)
{
	int num_guesses;

        printf("How many guesses would you like to have?\n");
        scanf("%d", &num_guesses);


	while (num_guesses <= 0)
	{
		clear_keyboard_buffer();
		printf("How many guesses would you like to have?\n");
		scanf("%d", &num_guesses);
	}

        return num_guesses;
}

/**
 * get player's guess, as well as determing type of guess player does
 *
 * @param guessed_letters
 * 	list of previous guessed letter
 *
 * @param guess
 * 	external guess variable used for validation in guessing loop of main
 *
 * @param current_family
 * 	current family of words used to determine if word is correctly guessed or not, as well as provide size of current family
 *
 * @return
 * 	returns type of input player inputs, having four conditions:
 * 		-letter is guessed, and there are still letters remaining
 *		-letter is guessed, but all letters have been guessed
 *		-word is guessed, but there is still more than 1 word left in the current family
 *		-word is guessed, there is 1 word left in the current family, and the guessed word is the same word
 */
Input_type get_guess(MY_STRING guessed_letters, char* guess, GENERIC_VECTOR current_family)
{
	MY_STRING read = my_string_init_default();
	MY_STRING compare = NULL;
	int i;
	char ch;
	
	//get input from user, helps with input validation
	input(read);

	//if player guessed a letter, and there are still letters to be guessed
	if (my_string_get_size(read) == 1 && my_string_get_size(guessed_letters) < 26)
	{
		i = 0;

		//checking to see if player has already guessed the letter
		while(i < my_string_get_size(guessed_letters))
		{
			//player has already guessed the letter
			if (*(my_string_at(read, 0)) == *(my_string_at(guessed_letters, i)))
			{	
				printf("You have already guessed that letter. Please enter another letter:\n");
				printf("Used letters: ");
				print_guessed_letters(guessed_letters);
				printf("\n");
				my_string_pop_back(read);
                		scanf(" %c", &ch);
				my_string_push_back(read, ch);
				i = 0;
				clear_keyboard_buffer();
			}
			else
			{
				++i;
			}
		}
		my_string_push_back(guessed_letters, *(my_string_at(read, 0))); //put guessed letter into list of already guessed letters
		*guess = *(my_string_at(read, 0)); //change external guess variable to guessed letters (for main to validate after function call)
		my_string_destroy(&read); 
		return letter;
	}

	//if player guessed a letter, but all letters have been guessed
	else if (my_string_get_size(read) == 1 && my_string_get_size(guessed_letters) >= 26)
	{
		my_string_destroy(&read);
		return all_letters_guessed;

	}

	//if player guesses a word
	else
	{
		//if there is only one word left in the family
		if (generic_vector_get_size(current_family) == 1)
		{
			compare = generic_vector_at(current_family, 0);
			//comparing the guessed word and the last word in family
			if (my_string_compare(read, compare) == 0)
			{
				my_string_destroy(&read);
				return correct_word; //player has guessed correct word
			}
			else
			{
				my_string_destroy(&read);
				return incorrect_word; //player has guessed incorrect word
			}
		}
		else
		{
			my_string_destroy(&read);
			//player will guess incorrect word if there is more than one word in the family, regardless
			return incorrect_word;
		}
	}
}

/**
 * initial game prompt to print list of keys and current possibilities (for debugging)
 *
 * @return
 * 	true or false depending on where user wants to turn on the option
 */
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

/**
 * initial generation of first key based on list of words of player chosen word length
 *
 * @param key
 * 	empty MY_STRING object, should be current_key object
 *
 * @param word_length
 * 	length of word that will generate size of key
 *
 * @return
 * 	returns SUCCESS if key was able to be generated. Otherwise, returns FAILURE
 */
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

/**
 * helper function to validate input in get_guess function
 *
 * @param read
 * 	MY_STRING object that any character read is placed into
 */
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

/**
 * prints list of guessed letters
 *
 * @param guessed_letters
 * 	MY_STRING object that is a list of player's guessed letters
 */
void print_guessed_letters(MY_STRING guessed_letters)
{
	int i;

	printf(" ");

	for(i = 0; i < my_string_get_size(guessed_letters); ++i)
	{
		printf("%c ", *(my_string_at(guessed_letters, i)));
	}
}

/**
 * clears unwanted input from buffer overflow
 *
 */
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
