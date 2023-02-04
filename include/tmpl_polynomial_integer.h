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

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_POLYNOMIAL_INTEGER_H
#define TMPL_POLYNOMIAL_INTEGER_H

/*  Macro indicating whether libtmpl has long long support found here.        */
#include <libtmpl/include/tmpl_inttype.h>

/*  Booleans located here.                                                    */
#include <libtmpl/include/tmpl_bool.h>

/*  The size_t data type is found here.                                       */
#include <stddef.h>

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

/*  Data type for working with elements of Z[x] that are of a high degree     *
 *  where most of the coefficients are zero. This method saves on memory.     */
typedef struct tmpl_SparseIntPolynomial_Def {

    /*  A pointer to all of the terms. The degree of the terms is stored in   *
     *  the next pointer.                                                     */
    signed long int *terms;

    /*  A pointer for the degrees of all of the terms.                        */
    size_t *degree_of_term;

    /*  The number of non-zero terms.                                         */
    size_t number_of_terms;

    /*  Boolean for keeping track of errors.                                  */
    tmpl_Bool error_occurred;

    /*  And an error message in case an error does occur.                     */
    char *error_message;
} tmpl_SparseIntPolynomial;

/*  Data type for matrices of polynomials in Z[x].                            */
typedef struct tmpl_IntPolynomialMatrix_Def {

    /*  An array of polynomials, representing the matrix.                     */
    tmpl_IntPolynomial *data;

    /*  The number of rows and columns, respectively.                         */
    size_t number_of_rows;
    size_t number_of_columns;

    /*  Boolean for keeping track of errors.                                  */
    tmpl_Bool error_occurred;

    /*  And an error message in case an error does occur.                     */
    char *error_message;
} tmpl_IntPolynomialMatrix;

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PolynomialZ_Calloc                                               *
 *  Purpose:                                                                  *
 *      Creates a polynomial in Z[x] with number_of_coeffs elements allocated *
 *      for the coeffs array, all of which are initialized to zero. Similar   *
 *      functions are provided for Q[x], R[x], and C[x].                      *
 *  Arguments:                                                                *
 *      number_of_coeffs (unsigned long int).                                 *
 *          The number of elements allocated to the coeffs array. All         *
 *          elements will be initialized to zero.                             *
 *  Output:                                                                   *
 *      poly (tmpl_PolynomialZ *):                                            *
 *          A pointer to a polynomial with all coefficients set to zero.      *
 *  Notes:                                                                    *
 *      If malloc fails this function returns NULL. If calloc fails, the      *
 *      pointer has the error_occurred Boolean set to True.                   *
 *  Source Code:                                                              *
 *      libtmpl/src/polynomial/tmpl_polynomial_calloc.c                       *
 ******************************************************************************/
extern tmpl_ShortPolynomial tmpl_ShortPolynomial_Calloc(size_t length);
extern tmpl_IntPolynomial tmpl_IntPolynomial_Calloc(size_t length);
extern tmpl_LongPolynomial tmpl_LongPolynomial_Calloc(size_t length);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_IntPolynomial_Init                                               *
 *  Purpose:                                                                  *
 *      Creates a polynomial in Z[x] with all pointers set to NULL and all    *
 *      variables set to 0. Similar functions are provided for Q[x], R[x],    *
 *      C[x] for rational, real, and complex polynomials, respectively.       *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      poly (tmpl_PolynomialZ *):                                            *
 *          A pointer to a polynomial with coeffs pointer set to NULL.        *
 *  Notes:                                                                    *
 *      If malloc fails this function returns NULL.                           *
 *  Source Code:                                                              *
 *      libtmpl/src/polynomial/tmpl_polynomial_create_empty.c                 *
 ******************************************************************************/
extern tmpl_ShortPolynomial tmpl_ShortPolynomial_Init(void);
extern tmpl_IntPolynomial tmpl_IntPolynomial_Init(void);
extern tmpl_LongPolynomial tmpl_LongPolynomial_Init(void);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Destroy_PolynomialZ                                              *
 *  Purpose:                                                                  *
 *      Free all of the memory in a tmpl_PolynomialZ pointer and set the      *
 *      the pointers inside the struct to NULL.                               *
 *  Arguments:                                                                *
 *      poly_ptr (tmpl_PolynomialZ **)                                        *
 *          A pointer a tmpl_PolynomialZ pointer whose memory needs to be     *
 *          freed. Given a tmpl_Polynomial pointer poly, pass it to this      *
 *          function by grabbing the address &poly.                           *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      This function should always be called when done with a polynomial     *
 *      to avoid memory leaks.                                                *
 *  Source Code:                                                              *
 *      libtmpl/src/polynomial/tmpl_polynomial_destroy.c                      *
 ******************************************************************************/
extern void tmpl_ShortPolynomial_Destroy(tmpl_ShortPolynomial *poly_ptr);
extern void tmpl_IntPolynomial_Destroy(tmpl_IntPolynomial *poly_ptr);
extern void tmpl_LongPolynomial_Destroy(tmpl_LongPolynomial *poly_ptr);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PolynomialZ_Multiply                                             *
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
 *  Notes:                                                                    *
 *      It is assumed none of the three input polynomials are NULL. If        *
 *      prod has it's degree not equal the sum of the two degrees of P and Q, *
 *      realloc will be called on the coeffs pointer.                         *
 *  Source Code:                                                              *
 *      libtmpl/src/polynomial/tmpl_multiply_polynomial_z.c                   *
 *  Examples:                                                                 *
 *      libtmpl/examples/bytes/tmpl_determine_endianness_example.c            *
 ******************************************************************************/
extern void
tmpl_PolynomialZ_Multiply(tmpl_PolynomialZ *P,
                          tmpl_PolynomialZ *Q,
                          tmpl_PolynomialZ *prod);

extern void
tmpl_PolynomialQ_Multiply(tmpl_PolynomialQ *P,
                          tmpl_PolynomialQ *Q,
                          tmpl_PolynomialQ *prod);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PolynomialZ_Get_String                                           *
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
 *      tmpl_PolynomialZ_Print_String                                         *
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
extern void
tmpl_PolynomialZ_Print_String(FILE *fp, tmpl_PolynomialZ *poly);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PolynomialZ_Add                                                  *
 *  Purpose:                                                                  *
 *      Adds two elements of Z[x].                                            *
 *  Arguments:                                                                *
 *      P (tmpl_PolynomialZ *):                                               *
 *          A pointer to a polynomial.                                        *
 *      Q (tmpl_PolynomialZ *):                                               *
 *          Another pointer to a polynomial.                                  *
 *      sum (tmpl_PolynomialZ *):                                             *
 *          A pointer to a polynomial, the value P + Q will be stored in it.  *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      It is assumed none of the three input polynomials are NULL. If        *
 *      sum has it's degree not equal to the max of the two degrees of P and  *
 *      Q realloc will be called on the coeffs pointer.                       *
 *  Source Code:                                                              *
 *      libtmpl/src/polynomial/tmpl_polynomial_z_add.c                        *
 *  Examples:                                                                 *
 *      libtmpl/examples/polynomial/tmpl_add_polynomial_z_example_001.c       *
 *      libtmpl/examples/polynomial/tmpl_add_polynomial_z_example_002.c       *
 *      libtmpl/examples/polynomial/tmpl_add_polynomial_z_example_003.c       *
 *      libtmpl/examples/polynomial/tmpl_add_polynomial_z_example_004.c       *
 *      libtmpl/examples/polynomial/tmpl_add_polynomial_z_example_005.c       *
 ******************************************************************************/
extern void
tmpl_PolynomialZ_Add(tmpl_PolynomialZ *P,
                     tmpl_PolynomialZ *Q,
                     tmpl_PolynomialZ *sum);

extern void
tmpl_PolynomialQ_Add(tmpl_PolynomialQ *P,
                     tmpl_PolynomialQ *Q,
                     tmpl_PolynomialQ *sum);

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
tmpl_PolynomialZ_Subtract(tmpl_PolynomialZ *P,
                          tmpl_PolynomialZ *Q,
                          tmpl_PolynomialZ *diff);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PolynomialZ_Set_Term                                             *
 *  Purpose:                                                                  *
 *      Set the coefficient of a given term to the given value.               *
 *  Arguments:                                                                *
 *      poly (tmpl_PolynomialZ *):                                            *
 *          A pointer to a polynomial.                                        *
 *      term (unsigned long int):                                             *
 *          The term to be set.                                               *
 *      coefficient (signed long int):                                        *
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
tmpl_PolynomialZ_Set_Term(tmpl_PolynomialZ *poly,
                          unsigned long int term,
                          signed long int coefficient);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PolynomialZ_Extract_Term                                         *
 *  Purpose:                                                                  *
 *      Extract the coefficient of a given term.                              *
 *  Arguments:                                                                *
 *      poly (tmpl_PolynomialZ *):                                            *
 *          A pointer to a polynomial.                                        *
 *      term (unsigned long int):                                             *
 *          The term to be extracted.                                         *
 *  Output:                                                                   *
 *      coefficient (signed lont int):                                        *
 *          The value of the given term.                                      *
 *  Notes:                                                                    *
 *      If poly is NULL, poly->error_occurred is true, poly->degree < term,   *
 *      or if poly->coeffs = NULL, the value 0 is returned.                   *
 *  Source Code:                                                              *
 *      libtmpl/src/polynomial/tmpl_polynomial_z_extract_term.c               *
 ******************************************************************************/
extern signed long int
tmpl_PolynomialZ_Extract_Term(tmpl_PolynomialZ *poly, unsigned long int term);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PolynomialZ_Shrink                                               *
 *  Purpose:                                                                  *
 *      Removes all non-zero terms with after the last non-zero term. This    *
 *      effectively "shrinks" the size of the coefficients array.             *
 *  Arguments:                                                                *
 *      poly (tmpl_PolynomialZ *):                                            *
 *          A pointer to a polynomial.                                        *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      If realloc fails, the error_occurred Boolean is set to true.          *
 *  Source Code:                                                              *
 *      libtmpl/src/polynomial/tmpl_polynomial_z_shrink.c                     *
 ******************************************************************************/
extern void
tmpl_PolynomialZ_Shrink(tmpl_PolynomialZ *poly);

extern void
tmpl_PolynomialQ_Shrink(tmpl_PolynomialQ *poly);

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
tmpl_PolynomialZ_Deriv(tmpl_PolynomialZ *poly, tmpl_PolynomialZ *deriv);

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
tmpl_PolynomialZ_Scale(tmpl_PolynomialZ *poly,
                       signed long int scale,
                       tmpl_PolynomialZ *prod);

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
tmpl_PolynomialZ_ScaleSelf(tmpl_PolynomialZ *poly, signed long int scale);

extern void
tmpl_PolynomialQ_ScaleSelf(tmpl_PolynomialQ *poly, tmpl_RationalNumber scale);

extern void
tmpl_PolynomialR_ScaleSelf(tmpl_PolynomialR *poly, double scale);

extern void
tmpl_PolynomialC_ScaleSelf(tmpl_PolynomialC *poly, tmpl_ComplexDouble scale);

#endif
