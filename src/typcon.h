#ifndef _TYPCON_H_
#define _TYPCON_H_

#include <stdbool.h>

static const int DEFAULT_LEN = 10;
static const signed char* DEFAULT_ALPH = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_!@#$";

typedef struct _flags {
	signed char* alph;
	int len;
} Flags;

typedef struct string {
	signed char* str;
	size_t len;
	bool free;
} Str;

#endif
