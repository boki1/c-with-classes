//
// Created by boki on 9/3/20.
//

#ifndef _CLASS_TYPES_H_
#define _CLASS_TYPES_H_

//const signed char SignedCharClass = 0;
//const void *SignedChar = &SignedCharClass;
//const void *Char = &SignedCharClass;
//const unsigned char UnsignedCharClass = 0;
//const void *UnsignedChar = &UnsignedCharClass;

extern const void *Integer;
//const void *SignedInteger = &SignedIntegerClass;
//const unsigned int UnsignedIntegerClass = 0;
//const void *UnsignedInteger = &UnsignedIntegerClass;
//
//const float FloatClass = 0;
//const void *Float = &FloatClass;
//const double DoubleClass = 0;
//const void *Double = &DoubleClass;
//const long double LongDoubleClass = 0;
//const void *LongDouble = &LongDoubleClass;
//
extern const void *Void;
extern const void *Other;	// same as void
extern const void *Pointer;

inline _Bool
is_type(const void *var, const void *type_ptr)
{
  return var == type_ptr;
}



#endif //_CLASS_TYPES_H_
