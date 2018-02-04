#include <stdlib.h>
typedef struct {
    size_t length;
    char * str;
} String;
//Err if malloc returns null
void err_if_null_ptr(void * ptr);

//Allocates a new string with a given character array
String * str_new(char *inserted_str);

//Frees a string string struct
void str_free(String * str_struct);

//Returns a character at index i
char str_char_at(String * str_struct, size_t index);

//Sets a character at a certain index. Fails if index out of bounds
void str_set_char(String * str_struct, size_t index, char chr);

//Returns index of char. Returns -1 if chr not found
int str_indexOf(String * str_struct, char chr);


//Allocates a new string, concatonates both objs
String * str_concat(String * begin, String * end);

String * str_concat_lit(String * begin, char * end);

//Sub string from begin (inclusive) to end (exclusive)
String * str_substr(String * str_struct, size_t begin, size_t end);

//Prints the contents of the string struct. 
void str_print(String * str_struct);

//Returns 0 if the strings do not match, returns 1 if they do. 
int str_equals(String * str_struct1, String * str_struct2);

//Returns a newly allocated reverse string
String * str_reverse(String * str_struct);
