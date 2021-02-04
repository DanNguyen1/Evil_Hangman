#ifndef MY_STRING_H
#define MY_STRING_H
typedef void * MY_STRING;
enum status{FAILURE, SUCCESS};
typedef enum status Status;

MY_STRING my_string_init_default(void);
MY_STRING my_string_init_c_string(const char* c_string);

int my_string_get_capacity(MY_STRING hMy_string);
int my_string_get_size(MY_STRING hMy_string);
int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string);

Status my_string_pop_back(MY_STRING hMy_string);
Status my_string_push_back(MY_STRING hMy_string, char ch);

Status my_string_extraction(MY_STRING hMy_string, FILE* fp);
Status my_string_insertion(MY_STRING hMy_string, FILE* fp);

void my_string_destroy(MY_STRING* phMy_string);

#endif//MY_STRING_H
