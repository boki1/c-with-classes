//
// Created by boki on 9/3/20.
//

#include "Class.h"

struct return_type
{
	void *value;
	void *class_type;
};

struct Method
{
	char *symbol;
	struct return_type * (*func)();

	long flags;
};
