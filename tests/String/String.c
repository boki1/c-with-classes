//
// Created by boki on 8/31/20.
//

#include <stdarg.h>
#include <string.h>
#include <assert.h>
#include "String.h"
#include "../../Class/Class.h"
#include "../../Class/new.h"

struct String {
	const void *class;
	char *buffer;
};

const void *String_ctor (const void *_self, va_list ap)
{
  struct String *const self = (void *) _self;
  const char *str = va_arg(ap, const char *);
  self->buffer = (char *) malloc (strlen (str) + sizeof "");
  strcpy (self->buffer, str);
  return self;
}

const void *String_dtor (const void *_self)
{
  struct String *self = (void *) _self;
  free (self->buffer), self->buffer = 0;
  free (self);
  return 0;
}

const void *String_copy (const void *_self)
{
  struct String *const self = (void *) _self;
  return new (String, self->buffer);
}

const void *String_mov (const void *_self, const void *_other)
{
  struct String *const self = (void *) _self;
  struct String *other = (void *) _other;

  self->buffer = realloc (self->buffer, strlen (other->buffer) + sizeof "");
  strcpy (self->buffer, other->buffer);

  /* Move, so destroy other */
  other = (void *) String_dtor (other);
  assert(other == 0);

  return self;
}

_Bool String_equals (const void *_self, const void *_other)
{
  struct String *const self = (void *) _self;
  struct String *other = (void *) _other;

  if (other->class != String)
	return 1;
  return strcmp (self->buffer, other->buffer);
}

/* TODO
 * Design issue:
 * free() has to be called w/ the result as an argument */
const char *String_repr (const void *Self)
{
  const struct String *const self = (void *) Self;
  char *str = malloc (strlen (self->buffer) + sizeof "");
  strcpy (str, self->buffer);
  return str;
}

void
String_index (const void *Self, unsigned i)
{
  const struct String *const self = (void *) Self;
  struct Class *const class = (void *) self->class;

  /* TODO
   * Add thread-safety to this solution or think of something else. */
  class->result = (void *) &self->buffer[i];
}

void	TO_FREE
String_substring (const void *Self, unsigned i, unsigned j)
{
  const struct String *const self = (void *) Self;
  struct Class *const class = (void *) self->class;

  char temp = self->buffer[j];
  self->buffer[j] = 0;
  void *res = new(String, self->buffer[i]);
  self->buffer[j] = temp;
  class->result = res;
}

void	TO_FREE
String_length (const void *Self)
{
  const struct String *const self = (void *) Self;
  struct Class *const class = (void *) self->class;

  size_t *len = malloc(sizeof(size_t));
  *len = strlen(self->buffer);
  class->result = len;
}

void
String_set (const void *Self, const char *v)
{
  struct String *const self = (void *) Self;

  self->buffer = realloc(self->buffer, strlen(v));
  strcpy(self->buffer, v);
}

void
String_invoke (const void *Self, int method, va_list args)
{
  const struct Class *const *self = (void *) Self;
  Type_methods m = ((*self)->methods);
  Type_method f = (*m)[method];
  f(args);
}

//void (*methods[]) () =
//	{
//		[SUBSTR] = String_substring,
//		[INDEX] = String_index,
//		[LENGTH] = String_length,
//		[SET] = String_set
//	};

static const struct Class StringClass = {
	.size = sizeof (struct String),
	.dtor = String_dtor,
	.ctor = String_ctor,
	.copy = String_copy,
	.move = String_mov,
	.equal = String_equals,
	.repr = String_repr,
	.invoke = String_invoke,
//	.index = (int *) &function_index,
//	.methods = methods,
	.result = 0
};

const void *String = &StringClass;