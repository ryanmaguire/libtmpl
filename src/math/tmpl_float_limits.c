

#include <libtmpl/include/tmpl_math.h>
#include <float.h>

const float tmpl_Max_Float_Base_E = FLT_MAX_10_EXP * 2.302585093F;
const double tmpl_Max_Double_Base_E = DBL_MAX_10_EXP * 2.30258509299404568;
const long double
tmpl_Max_LDouble_Base_E = LDBL_MAX_10_EXP * 2.3025850929940456840179910L;

/*  Macros for the smallest values of float, double, and long double,         *
 *  respectively, that will not return 0 when exp(x) is computed.             */
const float tmpl_Min_Float_Base_E = FLT_MIN_10_EXP * 2.302585093F;
const double tmpl_Min_Double_Base_E = DBL_MIN_10_EXP  * 2.30258509299404568;
const long double
tmpl_Min_LDouble_Base_E = LDBL_MIN_10_EXP * .3025850929940456840179910L;
