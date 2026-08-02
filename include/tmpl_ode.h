#ifndef TMPL_ODE_H
#define TMPL_ODE_H

#include <libtmpl/include/tmpl_attributes.h>
#include <libtmpl/include/types/tmpl_function_double.h>
#include <libtmpl/include/types/tmpl_function_float.h>
#include <libtmpl/include/types/tmpl_function_ldouble.h>
#include <libtmpl/include/types/tmpl_time_dependent_function_double.h>
#include <libtmpl/include/types/tmpl_time_dependent_function_float.h>
#include <libtmpl/include/types/tmpl_time_dependent_function_ldouble.h>

TMPL_CONST_FUNC
extern double
tmpl_Double_Autonomous_Euler(const tmpl_FunctionDouble f,
                             const double x,
                             const double h)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern float
tmpl_Float_Autonomous_Euler(const tmpl_FunctionFloat f,
                            const float x,
                            const float h)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern long double
tmpl_LDouble_Autonomous_Euler(const tmpl_FunctionLongDouble f,
                              const long double x,
                              const long double h)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern double
tmpl_Double_Autonomous_Heun(const tmpl_FunctionDouble f,
                            const double x,
                            const double h)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern float
tmpl_Float_Autonomous_Heun(const tmpl_FunctionFloat f,
                           const float x,
                           const float h)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern long double
tmpl_LDouble_Autonomous_Heun(const tmpl_FunctionLongDouble f,
                             const long double x,
                             const long double h)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern double
tmpl_Double_Autonomous_Midpoint(const tmpl_FunctionDouble f,
                                const double x,
                                const double h)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern float
tmpl_Float_Autonomous_Midpoint(const tmpl_FunctionFloat f,
                               const float x,
                               const float h)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern long double
tmpl_LDouble_Autonomous_Midpoint(const tmpl_FunctionLongDouble f,
                                 const long double x,
                                 const long double h)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern double
tmpl_Double_Autonomous_Ralston(const tmpl_FunctionDouble f,
                               const double x,
                               const double h)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern float
tmpl_Float_Autonomous_Ralston(const tmpl_FunctionFloat f,
                              const float x,
                              const float h)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern long double
tmpl_LDouble_Autonomous_Ralston(const tmpl_FunctionLongDouble f,
                                const long double x,
                                const long double h)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern double
tmpl_Double_Autonomous_RK4(const tmpl_FunctionDouble f,
                           const double x,
                           const double h)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern float
tmpl_Float_Autonomous_RK4(const tmpl_FunctionFloat f,
                          const float x,
                          const float h)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern long double
tmpl_LDouble_Autonomous_RK4(const tmpl_FunctionLongDouble f,
                            const long double x,
                            const long double h)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern double
tmpl_Double_Autonomous_Second_Order_CD(const tmpl_FunctionDouble f,
                                       const double x0,
                                       const double x1,
                                       const double h)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern float
tmpl_Float_Autonomous_Second_Order_CD(const tmpl_FunctionFloat f,
                                      const float x0,
                                      const float x1,
                                      const float h)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern long double
tmpl_LDouble_Autonomous_Second_Order_CD(const tmpl_FunctionLongDouble f,
                                        const long double x0,
                                        const long double x1,
                                        const long double h)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern double
tmpl_Double_Autonomous_Second_Order_Euler(const tmpl_FunctionDouble f,
                                          const double x,
                                          double * const v,
                                          const double h)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern float
tmpl_Float_Autonomous_Second_Order_Euler(const tmpl_FunctionFloat f,
                                         const float x,
                                         float * const v,
                                         const float h)
TMPL_UNSEQUENCED;

TMPL_CONST_FUNC
extern long double
tmpl_LDouble_Autonomous_Second_Order_Euler(const tmpl_FunctionLongDouble f,
                                           const long double x,
                                           long double * const v,
                                           const long double h)
TMPL_UNSEQUENCED;

#endif
