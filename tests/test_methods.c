//
// Created by boki on 9/4/20.
//

#include <stdio.h>
#include "../Class/Class.h"

METHOD_RETURN_TYPE test_int() {
  int a = 1000;
  RETURN_AS_METHOD(a, Integer);
}

METHOD_RETURN_TYPE test_local_str() {
  char *s = "asdf";
  RETURN_AS_METHOD(s, Other);
}

METHOD_RETURN_TYPE test_ptr_str(char *s)
{
  *s = 'G';
  RETURN_AS_METHOD(s, Pointer);
}

int main(int argc, const char *const *argv) {
  METHOD_RETURN_TYPE a = test_int();
  int a_return = EXTRACT_RETURN(a, int);
  free(a.retval);
  printf("%d\n", a_return);

  METHOD_RETURN_TYPE local_s = test_local_str();
  const char *local_str_return = EXTRACT_RETURN(local_s, const char *);
  free(local_s.retval);
  printf("%s\n", local_str_return);

  char *s = malloc(strlen("ghjk") + sizeof "");
  strcpy(s, "ghjk");
  METHOD_RETURN_TYPE ptr_s = test_ptr_str(s);
  const char *str_return = EXTRACT_RETURN(ptr_s, const char *);
  printf("%s\n", str_return);
	// Note: no `free()`

  return 0;
}