/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl is distributed in the hope that it will be useful,                *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *
 ******************************************************************************
 *                                  tmpl_ode                                  *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Tools for numerically solving ordinary differential equations.        *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       August 1, 2026                                                *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ODE_H
#define TMPL_ODE_H

/*  C23 attributes for optimization are found here.                           */
#include <libtmpl/include/tmpl_attributes.h>

/*  Function types for real-valued functions with real inputs.                */
#include <libtmpl/include/types/tmpl_function_double.h>
#include <libtmpl/include/types/tmpl_function_float.h>
#include <libtmpl/include/types/tmpl_function_ldouble.h>
#include <libtmpl/include/types/tmpl_time_dependent_function_double.h>
#include <libtmpl/include/types/tmpl_time_dependent_function_float.h>
#include <libtmpl/include/types/tmpl_time_dependent_function_ldouble.h>

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Autonomous_Euler                                          *
 *  Purpose:                                                                  *
 *      Computes the Euler iterate for an autonomous ODE x'(t) = f(x).        *
 *  Arguments:                                                                *
 *      f (const tmpl_FunctionDouble):                                        *
 *          The function for the differential equation.                       *
 *      x (const double):                                                     *
 *          The current iteration for the numerical solution to the ODE.      *
 *      h (const double):                                                     *
 *          The step size in t between iterations.                            *
 *  Output:                                                                   *
 *      sol (double):                                                         *
 *          The numerical approximation for x(t_0 + h) where x(t_0) is the    *
 *          input value provided above.                                       *
 ******************************************************************************/
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

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Autonomous_Heun                                           *
 *  Purpose:                                                                  *
 *      Computes the Heun RK2 iterate for an autonomous ODE x'(t) = f(x).     *
 *  Arguments:                                                                *
 *      f (const tmpl_FunctionDouble):                                        *
 *          The function for the differential equation.                       *
 *      x (const double):                                                     *
 *          The current iteration for the numerical solution to the ODE.      *
 *      h (const double):                                                     *
 *          The step size in t between iterations.                            *
 *  Output:                                                                   *
 *      sol (double):                                                         *
 *          The numerical approximation for x(t_0 + h) where x(t_0) is the    *
 *          input value provided above.                                       *
 ******************************************************************************/
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

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Autonomous_Midpoint                                       *
 *  Purpose:                                                                  *
 *      Computes the midpoint RK2 iterate for an autonomous ODE x'(t) = f(x). *
 *  Arguments:                                                                *
 *      f (const tmpl_FunctionDouble):                                        *
 *          The function for the differential equation.                       *
 *      x (const double):                                                     *
 *          The current iteration for the numerical solution to the ODE.      *
 *      h (const double):                                                     *
 *          The step size in t between iterations.                            *
 *  Output:                                                                   *
 *      sol (double):                                                         *
 *          The numerical approximation for x(t_0 + h) where x(t_0) is the    *
 *          input value provided above.                                       *
 ******************************************************************************/
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

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Autonomous_Ralston                                        *
 *  Purpose:                                                                  *
 *      Computes the Ralston RK2 iterate for an autonomous ODE x'(t) = f(x).  *
 *  Arguments:                                                                *
 *      f (const tmpl_FunctionDouble):                                        *
 *          The function for the differential equation.                       *
 *      x (const double):                                                     *
 *          The current iteration for the numerical solution to the ODE.      *
 *      h (const double):                                                     *
 *          The step size in t between iterations.                            *
 *  Output:                                                                   *
 *      sol (double):                                                         *
 *          The numerical approximation for x(t_0 + h) where x(t_0) is the    *
 *          input value provided above.                                       *
 ******************************************************************************/
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

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Autonomous_RK4                                            *
 *  Purpose:                                                                  *
 *      Computes the standard RK4 iterate for an autonomous ODE x'(t) = f(x). *
 *  Arguments:                                                                *
 *      f (const tmpl_FunctionDouble):                                        *
 *          The function for the differential equation.                       *
 *      x (const double):                                                     *
 *          The current iteration for the numerical solution to the ODE.      *
 *      h (const double):                                                     *
 *          The step size in t between iterations.                            *
 *  Output:                                                                   *
 *      sol (double):                                                         *
 *          The numerical approximation for x(t_0 + h) where x(t_0) is the    *
 *          input value provided above.                                       *
 ******************************************************************************/
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

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Autonomous_Second_Order_CD                                *
 *  Purpose:                                                                  *
 *      Computes the central difference iterate for an autonomous second      *
 *      order ODE x''(t) = f(x).                                              *
 *  Arguments:                                                                *
 *      f (const tmpl_FunctionDouble):                                        *
 *          The function for the differential equation.                       *
 *      x0 (const double):                                                    *
 *          The solution for x at time t - h.                                 *
 *      x1 (const double):                                                    *
 *          The solution for x at time t.                                     *
 *      h (const double):                                                     *
 *          The step size in t between iterations.                            *
 *  Output:                                                                   *
 *      sol (double):                                                         *
 *          The numerical approximation for x at time t + h.                  *
 ******************************************************************************/
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

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Double_Autonomous_Second_Order_Euler                             *
 *  Purpose:                                                                  *
 *      Computes the Euler iterate for an autonomous second order ODE         *
 *      x''(t) = f(x).                                                        *
 *  Arguments:                                                                *
 *      f (const tmpl_FunctionDouble):                                        *
 *          The function for the differential equation.                       *
 *      x (const double):                                                     *
 *          The solution for x at time t_0.                                   *
 *      v (double * const):                                                   *
 *          The solution for x' at time t_0.                                  *
 *      h (const double):                                                     *
 *          The step size in t between iterations.                            *
 *  Output:                                                                   *
 *      sol (double):                                                         *
 *          The numerical approximation for x at time t_0 + h.                *
 *  Notes:                                                                    *
 *      1.) The initial velocity parameter is taken as a pointer. The updated *
 *          velocity, which is the velocity at time t_0 + h, will be stored   *
 *          here at the end of the computation.                               *
 ******************************************************************************/
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
/*  End of include guard.                                                     */
