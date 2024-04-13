#ifndef TMPL_ERF_MEDIUM_LDOUBLE_H
#define TMPL_ERF_MEDIUM_LDOUBLE_H

#include <libtmpl/include/tmpl_config.h>

#if TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_64_BIT
#include "tmpl_erf_medium_ldouble_64_bit_double.h"
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_128_BIT
#include "tmpl_erf_medium_ldouble_128_bit_quadruple.h"
#elif TMPL_LDOUBLE_TYPE == TMPL_LDOUBLE_DOUBLEDOUBLE
#include "tmpl_erf_medium_ldouble_128_bit_double_double.h"
#else
#include "tmpl_erf_medium_ldouble_80_bit_extended.h"
#endif

#endif
