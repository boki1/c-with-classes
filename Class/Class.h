//
// Created by boki on 8/31/20.
//

#ifndef _CLASS_H_
#define _CLASS_H_

#include <stdlib.h>

#define TO_FREE    // Method needs to allocate space for the return result. Therefore free() must be called on Class.result

#include "method_internal.h"

struct Class {
	size_t size;
	const void *(*ctor) ();
	const void *(*dtor) ();
	const void *(*copy) ();
	const void *(*move) ();
	_Bool (*equal) ();
	const char *(*repr) ();
	void (*invoke) ();

	class_methods methods;
	unsigned methods_count;

	void *result;
};

#endif //_CLASS_H_
