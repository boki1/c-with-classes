//
// Created by boki on 9/3/20.
//

#include <assert.h>
#include <string.h>

#include "Class.h"

/* Works only with pointers a.k.a. p has to be allocated on the heap w/ malloc */
#define RETURN_AS_METHOD(p, t) \
  if (t == Pointer) { /* the approach used otherwise won't work with pointers */ }                             \
  else { void *pp = malloc(sizeof(p)); \
	memcpy(pp, &p, sizeof(p));    \
	struct return_type _ret = { .retval = pp, .class_type = t }; \
	return _ret;                                                \
  }

/* Extract the actual retval from the return_type struct */
#define TRANSLATE_RET(p) \
    (typeof((v)->class_type))    (v->value)

struct return_type {
	void *retval;
	void *class_type;
};

typedef struct return_type *(*func_dt) ();

struct Method {
	char *symbol;
	func_dt func;
	long flags;
};

struct Method *new_method (const char *symbol, func_dt f, ...)
{
  // Handle ... to work for private methods etc.
  struct Method *m = malloc (sizeof (struct Method));
  assert(m);
  m->symbol = malloc (strlen (symbol) + sizeof (""));
  assert(m->symbol);
  strcpy (m->symbol, symbol);
  m->flags = 0;
  return m;
}

void *
put_method (const void *obj, struct Method *m)
{
  struct Class *_class = (void *) obj;
  void *temp = realloc (_class->methods, _class->methods_count * sizeof (struct Method *) + 1);
  if (!temp)
	{
	  assert(0);
	}
  _class->methods_count++;
  _class->methods = temp;
  _class->methods[_class->methods_count - 1] = m;

  return _class;
}

void init_methods (const void *obj)
{
  (void) obj;
}

void
destroy_methods (const void *obj)
{
  struct Class *_class = (void *) obj;
  void *p;
  unsigned i;
  for (i = 0; i < _class->methods_count - 1; ++i)
	{
	  p = _class->methods + 1;
	  _class->methods += 1;
	  free (p);
	}
  free (_class->methods);
}
