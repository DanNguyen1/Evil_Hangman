#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
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
		pMy_string->data = (char*)malloc(sizeof(char) * (unsigned long)pMy_string->capacity);
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

	My_string* pMy_string = (My_string*)malloc(sizeof(My_string)) ;

	//pMy_string = (My_string*)malloc(sizeof(My_string));
	if (pMy_string != NULL)
	{
		pMy_string->size = len;
		pMy_string->capacity = len + 1;
		pMy_string->data = (char*)malloc(sizeof(char) *(unsigned long)pMy_string->capacity);
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
 *      handle to object that contains the first(left) string to be compared
 *
 * @param hRight_string
 *      handle to object that contains the second(right) sring to be compared
 *
 * @return
 *      return the difference between lexiographically sizes of the c-string (does not include null character)
 */
int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
        int i = 0;
        int difference = 0;
        My_string* pLeft_string = (My_string*)hLeft_string;
        My_string* pRight_string = (My_string*)hRight_string;

        while(i < pLeft_string->size && i < pRight_string->size)
        {
                difference = (int)pLeft_string->data[i] - (int)pRight_string->data[i];
                if (difference != 0)
                {
                        break;
                }
                ++i;
        }

        if ((i == pLeft_string->size || i == pRight_string->size) && difference == 0)
        {
                if (pLeft_string->size > pRight_string->size)
                {
                        return 1;
                }
                else if (pLeft_string->size < pRight_string->size)
                {
                        return -1;
                }
                else
                {
                        return 0;
                }
        }

        else
        {
                if (difference < 0)
                {
                        return -1;
                }
                else
                {
                        return 1;
                }
        }
}

/**
 * push back one index of the c-string array
 *
 * @param hMy_string
 * 	handle to object that contains array to be pushed back
 *
 * @return
 * 	returns if string was successfully able to be popped back
 */
Status my_string_pop_back(MY_STRING hMy_string)
{
	My_string* pMy_string = (My_string*)hMy_string;
	if (pMy_string->size <= 0)
	{
		return FAILURE;
	}
	--pMy_string->size;
	return SUCCESS;
}

/**
 * allocate more capacity for the array in the object and place a character in the newly resized array
 *
 * @param hMy_string
 * 	valid My_string object handle
 *
 * @param ch
 * 	character to be placed into array after resize
 *
 * @return
 * 	returns if push back was successful in resizing and placing
 */
Status my_string_push_back(MY_STRING hMy_string, char ch)
{
	My_string* pMy_string = (My_string*)hMy_string;
	char* temp;
	int i;

	if (pMy_string->size >= pMy_string->capacity)
	{
		temp = (char*)malloc(sizeof(char) *(unsigned long)( pMy_string->capacity * 2));
		if (temp == NULL)
		{
			return FAILURE;
		}
		for (i = 0; i < pMy_string->size; ++i)
		{	
			temp[i] = pMy_string->data[i];
		}
		free(pMy_string->data);
		pMy_string->data = temp;
		pMy_string->capacity *= 2;
	}

	pMy_string->data[pMy_string->size] = ch;
	pMy_string->size++;

	return SUCCESS;
}

/**
 * get the address at a certain point in the array of a My_string object
 *
 * @param hMy_string
 * 	valid My_string object handle
 *
 * @param index
 * 	index of array to be found
 *
 * @return
 * 	return address of array at given index
 */
char* my_string_at(MY_STRING hMy_string, int index)
{
	My_string* pMy_string = (My_string*)hMy_string;

	if (index < 0 || index >= pMy_string->size)
	{
		return NULL;
	}

	return &(pMy_string->data[index]);
}

/**
 * return the array inside a My_string object as a NULL-terminated c-string
 *
 * @param hMy_string
 * 	valid My_string object handle
 *
 * @return
 * 	return the address of the beginning of the NUll-terminated c-string
 */
char* my_string_c_str(MY_STRING hMy_string)
{
	My_string* pMy_string = (My_string*)hMy_string;
	char* temp;
	int i;

	if (pMy_string->size < 0)
	{
		return NULL;
	}

	if (pMy_string->size >= pMy_string->capacity)
	{
		temp = (char*)malloc(sizeof(char) * (unsigned long)(pMy_string->capacity + 1));
		if (temp == NULL)
		{
			return NULL;
		}

		for (i = 0; i < pMy_string->size; ++i)
		{
			temp[i] = pMy_string->data[i];
		}
		free(pMy_string->data);
		pMy_string->data = temp;
		++pMy_string->capacity;
	}

	pMy_string->data[pMy_string->size] = '\0';

	return &pMy_string->data[0];
}

/**
 * extract a token from a file and places it into the array of a My_string object
 *
 * @param hMy_string
 * 	valid My_string object handle
 *
 * @param fp
 * 	valid file handle
 *
 * @return
 * 	returns if extraction was successful (SUCCESS) or failed (FAILURE)
 */
Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
	My_string* pMy_string = (My_string*)hMy_string;
	pMy_string->size = 0;

	char ch = (char)fgetc(fp);

	while(isspace(ch))
	{
		ch = (char)fgetc(fp);
	}

	if (ch != EOF)
	{
		pMy_string->data[pMy_string->size] = ch;
		++pMy_string->size;
	}
	
	while(ch != EOF && ch != ' ' && ch != '\n')
	{
		//if size>=capacity, free data and malloc a larger space
		if (pMy_string->size >= pMy_string->capacity)
		{
			ch = (char)fgetc(fp);
			if (ch == ' ' || ch == '\n' || ch == EOF)
			{
				break;
			}
			my_string_push_back(hMy_string, ch);	
		}
		else
		{
			ch = (char)fgetc(fp);
			if (ch == ' ' || ch == '\n' || ch == EOF)
			{
				break;
			}
			pMy_string->data[pMy_string->size] = ch;
			++pMy_string->size;
		}
	}
	
	if (pMy_string->size == 0)
	{
		return FAILURE;
	}

	ungetc(ch, fp);

	return SUCCESS;
}

/**
 * inserts string array of a My_string object into a given file
 *
 * @param hMy_string
 * 	valid My_string object handle
 *
 * @param fp
 * 	valid FILE handle which array will be inserted into
 *
 * @return
 * 	returns if insertion was successful (SUCCESS) or failed (FAILURE)
 */
Status my_string_insertion(MY_STRING hMy_string, FILE* fp)
{
	My_string* pMy_string = (My_string*)hMy_string;
	
	int i;

	if (pMy_string->size <= 0)
	{
		return FAILURE;
	}
	
	for(i = 0; i < pMy_string->size; ++i){
		fputc(pMy_string->data[i], fp);
	}

	return SUCCESS;
}

/**
 * concatenates two c-strings from two My_string object
 *
 * @param hResult
 * 	valid My_string object handle which second My_string object string will be concatenated to
 *
 * @param hAppend
 * 	valid My_string object handle which will be concatenated to the first string
 *
 * @return
 * 	returns if concatenation is succesful (SUCCESS) or failed (FAILURE)
 */
Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
	My_string* pResult = (My_string*)hResult;
	My_string* pAppend = (My_string*)hAppend;
	char* temp;
	int i, j;

	while(pResult->capacity <= pResult->size + pAppend->size)
	{
		temp = (char*)malloc(sizeof(char) * (unsigned long)(pResult->capacity * 2));
		if (temp == NULL)
		{
			return FAILURE;
		}
		for(i = 0; i < pResult->size; ++i)
		{
			temp[i] = pResult->data[i];
		}
		free(pResult->data);
		pResult->data = temp;
		pResult->capacity *= 2;
	}

	for (j = 0; j < pAppend->size; ++j)
	{
		pResult->data[pResult->size + j] = pAppend->data[j];
	}

	pResult->size += pAppend->size;

	return SUCCESS;
}

/**
 * checks if string located inside given My_string is empty
 *
 * @param hMy_string
 * 	valid My_string object handle
 *
 * @return
 * 	returns TRUE if string inside My_string object is empty and FALSE if string is not empty
 */
Boolean my_string_empty(MY_STRING hMy_string)
{
	My_string* pMy_string = (My_string*)hMy_string;

	return (Boolean)(pMy_string->size <= 0);
}

Status my_string_assignment(Item* pLeft, Item Right)
{
	My_string* Left = (My_string*)*pLeft;
	My_string* pRight = (My_string*)Right;
	My_string* temp;
	int i;

	if (*pLeft == NULL)
	{
		temp = (My_string*)malloc(sizeof(My_string));
		if (temp != NULL)
		{
			temp->size = pRight->size;
			temp->capacity = pRight->capacity;
			temp->data = (char*)malloc(sizeof(char) *(unsigned long)temp->capacity);
			if (NULL == temp->data)
			{
				free(temp);
				return FAILURE;
			}

			for(i = 0; i < pRight->size; ++i)
			{
				temp->data[i] = pRight->data[i];
			}	
			*pLeft = (Item)temp;
			return SUCCESS;
		}
		else
		{
			return FAILURE;
		}
	}

	else
	{
		Left->size = 0;
		
		for(i = 0; i < pRight->size; ++i)
		{
			my_string_push_back(*pLeft, pRight->data[i]);
		}
	}

	return SUCCESS;
}

/**
 * free the memory that holds the c-string in the object and the object itself
 *
 * @param pItem
 * 	address of object handle
 */
void my_string_destroy(Item* pItem){
	My_string* pMy_string = (My_string*)*pItem;
	free(pMy_string->data);
	free(pMy_string);
	*pItem = NULL;
}
