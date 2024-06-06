#ifndef MSL_C_STRING_H
#define MSL_C_STRING_H

#include "../dolphin/gctypes.h"
#include "../addrs.h"

typedef char (*_strcpy)(char *dest, const char *source);
typedef char (*_strcat)(char *dst, const char *src);
typedef size_t (*_strlen)(const char *str);
typedef int (*_sprintf)(char *str, const char *string, ...);
typedef int (*_printf)(const char *string, ...);
typedef int (*_snprintf)(char *s, size_t n, const char *format, ...);
typedef char (*_strncpy) (char *destination, const char *source, size_t num);
typedef int (*_strcmp)(const char* str1, const char* str2);
typedef void* (*tww_memcpy_t)(void* dest, void* src, size_t size);

#define tww_strlen ((_strlen)tww_strlen_addr)
#define tww_printf ((_printf)tww_printf_addr)
#define tww_sprintf ((_sprintf)tww_sprintf_addr)
#define tww_snprintf ((_snprintf)tww_snprintf_addr)
#define tww_strcat ((_strcat)tww_strcat_addr)
#define tww_strncpy ((_strncpy)tww_strncpy_addr)
#define tww_strcpy ((_strcpy)tww_strcpy_addr)
#define tww_strcmp ((_strcmp)tww_strcmp_addr)

#define tww_memcpy ((tww_memcpy_t)tww_memcpy_addr)

#endif /* MSL_C_STRING_H */
