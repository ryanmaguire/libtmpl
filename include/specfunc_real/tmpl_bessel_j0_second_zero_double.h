#ifndef TMPL_BESSEL_J0_SECOND_ZERO_DOUBLE_H
#define TMPL_BESSEL_J0_SECOND_ZERO_DOUBLE_H

#include <libtmpl/include/tmpl_config.h>

/*  Coefficients for the numerator of the Remez rational approximation.       */
#define P00 (+3.4026480655836814182040706541832153222068224049489E-01)
#define P01 (-2.3038727542291233279399119518959889209791349351958E-02)
#define P02 (-4.7928864519998419949589548608694720214496193701649E-02)
#define P03 (+3.0108330814648854392470613126527331580755322686424E-03)
#define P04 (+1.4994327268912033364959197602150287192481395425054E-03)
#define P05 (-6.6226394862460035380496592403448849080851595428754E-05)
#define P06 (-1.7493438639023271141334258452329744594858884603136E-05)
#define P07 (+4.1667237756950095321157528294740159946546568792610E-07)
#define P08 (+7.3671870649266103017690803313476339957525843967159E-08)

/*  Coefficients for the denominator of the Remez rational approximation.     */
#define Q00 (+1.0000000000000000000000000000000000000000000000000E+00)
#define Q01 (+2.2870199131123099030306700156336010607855682979110E-02)
#define Q02 (+1.6941401731687180653887645350074087642983730428247E-02)
#define Q03 (+3.3442991029403907135136088087976611122246232819088E-04)
#define Q04 (+1.2956776590396646109785974753348875955629223660771E-04)
#define Q05 (+1.7315958071840709335450783742620926201313388660630E-06)
#define Q06 (+4.7081304850024478004841232912480228210495288532604E-07)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_NUM_EVAL(z) \
P00 + z*(\
    P01 + z*(\
        P02 + z*(\
            P03 + z*(\
                P04 + z*(\
                    P05 + z*(\
                        P06 + z*(\
                            P07 + z*P08\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  Helper macro for evaluating a polynomial via Horner's method.             */
#define TMPL_DEN_EVAL(z) \
Q00 + z*(\
    Q01 + z*(\
        Q02 + z*(\
            Q03 + z*(\
                Q04 + z*(\
                    Q05 + z*Q06\
                )\
            )\
        )\
    )\
)



#define J0_ZERO_HI (+5.5200781102863105687106326513458043336868E+00)
#define J0_ZERO_LO (+8.0885971461467223317584450909605563952859E-17)

TMPL_INLINE_DECL
double tmpl_Double_Bessel_J0_Second_Zero(double x)
{
    const double z = (x - J0_ZERO_HI) - J0_ZERO_LO;
    const double p = TMPL_NUM_EVAL(z);
    const double q = TMPL_DEN_EVAL(z);
    return z * p / q;
}

#undef P00
#undef P01
#undef P02
#undef P03
#undef P04
#undef P05
#undef P06
#undef P07
#undef P08
#undef P09
#undef P10
#undef P11

#undef Q00
#undef Q01
#undef Q02
#undef Q03
#undef Q04
#undef Q05
#undef Q06
#undef Q07
#undef Q08

#undef TMPL_NUM_EVAL
#undef TMPL_DEN_EVAL

#undef J0_ZERO_HI
#undef J0_ZERO_LO

#endif
