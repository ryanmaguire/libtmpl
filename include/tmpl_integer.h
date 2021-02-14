
/*  include guard to prevent including this file twice.                       */
#ifndef __TMPL_INTEGER_H__
#define __TMPL_INTEGER_H__

#include <limits.h>

#if __TMPL_USE_C99_STDINT_H__ == 1
#include <stdint.h>

typedef uint32_t tmpl_uint32;
typedef uint64_t tmpl_uint64;

#else

#if USHRT_MAX == 0xFFFFFFFF
typedef short unsigned int tmpl_uint32;
#elif UINT_MAX == 0xFFFFFFFF
typedef unsigned int tmpl_uint32;
#elif ULONG_MAX == 0xFFFFFFFF
typedef long unsigned int tmpl_uint32;
#else
#error "libtmpl: No 32-bit integer type found."
#endif

#if USHRT_MAX == 0xFFFFFFFFFFFFFFFF
typedef short unsigned int tmpl_uint64;
#elif UINT_MAX == 0xFFFFFFFFFFFFFFFF
typedef unsigned int tmpl_uint64;
#elif ULONG_MAX == 0xFFFFFFFFFFFFFFFF
typedef long unsigned int tmpl_uint64;
#else
#error "libtmpl: No 64-bit integer type found."
#endif

#endif

#if USHRT_MAX == 0xFFFF
#define TMPL_SHORT_WIDTH 16

#elif USHRT_MAX == 0xFFFFFF
#define TMPL_SHORT_WIDTH 24

#elif USHRT_MAX == 0xFFFFFFFF
#define TMPL_SHORT_WIDTH 32

#else
#error "libtmpl: Unsupported short width (not 16, 24, or 32)."

#endif

#endif
/*  End of include guard.                                                     */

