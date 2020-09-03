//
// Created by boki on 8/31/20.
//

#ifndef _NEW_H_
#define _NEW_H_

#include <stdarg.h>
#include <stddef.h>

void *
new(const void *, ...);

void
delete(const void *);

void *
clone(const void *);

int
equals(const void *, const void *);

size_t
size(const void *);

const char *
repr(const void *);

void *
apply(const void *, void *(*)(const void *, va_list), ...);

void
invoke(const void *, int, ...);

#endif //_NEW_H_
