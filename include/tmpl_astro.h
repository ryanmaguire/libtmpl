/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ASTRO_H
#define TMPL_ASTRO_H

/*  If using with C++ (and not C), wrap the entire header file in an extern   *
 *  "C" statement. Check if C++ is being used with __cplusplus.               */
#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Light_Distance                                            *
 *  Purpose:                                                                  *
 *      Computes the distance light travels in |t1 - t0| seconds.             *
 *  Arguments:                                                                *
 *      t0 (const double):                                                    *
 *          The start time.                                                   *
 *      t0 (const double):                                                    *
 *          The finish time.                                                  *
 *  Outputs:                                                                  *
 *      distance (double):                                                    *
 *          The distance light travels in vacuum in |t1 - t0| seconds.        *
 *  Notes:                                                                    *
 *      1.) Float and long double precisions also provided.                   *
 *      2.) All times are assumed to be in seconds.                           *
 *      3.) No checks for NaN or infinity are performed.                      *
 *      4.) There is no assumption that t0 < t1 or t1 < t0. You may use this  *
 *          via tmpl_Double_Light_Distance(t0, t1), or you may write          *
 *          tmpl_Double_Light_Distance(t1, t0). Both return the same value.   *
 ******************************************************************************/
extern float
tmpl_Float_Light_Distance(const float t0, const float t1);

extern double
tmpl_Double_Light_Distance(const double t0, double t1);

extern long double
tmpl_LDouble_Light_Distance(const long double t0, const long double t1);

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
/*  End of include guard.                                                     */
