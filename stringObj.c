#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stringObj.h"

/*
*  About string lengths: The length of the string in the struct counts all characters except the null terminating character. 
*  Allocating memory is length+1 for the null terminator.
*/

/*
*  House keeping utilities. Functionalities include freeing Strings, and null pointer checks
*/

//Frees a string struct
void str_free(String * str_struct){ 
  free(str_struct->str);
  free(str_struct);
}
//Prints the contents of a string struct
void str_print(String * str_struct){
  printf("%s\n", str_struct->str);
}

//Exits if malloc returned a null ptr
void err_if_null_ptr(void * ptr){
 if(ptr == NULL){
   fprintf(stderr, "Error: Malloc or realloc returned null, out of memory\n");
   exit(1);
 }
}

/*
* Beginning the string library
*/

//Allocates a new string with a given character array
String * str_new(char *inserted_str){
   size_t length = strlen(inserted_str);

   String * new_str = (String *) malloc(sizeof(String));
   //Set initial length
   new_str->length = length;

   //Allocate memory for length + 1 for null terminator
   new_str->str = (char *) malloc((length+1)*sizeof(char));

   //Copy inserted string over
   strncpy(new_str->str, inserted_str, length);
   new_str->str[length] = '\0';
   return new_str;
}

//Returns char at index
char str_char_at(String * str_struct, size_t index){
   if(index >= str_struct->length){
     fprintf(stderr, "Error in CHAR_AT: Array index out of bounds exception\n");
     exit(1);
     return 0;
   }else{
     return str_struct->str[index];
   }
}

//Changes a character at a specified index to the provided character
void str_set_char(String * str_struct, size_t index, char chr){
  if(index >= str_struct->length){
   fprintf(stderr, "Error in SET_CHAR: Array index out of bounds exception\n");
   exit(1);
  }
  
  str_struct->str[index] = chr;
}

//Allocates a new string which needs to be freed.
String * str_concat(String * begin, String * end){
  String * concatonated = (String *) malloc(sizeof(String));

  err_if_null_ptr(concatonated);
  //Increase length on concatonation
  concatonated->length = begin->length + end->length;

  concatonated->str = (char *) malloc(sizeof(char) * (begin->length + end->length + 1));

  err_if_null_ptr(concatonated->str);
  strncpy(concatonated->str, begin->str, begin->length+1);

  //Concatonation operation on the strings. 
  size_t i = begin->length;
  for(size_t j = 0; end->str[j]!='\0'; i++, j++){
     concatonated->str[i] = end->str[j];
  }
  concatonated->str[i] = '\0';

  return concatonated;
}
//Takes in a string literal, and allocates another str struct
String * str_concat_lit(String * begin, char * end){
	  size_t end_len = strlen(end);
	  if(end_len < 1){
	   return begin; 
	  }
          size_t begin_len = begin->length; 
	  String * concatonated = begin;
	  concatonated->length += end_len;
          //Increases size of char * in struct to make room for added string 
	  concatonated->str = (char *) realloc(concatonated->str, (concatonated->length + 1)*sizeof(char) );
          err_if_null_ptr(concatonated->str);
          for(size_t i = begin_len, j = 0; i < concatonated->length; i++){
	    concatonated->str[i] = end[j++];
          }
          concatonated->str[concatonated->length] = '\0';

  return concatonated;

}

String * str_substr(String * str_struct, size_t begin, size_t end){
  if(end > str_struct->length || begin > str_struct->length){  
   fprintf(stderr, "Error: array index out of bounds.\n");
   exit(1);
  }

  size_t new_len = end - begin;
  char substr[new_len+1];
  substr[new_len] = '\0';
  for(size_t i = begin, j = 0; i<end; i++){
    substr[j++] = str_struct->str[i];
  }
  return str_new(substr);
}

String * str_reverse(String * str_struct){
  String * new_str = (String *) malloc(sizeof(String));
  new_str->str = (char *) malloc(sizeof(char)*str_struct->length);
  size_t len = str_struct->length;
  size_t i = 0;
  do{
     new_str->str[i++] = str_struct->str[--len];
  }while(len > 0);
  return new_str;
}

/*This function returns 0 if the strings do not equal, and 1 if they do.*/
int str_equals(String * str_struct1, String * str_struct2){
  if(str_struct1->length != str_struct2->length){
    return 0;
  }
  int equals_flag = strcmp(str_struct1->str, str_struct2->str);
  if(equals_flag == 0){
    return 1;
  }else{
    return 0;
  }
}
//Finds index of character. Returns -1 if not found
int str_indexOf(String * str_struct, char chr){
  for(size_t i = 0; i < str_struct->length; i++){
    if(str_struct->str[i] == chr){
       return i;
    }
  }
  return -1;
}


