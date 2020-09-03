//
// Created by boki on 8/31/20.
//

#include <assert.h>
#include "new.h"
#include "Class.h"

void *
new (const void *Class, ...)
{
  struct Class *const class = (void *) Class;
  void *p = malloc (class->size);

  assert(p);

  *(struct Class **) p = class;

  if (class->ctor)
	{
	  va_list ap;
	  va_start(ap, Class);
	  p = (void *) class->ctor (p, &ap);
	  va_end(ap);
	}
  return p;
}

void
delete (const void *Class)
{
  const struct Class **p = (void *) Class;
  if (Class && p && (*p)->dtor)
	p = (void *) (*p)->dtor (Class);
  free (p);
}

void *
clone (const void *Class)
{
  const struct Class **p = (void *) Class;
  if (Class && p && (*p)->copy)
	{
	  return (void *) (*p)->copy (Class);
	}
  return 0;
}

int
equals (const void *Self, const void *Other)
{
  const struct Class **self = (void *) Self;
  const struct Class **other = (void *) Other;

  return (*self)->equal (self, other);
}

size_t
size (const void *Self)
{
  const struct Class **self = (void *) Self;
  return (*self)->size;
}

const char *	TO_FREE
repr (const void *Self)
{
  const struct Class **self = (void *) Self;
  return (*self)->repr (self);
}

void *
apply (const void *Self, void *(*method) (const void *, va_list), ...)
{
  const struct Class **self = (void *) Self;
  void *ret = 0;
  if (self && method)
	{
	  va_list ap;
	  va_start(ap, method);
	  ret = method (self, &ap);
	  va_end(ap);
	}
  return ret;
}

void
invoke(const void *Self, int i, ...)
{
  const struct Class * const *self = Self;
  if (self && (*self)->invoke)
	{
	  va_list l;
	  va_start(l, i);
	  (*self)->invoke(self, i, &l);
	  va_end(l);
	}
}