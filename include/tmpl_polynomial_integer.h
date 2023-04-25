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
 *                          tmpl_polynomial_integer                           *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide data types for polynomials with integer coefficients.         *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file containing Booleans.                                  *
 *  2.) stdio.h:                                                              *
 *          Standard C header file containing the FILE data type.             *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 1, 2023                                              *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/02/01: Ryan Maguire                                                  *
 *      Getting rid of -Wreserved-identifier warnings with clang.             *
 *  2022/02/15: Ryan Maguire                                                  *
 *      Changing overall layout of polynomials.                               *
 *  2023/02/01: Ryan Maguire                                                  *
 *      Moved integer data type to own file. Added more data types (int etc.).*
 ******************************************************************************/

/*  TODO:
 *      Add "From_String" function that converts string (like "x^2 + 1") to
 *      a polynomial.
 */

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_POLYNOMIAL_INTEGER_H
#define TMPL_POLYNOMIAL_INTEGER_H

/*  If using with C++ (and not C) we need to wrap the entire header file in   *
 *  an extern "C" statement. Check if C++ is being used with __cplusplus.     */
#ifdef __cplusplus
extern "C" {
#endif

/*  Macro indicating whether libtmpl has long long support found here.        */
#include <libtmpl/include/tmpl_inttype.h>

/*  Booleans located here.                                                    */
#include <libtmpl/include/tmpl_bool.h>

/*  The size_t data type is found here.                                       */
#include <stddef.h>

/*  FILE data type found here.                                                */
#include <stdio.h>

/*  Polynomials with integer coefficients, elements of Z[x]. Short data type. */
typedef struct tmpl_ShortPolynomial_Def {

    /*  A pointer to a signed short int array containing the coefficients.    */
    signed short int *coeffs;

    /*  The degree of the polynomial. coeffs has degree + 1 elements.         */
    size_t degree;

    /*  Boolean for keeping track of errors.                                  */
    tmpl_Bool error_occurred;

    /*  And an error message in case an error does occur.                     */
    char *error_message;
} tmpl_ShortPolynomial;

/*  Polynomials with integer coefficients, elements of Z[x]. int data type.   */
typedef struct tmpl_IntPolynomial_Def {

    /*  A pointer to a signed int array containing the coefficients.          */
    signed int *coeffs;

    /*  The degree of the polynomial. coeffs has degree + 1 elements.         */
    size_t degree;

    /*  Boolean for keeping track of errors.                                  */
    tmpl_Bool error_occurred;

    /*  And an error message in case an error does occur.                     */
    char *error_message;
} tmpl_IntPolynomial;

/*  Polynomials with integer coefficients, elements of Z[x]. long data type.  */
typedef struct tmpl_LongPolynomial_Def {

    /*  A pointer to a signed long int array containing the coefficients.     */
    signed long int *coeffs;

    /*  The degree of the polynomial. coeffs has degree + 1 elements.         */
    size_t degree;

    /*  Boolean for keeping track of errors.                                  */
    tmpl_Bool error_occurred;

    /*  And an error message in case an error does occur.                     */
    char *error_message;
} tmpl_LongPolynomial;

/*  If long long support is available, and requested, provide long long poly. */
#if TMPL_HAS_LONGLONG == 1

/*  Polynomials with integer coefficients, elements of Z[x]. long long data.  */
typedef struct tmpl_LongLongPolynomial_Def {

    /*  A pointer to a signed long int array containing the coefficients.     */
    signed long long int *coeffs;

    /*  The number of elements in the coeffs array.                           */
    size_t number_of_coeffs;

    /*  The smallest degree in the polynomial. The degree of the nth term in  *
     *  the coeffs array is min_degree + n;                                   */
    size_t min_degree;

    /*  Boolean for keeping track of the coeffs pointer.                      */
    tmpl_Bool coeffs_can_be_freed;

    /*  Boolean for keeping track of the entire polynomial.                   */
    tmpl_Bool poly_can_be_freed;

    /*  Boolean for keeping track of errors.                                  */
    tmpl_Bool error_occurred;

    /*  And an error message in case an error does occur.                     */
    char *error_message;
} tmpl_LongLongPolynomial;

#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_IntPolynomial_Add_Kernel                                         *
 *  Purpose:                                                                  *
 *      Adds two elements of Z[x] without error checks or shrinking the sum.  *
 *  Arguments:                                                                *
 *      P (const tmpl_IntPolynomial *):                                       *
 *          A pointer to a polynomial.                                        *
 *      Q (const tmpl_IntPolynomial *):                                       *
 *          Another pointer to a polynomial.                                  *
 *      sum (tmpl_IntPolynomial *):                                           *
 *          A pointer to a polynomial, the value P + Q will be stored in it.  *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      Use this if you are absolutely certain P, Q, and sum are not NULL and *
 *      do not have error_occurred set to true, and you don't want the final  *
 *      result to be shrunk (i.e. have its padded zeros removed).             *
 ******************************************************************************/
extern void
tmpl_IntPolynomial_Add_Kernel(const tmpl_IntPolynomial *P,
                              const tmpl_IntPolynomial *Q,
                              tmpl_IntPolynomial *sum);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_IntPolynomial_Add                                                *
 *  Purpose:                                                                  *
 *      Adds two elements of Z[x]. The redundant zeros of the sum are removed.*
 *  Arguments:                                                                *
 *      P (const tmpl_IntPolynomial *):                                       *
 *          A pointer to a polynomial.                                        *
 *      Q (const tmpl_IntPolynomial *):                                       *
 *          Another pointer to a polynomial.                                  *
 *      sum (tmpl_IntPolynomial *):                                           *
 *          A pointer to a polynomial, the value P + Q will be stored in it.  *
 *  Output:                                                                   *
 *      None (void).                                                          *
 ******************************************************************************/
extern void
tmpl_IntPolynomial_Add(const tmpl_IntPolynomial *P,
                       const tmpl_IntPolynomial *Q,
                       tmpl_IntPolynomial *sum);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_IntPolynomial_Calloc                                             *
 *  Purpose:                                                                  *
 *      Creates a polynomial in Z[x] with "length" elements allocated         *
 *      for the coeffs array, all of which are initialized to zero.           *
 *  Arguments:                                                                *
 *      length (size_t).                                                      *
 *          The number of elements allocated to the coeffs array. All         *
 *          elements will be initialized to zero.                             *
 *  Output:                                                                   *
 *      poly (tmpl_IntPolynomial *):                                          *
 *          A pointer to a polynomial with all coefficients set to zero.      *
 *  Notes:                                                                    *
 *      If calloc fails the error_occurred Boolean set to true.               *
 ******************************************************************************/
extern tmpl_IntPolynomial tmpl_IntPolynomial_Calloc(size_t length);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_IntPolynomial_Copy_Kernel                                        *
 *  Purpose:                                                                  *
 *      Copies the data from one polynomial to another.                       *
 *  Arguments:                                                                *
 *      dest (tmpl_IntPolynomial *):                                          *
 *          A pointer to a polynomial. "src" is copied here.                  *
 *      src (const tmpl_IntPolynomial *):                                     *
 *          A pointer to a polynomial. This is the polynomial to be copied.   *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      This function does not check the inputs for possible errors before    *
 *      attempting to copy the data. tmpl_IntPolynomial_Copy is a safer       *
 *      alternative which checks the inputs and then calls this function.     *
 *      This function assumes src and dest are not NULL, their error_occurred *
 *      Booleans are set to False, and src->coeffs is not NULL. The function  *
 *      tmpl_IntPolynomial_Copy does not make these assumptions.              *
 ******************************************************************************/
extern void
tmpl_IntPolynomial_Copy_Kernel(tmpl_IntPolynomial *dest,
                               const tmpl_IntPolynomial *src);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_IntPolynomial_Copy                                               *
 *  Purpose:                                                                  *
 *      Copies the data from one polynomial to another.                       *
 *  Arguments:                                                                *
 *      dest (tmpl_IntPolynomial *):                                          *
 *          A pointer to a polynomial. "src" is copied here.                  *
 *      src (const tmpl_IntPolynomial *):                                     *
 *          A pointer to a polynomial. This is the polynomial to be copied.   *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      If malloc fails the coeffs pointer is set to NULL.                    *
 ******************************************************************************/
extern void
tmpl_IntPolynomial_Copy(tmpl_IntPolynomial *dest,
                        const tmpl_IntPolynomial *src);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_IntPolynomial_Destroy                                            *
 *  Purpose:                                                                  *
 *      Free all of the memory in a tmpl_IntPolynomial pointer and set the    *
 *      the pointers inside the struct to NULL.                               *
 *  Arguments:                                                                *
 *      poly_ptr (tmpl_IntPolynomial *)                                       *
 *          A pointer a polynomial, the polynomial to be destroyed.           *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      This function should always be called when done with a polynomial     *
 *      to avoid memory leaks.                                                *
 ******************************************************************************/
extern void tmpl_IntPolynomial_Destroy(tmpl_IntPolynomial *poly);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_IntPolynomial_Empty                                              *
 *  Purpose:                                                                  *
 *      Creates an empty polynomial with pointers set to NULL.                *
 *  Inputs:                                                                   *
 *      None (void).                                                          *
 *  Outputs:                                                                  *
 *      poly (tmpl_IntPolynomial):                                            *
 *          The empty polynomial.                                             *
 ******************************************************************************/
tmpl_IntPolynomial tmpl_IntPolynomial_Empty(void);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_IntPolynomial_Extract_Term                                       *
 *  Purpose:                                                                  *
 *      Extract the coefficient of a given term.                              *
 *  Arguments:                                                                *
 *      poly (const tmpl_IntPolynomial *):                                    *
 *          A pointer to a polynomial.                                        *
 *      term (size_t):                                                        *
 *          The term to be extracted.                                         *
 *  Output:                                                                   *
 *      coefficient (int):                                                    *
 *          The value of the given term.                                      *
 *  Notes:                                                                    *
 *      If poly is NULL, poly->error_occurred is true, poly->degree < term,   *
 *      or if poly->coeffs = NULL, the value 0 is returned.                   *
 ******************************************************************************/
extern int
tmpl_IntPolynomial_Extract_Term(const tmpl_IntPolynomial *poly, size_t term);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_IntPolynomial_Init                                               *
 *  Purpose:                                                                  *
 *      Initializes a polynomial in Z[x] with all pointers set to NULL and    *
 *      all variables set to their zero values.                               *
 *  Inputs:                                                                   *
 *      poly (tmpl_IntPolynomial *):                                          *
 *          A pointer to the polynomial that is to be initialized.            *
 *  Outputs:                                                                  *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      The coeffs and error_message pointers are set to NULL regardless of   *
 *      what they point to. Do not use this function on polynomials that have *
 *      memory allocated for their pointers or you will have a memory leak.   *
 ******************************************************************************/
extern void tmpl_IntPolynomial_Init(tmpl_IntPolynomial *poly);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_IntPolynomial_Multiply                                           *
 *  Purpose:                                                                  *
 *      Multiplies two elements of Z[x].                                      *
 *  Arguments:                                                                *
 *      P (tmpl_PolynomialZ *):                                               *
 *          A pointer to a polynomial.                                        *
 *      Q (tmpl_PolynomialZ *):                                               *
 *          Another pointer to a polynomial.                                  *
 *      prod (tmpl_PolynomialZ *):                                            *
 *          A pointer to a polynomial, the value P*Q will be stored in it.    *
 *  Output:                                                                   *
 *      None (void).                                                          *
 ******************************************************************************/
extern void
tmpl_IntPolynomial_Multiply(const tmpl_IntPolynomial *P,
                            const tmpl_IntPolynomial *Q,
                            tmpl_IntPolynomial *prod);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_IntPolynomial_Naive_Multiply                                     *
 *  Purpose:                                                                  *
 *      Multiplies two elements of Z[x].                                      *
 *  Arguments:                                                                *
 *      P (tmpl_PolynomialZ *):                                               *
 *          A pointer to a polynomial.                                        *
 *      Q (tmpl_PolynomialZ *):                                               *
 *          Another pointer to a polynomial.                                  *
 *      prod (tmpl_PolynomialZ *):                                            *
 *          A pointer to a polynomial, the value P*Q will be stored in it.    *
 *  Output:                                                                   *
 *      None (void).                                                          *
 ******************************************************************************/
extern void
tmpl_IntPolynomial_Naive_Multiply(const tmpl_IntPolynomial *P,
                                  const tmpl_IntPolynomial *Q,
                                  tmpl_IntPolynomial *prod);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_IntPolynomial_As_String                                          *
 *  Purpose:                                                                  *
 *      Represents a polynomial as a string. Coefficients that are zero will  *
 *      not be printed, unless the polynomial is the zero polynomial.         *
 *  Arguments:                                                                *
 *      P (tmpl_PolynomialZ *):                                               *
 *          A pointer to a polynomial.                                        *
 *  Output:                                                                   *
 *      str (char *):                                                         *
 *          A pointer to a char array representing the polynomial as a string.*
 *  Notes:                                                                    *
 *      If poly->error_occurred is true, or if poly->coeffs = NULL, or if     *
 *      poly = NULL, a NULL pointer is returned. Otherwise, malloc will be    *
 *      called. If malloc fails, a NULL pointer is returned. It is worth      *
 *      checking if the output is NULL before using it. If the output is not  *
 *      NULL, it needs to be free'd when done with.                           *
 *  Source Code:                                                              *
 *      libtmpl/src/polynomial/tmpl_polynomial_z_get_string.c                 *
 ******************************************************************************/
extern char *tmpl_IntPolynomial_As_String(tmpl_IntPolynomial *poly);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_IntPolynomial_Print_String                                       *
 *  Purpose:                                                                  *
 *      Prints the contents of a polynomial to a file.                        *
 *  Arguments:                                                                *
 *      fp (FILE *):                                                          *
 *          A pointer to a FILE, the file the polynomial is printed to.       *
 *      poly (tmpl_PolynomialZ *):                                            *
 *          A pointer to a polynomial.                                        *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      If poly->error_occurred is true, or if poly->coeffs = NULL, or if     *
 *      poly = NULL, nothing is printed.                                      *
 *  Source Code:                                                              *
 *      libtmpl/src/polynomial/tmpl_polynomial_z_print_string.c               *
 ******************************************************************************/
extern void tmpl_IntPolynomial_Print_String(FILE *fp, tmpl_IntPolynomial *poly);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PolynomialZ_Subtract                                             *
 *  Purpose:                                                                  *
 *      Subtracts two elements of Z[x].                                       *
 *  Arguments:                                                                *
 *      P (tmpl_PolynomialZ *):                                               *
 *          A pointer to a polynomial.                                        *
 *      Q (tmpl_PolynomialZ *):                                               *
 *          Another pointer to a polynomial.                                  *
 *      diff (tmpl_PolynomialZ *):                                            *
 *          A pointer to a polynomial, the value P - Q will be stored in it.  *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      It is assumed none of the three input polynomials are NULL. If        *
 *      sum has it's degree not equal to the max of the two degrees of P and  *
 *      Q realloc will be called on the coeffs pointer.                       *
 *  Source Code:                                                              *
 *      libtmpl/src/polynomial/tmpl_subtract_polynomial_z.c                   *
 *  Examples:                                                                 *
 *      libtmpl/examples/polynomial/tmpl_subtract_polynomial_z_example_001.c  *
 ******************************************************************************/
extern void
tmpl_IntPolynomial_Subtract(tmpl_IntPolynomial *P,
                            tmpl_IntPolynomial *Q,
                            tmpl_IntPolynomial *diff);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PolynomialZ_Set_Term                                             *
 *  Purpose:                                                                  *
 *      Set the coefficient of a given term to the given value.               *
 *  Arguments:                                                                *
 *      poly (tmpl_PolynomialZ *):                                            *
 *          A pointer to a polynomial.                                        *
 *      term (size_t):                                                        *
 *          The term to be set.                                               *
 *      value (int):                                                          *
 *          The value to be set for the term.                                 *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      If term is greater than poly->degree, the poly->coeffs pointer is     *
 *      realloced, the values between poly->degree and term are set to zero,  *
 *      and the last value is set to the given coefficient.                   *
 *  Source Code:                                                              *
 *      libtmpl/src/polynomial/tmpl_polynomial_z_set_term.c                   *
 ******************************************************************************/
extern void
tmpl_IntPolynomial_SetTerm(tmpl_IntPolynomial *poly, size_t term, int value);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_IntPolynomial_Shrink                                             *
 *  Purpose:                                                                  *
 *      Removes all zero terms with after the last non-zero term. This        *
 *      effectively "shrinks" the size of the coefficients array.             *
 *  Arguments:                                                                *
 *      poly (tmpl_PolynomialZ *):                                            *
 *          A pointer to a polynomial.                                        *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      If realloc fails the error_occurred Boolean is set to true.           *
 ******************************************************************************/
extern void tmpl_IntPolynomial_Shrink(tmpl_IntPolynomial *poly);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PolynomialZ_Deriv                                                *
 *  Purpose:                                                                  *
 *      Computes the derivative of a polynomial in Z[x].                      *
 *  Arguments:                                                                *
 *      poly (tmpl_PolynomialZ *):                                            *
 *          A pointer to a polynomial.                                        *
 *      poly (tmpl_PolynomialZ *):                                            *
 *          A pointer to a polynomial, the derivative will be stored in it.   *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Source Code:                                                              *
 *      libtmpl/src/polynomial/tmpl_polynomial_z_deriv.c                      *
 *  Examples:                                                                 *
 *      libtmpl/examples/polynomial/tmpl_deriv_polynomial_z_example_001.c     *
 *      libtmpl/examples/polynomial/tmpl_deriv_polynomial_z_example_002.c     *
 *      libtmpl/examples/polynomial/tmpl_deriv_polynomial_z_example_003.c     *
 ******************************************************************************/
extern void
tmpl_IntPolynomial_Deriv(tmpl_IntPolynomial *poly, tmpl_IntPolynomial *deriv);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PolynomialZ_Scale                                                *
 *  Purpose:                                                                  *
 *      Multiply a polynomial by an integer.                                  *
 *  Arguments:                                                                *
 *      poly (tmpl_PolynomialZ *):                                            *
 *          A pointer to a polynomial.                                        *
 *      scale (signed long int):                                              *
 *          The integer the polynomial is multiplied with.                    *
 *      prod (tmpl_PolynomialZ *):                                            *
 *          The product of poly and scale.                                    *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Source Code:                                                              *
 *      libtmpl/src/polynomial/tmpl_polynomial_z_scale.c                      *
 ******************************************************************************/
extern void
tmpl_IntPolynomial_Scale(const tmpl_IntPolynomial *poly,
                         int scale, tmpl_IntPolynomial *prod);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PolynomialZ_ScaleSelf                                            *
 *  Purpose:                                                                  *
 *      Multiply a polynomial by an integer.                                  *
 *  Arguments:                                                                *
 *      poly (tmpl_PolynomialZ *):                                            *
 *          A pointer to a polynomial.                                        *
 *      scale (signed long int):                                              *
 *          The integer the polynomial is multiplied with.                    *
 *      prod (tmpl_PolynomialZ *):                                            *
 *          The product of poly and scale.                                    *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Source Code:                                                              *
 *      libtmpl/src/polynomial/tmpl_polynomial_z_scale.c                      *
 ******************************************************************************/
extern void
tmpl_IntPolynomial_ScaleSelf(tmpl_IntPolynomial *poly, int scale);

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
/*  End of include guard.                                                     */
