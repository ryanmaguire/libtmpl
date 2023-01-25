#include <libtmpl/include/tmpl_math.h>
#include <libtmpl/include/tmpl_special_functions_real.h>

/*  TODO:
 *      Add float and long double versions.
 *      Rewrite this using coefficients that are more easily reproducible.
 *      Add programs to the data/ directory to compute these coefficients.
 *      Add license and doc-string.
 *      Add comments and explain everything.
 *      Inline this function, or split it into several inlined functions that
 *      are smaller.
 */

#define PA0 (-8.63399505615014331E-02)
#define PA1 (-1.64303871814816464E+00)
#define PA2 (-7.71247913918273738E+00)
#define PA3 (-1.41014495545382454E+01)
#define PA4 (-1.02269079949257616E+01)
#define PA5 (-2.17236002836306691E+00)

#define QA0 (+1.00000000000000000E+00)
#define QA1 (+7.44775406945739243E+00)
#define QA2 (+2.04392643087266541E+01)
#define QA3 (+2.51001961077774193E+01)
#define QA4 (+1.31256080849023319E+01)
#define QA5 (+2.11640324843601588E+00)

#define A0 (+1.08633995056152344E+00)

#define TMPL_PA_POLY_EVAL(x) PA0+x*(PA1+x*(PA2+x*(PA3+x*(PA4+x*PA5))))
#define TMPL_QA_POLY_EVAL(x) QA0+x*(QA1+x*(QA2+x*(QA3+x*(QA4+x*QA5))))

#define PB0 (-2.03596115108465635E-01)
#define PB1 (-2.95029082937201859E+00)
#define PB2 (-1.54287922188671648E+01)
#define PB3 (-3.81185809571116965E+01)
#define PB4 (-4.66384358235575985E+01)
#define PB5 (-2.59282069989642468E+01)
#define PB6 (-4.70140451266553279E+00)

#define QB0 (+1.00000000000000000E+00)
#define QB1 (+9.57921436074599929E+00)
#define QB2 (+3.60988119290234377E+01)
#define QB3 (+6.73977699505546007E+01)
#define QB4 (+6.41104992068148823E+01)
#define QB5 (+2.82060127225153607E+01)
#define QB6 (+4.10677610657724330E+00)

#define B0 (+1.20359611511230469E+00)

#define TMPL_PB_POLY_EVAL(x) PB0+x*(PB1+x*(PB2+x*(PB3+x*(PB4+x*(PB5+x*PB6)))))
#define TMPL_QB_POLY_EVAL(x) QB0+x*(QB1+x*(QB2+x*(QB3+x*(QB4+x*(QB5+x*QB6)))))

#define PC0 (-3.49729841718749014E-01)
#define PC1 (-6.28207407760709028E+01)
#define PC2 (-2.57226178029669171E+03)
#define PC3 (-2.50271008623093747E+04)
#define PC4 (+1.11949239154711388E+05)
#define PC5 (+1.85684566607844318E+06)
#define PC6 (+4.80802490427638643E+06)
#define PC7 (+2.76624752134636406E+06)

#define QC0 (+1.00000000000000000E+00)
#define QC1 (+1.82717661215113000E+02)
#define QC2 (+8.00121119810280100E+03)
#define QC3 (+1.06073266717010129E+05)
#define QC4 (+3.22848993926057721E+05)
#define QC5 (-8.05684814514171256E+05)
#define QC6 (-2.59223192927265737E+06)
#define QC7 (-5.61719645211570871E+05)
#define QC8 (+6.27765369292636844E+04)

#define C0 (+3.49680423736572266E-01)

#define TMPL_PC_POLY_EVAL(x) \
PC0+x*(PC1+x*(PC2+x*(PC3+x*(PC4+x*(PC5+x*(PC6+x*PC7))))))

#define TMPL_QC_POLY_EVAL(x) \
QC0+x*(QC1+x*(QC2+x*(QC3+x*(QC4+x*(QC5+x*(QC6+x*(QC7+x*QC8)))))))

#define PD0 (-5.00173570682372162E-02)
#define PD1 (-4.44242461870072044E+01)
#define PD2 (-9.51185533619946042E+03)
#define PD3 (-5.88605699015429386E+05)
#define PD4 (-1.90760843597427751E+06)
#define PD5 (+5.79797663818311404E+08)
#define PD6 (+1.11383352508459134E+10)
#define PD7 (+5.67791253678716467E+10)
#define PD8 (+6.32694500716584572E+10)

#define QD0 (+1.00000000000000000E+00)
#define QD1 (+9.08910517489981551E+02)
#define QD2 (+2.10170163753340133E+05)
#define QD3 (+1.67858612416470327E+07)
#define QD4 (+4.90435561733227953E+08)
#define QD5 (+4.54978142622939917E+09)
#define QD6 (+2.87716585708739168E+09)
#define QD7 (-4.59414247951143131E+10)
#define QD8 (-1.72845216404874299E+10)

#define D0 (+5.00126481056213379E-02)

#define TMPL_PD_POLY_EVAL(x) \
PD0+x*(PD1+x*(PD2+x*(PD3+x*(PD4+x*(PD5+x*(PD6+x*(PD7+x*PD8)))))))

#define TMPL_QD_POLY_EVAL(x) \
QD0+x*(QD1+x*(QD2+x*(QD3+x*(QD4+x*(QD5+x*(QD6+x*(QD7+x*QD8)))))))

double tmpl_Double_LambertW_Negative(double x)
{
    double p, q, z;
    if (x > -0.1)
    {
        p = TMPL_PA_POLY_EVAL(x);
        q = TMPL_QA_POLY_EVAL(x);
        return x*(A0 + p/q);
    }
    else if (x > -0.2)
    {
        p = TMPL_PB_POLY_EVAL(x);
        q = TMPL_QB_POLY_EVAL(x);
        return x*(B0 + p/q);
    }

    z = x + tmpl_Rcpr_Euler_E;

    if (z > 0.05)
    {
        p = TMPL_PC_POLY_EVAL(z);
        q = TMPL_QC_POLY_EVAL(z);
        return -z / (C0 + p/q);
    }
    else if (z > 0.01)
    {
        p = TMPL_PD_POLY_EVAL(z);
        q = TMPL_QD_POLY_EVAL(z);
        return -z / (D0 + p/q);
    }
    else
    {
        const double x0 = x;
        const double tol = -x0*2.220446049250313e-16;
        return tmpl_Double_LambertW_Halley(x, x0, tol);
    }
}
