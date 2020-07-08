#ifndef AMBIENT_H
#define AMBIENT_H

#include <stdarg.h>
#include <stddef.h>

// Out of the box definitions
int snprintf(char* s, size_t n, const char* format, ...);
int vsnprintf(char* s, size_t n, const char* format, va_list arg);

#endif  // AMBIENT_H
