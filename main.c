#include "stringObj.h"
#include <stdio.h>

int main(){

  String * test = str_new("This is a simple C string");

  printf("%s\n", test->str);

  str_free(test);
  return 0;

}

