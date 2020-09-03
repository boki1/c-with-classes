//
// Created by boki on 8/31/20.
//

#ifndef _CLASS_H_
#define _CLASS_H_

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "class_types.h"
#include "method_internal.h"

struct Class {
  size_t size;
  const void *(*ctor)();
  const void *(*dtor)();
  const void *(*copy)();
  const void *(*move)();
  _Bool (*equal)();
  const char *(*repr)();
  void (*invoke)();

  class_methods methods;
  unsigned methods_count;

  void *result;
};

struct return_type {
  void *retval;
  void *class_type;
};

// Method needs to allocate space for the return result. Therefore free() must be called on Class.result
#define TO_FREE

#define METHOD_RETURN_TYPE    struct return_type

METHOD_RETURN_TYPE
method_return(void *v, const void *t, size_t s);

#define RETURN_AS_METHOD(v, t) \
	return method_return(&v, t, sizeof(v))

/* Extract the actual retval from the return_type struct */
#define EXTRACT_RETURN(p, t) \
	*((t *) ((p).retval))

struct return_type;

#endif //_CLASS_H_
