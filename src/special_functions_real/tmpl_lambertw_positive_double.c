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

#define PA00 (+1.80340766906685177E-01)
#define PA01 (+3.28178241493119307E-01)
#define PA02 (-2.19153620687139706E+00)
#define PA03 (-7.24750929074563990E+00)
#define PA04 (-7.28395876262524204E+00)
#define PA05 (-2.57417169492512916E+00)
#define PA06 (-2.31606948888704503E-01)

#define QA00 (+1.00000000000000000E+00)
#define QA01 (+7.36482529307436604E+00)
#define QA02 (+2.03686007856430677E+01)
#define QA03 (+2.62864592096657307E+01)
#define QA04 (+1.59742041380858333E+01)
#define QA05 (+4.03760534788374589E+00)
#define QA06 (+2.91327346750475362E-01)

#define A00 (+8.19659233093261719E-01)

#define TMPL_PA_POLY_EVAL(x) \
PA00+x*(PA01+x*(PA02+x*(PA03+x*(PA04+x*(PA05+x*PA06)))))

#define TMPL_QA_POLY_EVAL(x) \
QA00+x*(QA01+x*(QA02+x*(QA03+x*(QA04+x*(QA05+x*QA06)))))

#define PB00 (+4.49664083944098322E-01)
#define PB01 (+1.90417666196776909E+00)
#define PB02 (+1.99951368798255994E+00)
#define PB03 (-6.91217310299270265E-01)
#define PB04 (-1.88533935998617058E+00)
#define PB05 (-7.96743968047750836E-01)
#define PB06 (-1.02891726031055254E-01)
#define PB07 (-3.09156013592636568E-03)

#define QB00 (1.00000000000000000E+00)
#define QB01 (6.45854489419584014E+00)
#define QB02 (1.54739232422116048E+01)
#define QB03 (1.72606164253337843E+01)
#define QB04 (9.29427055609544096E+00)
#define QB05 (2.29040824649748117E+00)
#define QB06 (2.21610620995418981E-01)
#define QB07 (5.70597669908194213E-03)

#define B00 (+5.50335884094238281e-01)

#define TMPL_PB_POLY_EVAL(x) \
PB00+x*(PB01+x*(PB02+x*(PB03+x*(PB04+x*(PB05+x*(PB06+x*PB07))))))

#define TMPL_QB_POLY_EVAL(x) \
QB00+x*(QB01+x*(QB02+x*(QB03+x*(QB04+x*(QB05+x*(QB06+x*QB07))))))

#define PC00 (-1.16230494982099475E+00)
#define PC01 (-3.38528144432561136E+00)
#define PC02 (-2.55653717293161565E+00)
#define PC03 (-3.06755172989214189E-01)
#define PC04 (+1.73149743765268289E-01)
#define PC05 (+3.76906042860014206E-02)
#define PC06 (+1.84552217624706666E-03)
#define PC07 (+1.69434126904822116E-05)

#define QC00 (+1.00000000000000000E+00)
#define QC01 (+3.77187616711220819E+00)
#define QC02 (+4.58799960260143701E+00)
#define QC03 (+2.24101228462292447E+00)
#define QC04 (+4.54794195426212385E-01)
#define QC05 (+3.60761772095963982E-02)
#define QC06 (+9.25176499518388571E-04)
#define QC07 (+4.43611344705509378E-06)

#define C00 (+1.16239356994628906E+00)

#define TMPL_PC_POLY_EVAL(x) \
PC00+x*(PC01+x*(PC02+x*(PC03+x*(PC04+x*(PC05+x*(PC06+x*PC07))))))

#define TMPL_QC_POLY_EVAL(x) \
QC00+x*(QC01+x*(QC02+x*(QC03+x*(QC04+x*(QC05+x*(QC06+x*QC07))))))

#define PD00 (-1.80690935424793635E+00)
#define PD01 (-3.66995929380314602E+00)
#define PD02 (-1.93842957940149781E+00)
#define PD03 (-2.94269984375794040E-01)
#define PD04 (+1.81224710627677778E-03)
#define PD05 (+2.48166798603547447E-03)
#define PD06 (+1.15806592415397245E-04)
#define PD07 (+1.43105573216815533E-06)
#define PD08 (+3.47281483428369604E-09)

#define QD00 (+1.00000000000000000E+00)
#define QD01 (+2.57319080723908597E+00)
#define QD02 (+1.96724528442680658E+00)
#define QD03 (+5.84501352882650722E-01)
#define QD04 (+7.37152837939206240E-02)
#define QD05 (+3.97368430940416778E-03)
#define QD06 (+8.54941838187085088E-05)
#define QD07 (+6.05713225608426678E-07)
#define QD08 (+8.17517283816615732E-10)

#define D00 (+1.80937194824218750E+00)

#define TMPL_PD_POLY_EVAL(x) \
PD00+x*(PD01+x*(PD02+x*(PD03+x*(PD04+x*(PD05+x*(PD06+x*(PD07+x*PD08)))))))

#define TMPL_QD_POLY_EVAL(x) \
QD00+x*(QD01+x*(QD02+x*(QD03+x*(QD04+x*(QD05+x*(QD06+x*(QD07+x*QD08)))))))

#define PE00 (+1.97011826279311924E+00)
#define PE01 (+1.05639945701546704E+00)
#define PE02 (+3.33434529073196304E-01)
#define PE03 (+3.34619153200386816E-02)
#define PE04 (-5.36238353781326675E-03)
#define PE05 (-2.43901294871308604E-03)
#define PE06 (-2.13762095619085404E-04)
#define PE07 (-4.85531936495542274E-06)
#define PE08 (-2.02473518491905386E-08)

#define QE00 (+1.00000000000000000E+00)
#define QE01 (+8.60107275833921618E-01)
#define QE02 (+4.10420467985504373E-01)
#define QE03 (+1.18444884081994841E-01)
#define QE04 (+2.16966505556021046E-02)
#define QE05 (+2.24529766630769097E-03)
#define QE06 (+9.82045090226437614E-05)
#define QE07 (+1.36363515125489502E-06)
#define QE08 (+3.44200749053237945E-09)

#define E00 (-1.40297317504882812E+00)

#define TMPL_PE_POLY_EVAL(x) \
PE00+x*(PE01+x*(PE02+x*(PE03+x*(PE04+x*(PE05+x*(PE06+x*(PE07+x*PE08)))))))

#define TMPL_QE_POLY_EVAL(x) \
QE00+x*(QE01+x*(QE02+x*(QE03+x*(QE04+x*(QE05+x*(QE06+x*(QE07+x*QE08)))))))

#define PF00 (+3.30547638424076217E+00)
#define PF01 (+1.64050071277550167E+00)
#define PF02 (+4.57149576470736039E-01)
#define PF03 (+4.03821227745424840E-02)
#define PF04 (-4.99664976882514362E-04)
#define PF05 (-1.28527893803052956E-04)
#define PF06 (-2.95470325373338738E-06)
#define PF07 (-1.76662025550202762E-08)
#define PF08 (-1.98721972463709290E-11)

#define QF00 (+1.00000000000000000E+00)
#define QF01 (+6.91472559412458759E-01)
#define QF02 (+2.48154578891676774E-01)
#define QF03 (+4.60893578284335263E-02)
#define QF04 (+3.60207838982301946E-03)
#define QF05 (+1.13001153242430471E-04)
#define QF06 (+1.33690948263488455E-06)
#define QF07 (+4.97253225968548872E-09)
#define QF08 (+3.39460723731970550E-12)

#define F00 (-2.73572921752929688E+00)

#define TMPL_PF_POLY_EVAL(x) \
PF00+x*(PF01+x*(PF02+x*(PF03+x*(PF04+x*(PF05+x*(PF06+x*(PF07+x*PF08)))))))

#define TMPL_QF_POLY_EVAL(x) \
QF00+x*(QF01+x*(QF02+x*(QF03+x*(QF04+x*(QF05+x*(QF06+x*(QF07+x*QF08)))))))

#define PG00 (+5.07714858354309672E+00)
#define PG01 (-3.32994414518701458E+00)
#define PG02 (-8.61170416909864451E-01)
#define PG03 (-4.01139705309486142E-02)
#define PG04 (-1.85374201771834585E-04)
#define PG05 (+1.08824145844270666E-05)
#define PG06 (+1.17216905810452396E-07)
#define PG07 (+2.97998248101385990E-10)
#define PG08 (+1.42294856434176682E-13)

#define QG00 (+1.00000000000000000E+00)
#define QG01 (-4.85840770639861485E-01)
#define QG02 (-3.18714850604827580E-01)
#define QG03 (-3.20966129264610534E-02)
#define QG04 (-1.06276178044267895E-03)
#define QG05 (-1.33597828642644955E-05)
#define QG06 (-6.27900905346219472E-08)
#define QG07 (-9.35271498075378319E-11)
#define QG08 (-2.60648331090076845E-14)

#define G00 (-4.01286315917968750E+00)

#define TMPL_PG_POLY_EVAL(x) \
PG00+x*(PG01+x*(PG02+x*(PG03+x*(PG04+x*(PG05+x*(PG06+x*(PG07+x*PG08)))))))

#define TMPL_QG_POLY_EVAL(x) \
QG00+x*(QG01+x*(QG02+x*(QG03+x*(QG04+x*(QG05+x*(QG06+x*(QG07+x*QG08)))))))

#define PH00 (+6.42275660145116698E+00)
#define PH01 (+1.33047964073367945E+00)
#define PH02 (+6.72008923401652816E-02)
#define PH03 (+1.16444069958125895E-03)
#define PH04 (+7.06966760237470501E-06)
#define PH05 (+5.48974896149039165E-09)
#define PH06 (-7.00379652018853621E-11)
#define PH07 (-1.89247635913659556E-13)
#define PH08 (-1.55898770790170598E-16)
#define PH09 (-4.06109208815303157E-20)
#define PH10 (-2.21552699006496737E-24)

#define QH00 (+1.00000000000000000E+00)
#define QH01 (+3.34498588416632854E-01)
#define QH02 (+2.51519862456384983E-02)
#define QH03 (+6.81223810622416254E-04)
#define QH04 (+7.94450897106903537E-06)
#define QH05 (+4.30675039872881342E-08)
#define QH06 (+1.10667669458467617E-10)
#define QH07 (+1.31012240694192289E-13)
#define QH08 (+6.53282047177727125E-17)
#define QH09 (+1.11775518708172009E-20)
#define QH10 (+3.78250395617836059E-25)

#define H00 (-5.70115661621093750E+00)

#define TMPL_PH_POLY_EVAL(x) \
PH00 + x*(\
    PH01 + x*(\
        PH02 + x*(\
            PH03 + x*(\
                PH04 + x*(\
                    PH05 + x*(\
                        PH06 + x*(\
                            PH07 + x*(\
                                PH08 + x*(\
                                    PH09 + x*PH10\
                                )\
                            )\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

#define TMPL_QH_POLY_EVAL(x) \
QH00 + x*(\
    QH01 + x*(\
        QH02 + x*(\
            QH03 + x*(\
                QH04 + x*(\
                    QH05 + x*(\
                        QH06 + x*(\
                            QH07 + x*(\
                                QH08 + x*(\
                                    QH09 + x*QH10\
                                )\
                            )\
                        )\
                    )\
                )\
            )\
        )\
    )\
)

/*  Function for computing LambertW(x) for real x > 0.                        */
double tmpl_Double_LambertW_Positive(double x)
{
    double p, q, log_x;

    if (x < 2.0)
    {
        if (x < 0.5)
        {
            p = TMPL_PA_POLY_EVAL(x);
            q = TMPL_QA_POLY_EVAL(x);
            return x * (A00 + p/q);
        }
        else
        {
            p = TMPL_PB_POLY_EVAL(x);
            q = TMPL_QB_POLY_EVAL(x);
            return x * (B00 + p/q);
        }
    }
    else if (x < 6.0)
    {
        p = TMPL_PC_POLY_EVAL(x);
        q = TMPL_QC_POLY_EVAL(x);
        return C00 + p/q;
    }
    else if (x < 18.0)
    {
        p = TMPL_PD_POLY_EVAL(x);
        q = TMPL_QD_POLY_EVAL(x);
        return D00 + p/q;
    }

    log_x = tmpl_Double_Log(x);

    if (log_x < 9.2)
    {
        p = TMPL_PE_POLY_EVAL(log_x);
        q = TMPL_QE_POLY_EVAL(log_x);
        return log_x + E00 + p/q;
    }

    else if (log_x < 32.0)
    {
        p = TMPL_PF_POLY_EVAL(log_x);
        q = TMPL_QF_POLY_EVAL(log_x);
        return log_x + F00 + p/q;
    }
    else if (log_x < 100.0)
    {
        p = TMPL_PG_POLY_EVAL(log_x);
        q = TMPL_QG_POLY_EVAL(log_x);
        return log_x + G00 + p/q;
    }
    else
    {
        p = TMPL_PH_POLY_EVAL(log_x);
        q = TMPL_QH_POLY_EVAL(log_x);
        return log_x + H00 + p/q;
    }
}
/*  End of tmpl_Double_LambertW_Positive.                                     */

/*  Undefine everything in case someone wants to #include this file.          */
#undef PA00
#undef PA01
#undef PA02
#undef PA03
#undef PA04
#undef PA05
#undef PA06
#undef QA00
#undef QA01
#undef QA02
#undef QA03
#undef QA04
#undef QA05
#undef QA06
#undef PB00
#undef PB01
#undef PB02
#undef PB03
#undef PB04
#undef PB05
#undef PB06
#undef PB07
#undef QB00
#undef QB01
#undef QB02
#undef QB03
#undef QB04
#undef QB05
#undef QB06
#undef QB07
#undef PC00
#undef PC01
#undef PC02
#undef PC03
#undef PC04
#undef PC05
#undef PC06
#undef PC07
#undef QC00
#undef QC01
#undef QC02
#undef QC03
#undef QC04
#undef QC05
#undef QC06
#undef QC07
#undef PD00
#undef PD01
#undef PD02
#undef PD03
#undef PD04
#undef PD05
#undef PD06
#undef PD07
#undef PD08
#undef QD00
#undef QD01
#undef QD02
#undef QD03
#undef QD04
#undef QD05
#undef QD06
#undef QD07
#undef QD08
#undef PE00
#undef PE01
#undef PE02
#undef PE03
#undef PE04
#undef PE05
#undef PE06
#undef PE07
#undef PE08
#undef QE00
#undef QE01
#undef QE02
#undef QE03
#undef QE04
#undef QE05
#undef QE06
#undef QE07
#undef QE08
#undef PF00
#undef PF01
#undef PF02
#undef PF03
#undef PF04
#undef PF05
#undef PF06
#undef PF07
#undef PF08
#undef QF00
#undef QF01
#undef QF02
#undef QF03
#undef QF04
#undef QF05
#undef QF06
#undef QF07
#undef QF08
#undef PG00
#undef PG01
#undef PG02
#undef PG03
#undef PG04
#undef PG05
#undef PG06
#undef PG07
#undef PG08
#undef QG00
#undef QG01
#undef QG02
#undef QG03
#undef QG04
#undef QG05
#undef QG06
#undef QG07
#undef QG08
#undef PH00
#undef PH01
#undef PH02
#undef PH03
#undef PH04
#undef PH05
#undef PH06
#undef PH07
#undef PH08
#undef PH09
#undef PH10
#undef QH00
#undef QH01
#undef QH02
#undef QH03
#undef QH04
#undef QH05
#undef QH06
#undef QH07
#undef QH08
#undef QH09
#undef QH10

/*  Undefine the constant offsets for each region.                            */
#undef A00
#undef B00
#undef C00
#undef D00
#undef E00
#undef F00
#undef G00
#undef H00

/*  Lastly undef the helpers for evaluating a polynomial via Horner's method. */
#undef TMPL_PA_POLY_EVAL
#undef TMPL_QA_POLY_EVAL
#undef TMPL_PB_POLY_EVAL
#undef TMPL_QB_POLY_EVAL
#undef TMPL_PC_POLY_EVAL
#undef TMPL_QC_POLY_EVAL
#undef TMPL_PD_POLY_EVAL
#undef TMPL_QD_POLY_EVAL
#undef TMPL_PE_POLY_EVAL
#undef TMPL_QE_POLY_EVAL
#undef TMPL_PF_POLY_EVAL
#undef TMPL_QF_POLY_EVAL
#undef TMPL_PG_POLY_EVAL
#undef TMPL_QG_POLY_EVAL
#undef TMPL_PH_POLY_EVAL
#undef TMPL_QH_POLY_EVAL
