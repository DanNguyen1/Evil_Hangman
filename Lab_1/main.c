#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){
	int r = 20;
	int c = 30;

	int* arr = (int*)malloc(sizeof(int) * r * c);

	int i;
	int j;
	int count;

	for(i = 0; i < r; ++i){
		count = i;
		for(j = 0; j < c; ++j){
			*(arr + (i * c) + j) = count;
			++count;
		}
	}

	printf("Hello world! I have created a dynamic 2d-array of 20x30 integers!\n");

	for(i = 0; i < r; ++i){
		for(j = 0; j < c; ++j){
			printf("%3d", *(arr + (i * c) + j));
		}
		printf("\n");
	}

	free(arr);

	return 0;
}
