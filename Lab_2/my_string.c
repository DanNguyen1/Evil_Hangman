#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

typedef struct string{
	int size;
	int capacity;
	char* data;
}My_string;

/**
 * initialize a string with the default capacity(7) and size(0)
 *
 *@return
 *	reutrn the structure typecasted to the opaque object
 */
MY_STRING my_string_init_default(void)
{
	My_string* pMy_string;

	pMy_string = (My_string*)malloc(sizeof(My_string));
	if (pMy_string != NULL)
	{
		pMy_string->size = 0;
		pMy_string->capacity = 7;
		pMy_string->data = (char*)malloc(sizeof(char) * pMy_string->capacity);
		if(pMy_string->data == NULL){
			free(pMy_string);
			pMy_string = NULL;
		}
	}

	return (MY_STRING)pMy_string;
}

/**
 * initialize an object with the parameters defined by the given c_string
 *
 * @param c_string
 * 	c_string passed to function
 *
 * @return 
 * 	return structure typecasted to opaque object
 */
MY_STRING my_string_init_c_string(const char* c_string)
{
	//get length of string
	int len = 0;
	while(c_string[len] != '\0')
	{
		++len;
	}

	My_string* pMy_string;

	pMy_string = (My_string*)malloc(sizeof(My_string));
	if (pMy_string != NULL)
	{
		pMy_string->size = len;
		pMy_string->capacity = len + 1;
		pMy_string->data = (char*)malloc(sizeof(char) * pMy_string->capacity);
		if(pMy_string->data == NULL) //if malloc above fails
		{
			free(pMy_string);
			pMy_string = NULL;
		}
		//copy c-string to array in objecct
		else
		{
			for(int i = 0; i < pMy_string->capacity; ++i)
			{
				pMy_string->data[i] = c_string[i];
			}
		}	
	}
	return (MY_STRING)pMy_string;
}

/**
 * get the capacity of the array which holds the c-string in the object
 *
 * @param hMy_string
 * 	handle to object
 *
 * @return
 * 	return capacity of array
 */
int my_string_get_capacity(MY_STRING hMy_string)
{
	My_string* pMy_string = (My_string*)hMy_string;
	return pMy_string->capacity;
}

/**
 * get the size of the c-string held in the object
 *
 * @param hMy_string
 * 	handle to opaque object
 *
 * @return
 * 	return size of c-string
 */
int my_string_get_size(MY_STRING hMy_string){
	My_string* pMy_string = (My_string*)hMy_string;
	return pMy_string->size;
}

/**
 * compare the size of two c-strings
 *
 * @param hLeft_string
 * 	handle to object that contains the first(left) string to be compared
 *
 * @param hRight_string
 * 	handle to object that contains the second(right) sring to be compared
 *
 * @return
 * 	return the difference between sizes of the c-string (does not include null character)
 */
int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
	My_string* pLeft_string = (My_string*)hLeft_string;
	My_string* pRight_string = (My_string*)hRight_string;

	return pLeft_string->size - pRight_string->size;
}

/**
 * free the memory that holds the c-string in the object and the object itself
 *
 * @param phMy_string
 * 	address of object handle
 */
void my_string_destroy(MY_STRING* phMy_string){
	My_string* pMy_string = (My_string*)*phMy_string;
	free(pMy_string->data);
	free(pMy_string);
	*phMy_string = NULL;
}
