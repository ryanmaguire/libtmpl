#include "tmppl_complex.hpp"

tmppl::complex tmppl::cos(tmppl::complex z)
{
    return tmppl::complex(tmpl_CDouble_Cos(z.data));
}

tmppl::complex tmppl::sin(tmppl::complex z)
{
    return tmppl::complex(tmpl_CDouble_Sin(z.data));
}

tmppl::complex tmppl::exp(tmppl::complex z)
{
    return tmppl::complex(tmpl_CDouble_Exp(z.data));
}


