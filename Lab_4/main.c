#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

int main(int argc, char* argv[])
{
	MY_STRING hMy_string = NULL;
	MY_STRING hMy_string2 = NULL;
	char* str;
	FILE* fp;
	int i;

	hMy_string = my_string_init_default();
	hMy_string2 = my_string_init_default();
	fp = fopen("simple.txt", "r");

	/*
	while (my_string_extraction(hMy_string,fp))
	{
		i = 0;
		str = my_string_c_str(hMy_string);

		while (str[i] != '\0')
		{	
			printf("%c", str[i]);
			++i;
		}	

		printf("\n");
	}
	*/

	my_string_extraction(hMy_string, fp);
	str = my_string_c_str(hMy_string);

	i = 0;

	while (str[i] != '\0')
	{
		printf("%c", str[i]);
		++i;
	}
	printf("\n");

	my_string_extraction(hMy_string2, fp);
	str = my_string_c_str(hMy_string2);

	i = 0;

	while (str[i] != '\0')
	{
		printf("%c", str[i]);
		++i;
	}
	printf("\n");

	my_string_concat(hMy_string, hMy_string2);
	str = my_string_c_str(hMy_string);

	i = 0;

	while (str[i] != '\0')
	{
		printf("%c", str[i]);
		++i;
	}

	printf("\n");

	my_string_destroy(&hMy_string);
	my_string_destroy(&hMy_string2);
	fclose(fp);

	return 0;
}
