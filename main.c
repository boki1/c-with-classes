#include <stdio.h>
#include <stdlib.h>

#include "String/String.h"
#include "Class/new.h"

int main ()
{
  void *a = new (String, "aAA");
  void *b = new (String, "b");
  void *aa = clone (a);

  printf ("a size == %lu\n", (unsigned long) size (a));
  if (equals (a, b))
	puts ("ok");

  if (!equals (a, aa))
	puts ("ok");

  if (a != aa)
	puts ("ok");

  char *r = repr (a);
  printf ("%s\n");
  free (r);

//  invoke(a, C_METHOD(String, SUBSTR), 1, 3);

  delete (a);
  delete (aa);
  delete (b);

  return 0;
}
