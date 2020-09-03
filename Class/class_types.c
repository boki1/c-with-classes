//
// Created by boki on 9/4/20.
//

#include "class_types.h"

const unsigned int SignedIntegerClass = 0;
const void *Integer = &SignedIntegerClass;

const void *Void = 0;
const void *Other = 0;
const void *Pointer = &Void;

extern inline _Bool
is_type(const void *var, const void *type_ptr);