/******************************************************************************
 *                                 LICENSE                                    *
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
 *                             tmpl_polynomial                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide data types for working with polynomials.                      *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file containing Booleans.                                  *
 *  2.) tmpl_rational.h:                                                      *
 *          Header file containing a data type for working with rational      *
 *          numbers.                                                          *
 *  3.) tmpl_complex.h:                                                       *
 *          Header file containing complex data types.                        *
 *  4.) stdio.h:                                                              *
 *          Standard C header file containing the FILE data type.             *
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                            A FRIENDLY WARNING                              *
 ******************************************************************************
 *  This code is compatible with the C89/C90 standard. The setup script that  *
 *  is used to compile this in make.sh uses gcc and has the                   *
 *  -pedantic and -std=c89 flags to check for compliance. If you edit this to *
 *  use C99 features (built-in complex, built-in booleans, C++ style comments *
 *  and etc.), or GCC extensions, you will need to edit the config script.    *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       June 15, 2021                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_POLYNOMIAL_H
#define TMPL_POLYNOMIAL_H

/*  Booleans located here.                                                    */
#include <libtmpl/include/tmpl_bool.h>

/*  Rational numbers found here.                                              */
#include <libtmpl/include/tmpl_rational.h>

/*  And lastly, complex numbers are here.                                     */
#include <libtmpl/include/tmpl_complex.h>

/*  The FILE data type is found here.                                         */
#include <stdio.h>

/*  Data type for working with elements of Z[x]. That is, polynomials with    *
 *  integer coefficients.                                                     */
typedef struct _tmpl_PolynomialZ {
    /*  A single pointer to a SIGNED long int array will contain the          *
     *  coefficients in the order a_0 + a_1 x + ... + a_N x^N.                */
    signed long int *coeffs;

    /*  The degree of the polynomial. A polynomial will have degree + 1       *
     *  elements.                                                             */
    unsigned long int degree;

    /*  Boolean for keeping track of errors.                                  */
    tmpl_Bool error_occurred;

    /*  And an error message in case an error does occur.                     */
    char *error_message;
} tmpl_PolynomialZ;

/*  Data type for working with elements of Z[x] that are of a high degree     *
 *  where most of the coefficients are zero. This method saves on memory.     */
typedef struct _tmpl_SparsePolynomialZ {
    /*  A pointer to all of the terms. The degree of the terms is stored in   *
     *  the next pointer.                                                     */
    signed long int *terms;

    /*  A pointer for the degrees of all of the terms.                        */
    unsigned long int *degree_of_term;

    /*  The number of non-zero terms.                                         */
    unsigned long int size;

    /*  Boolean for keeping track of errors.                                  */
    tmpl_Bool error_occurred;

    /*  And an error message in case an error does occur.                     */
    char *error_message;
} tmpl_SparsePolynomialZ;

/*  Data type for matrices of polynomials in Z[x].                            */
typedef struct _tmpl_PolynomialZMatrix {
    /*  An array of polynomials, representing the matrix.                     */
    tmpl_PolynomialZ **data;

    /*  The number of rows and columns, respectively.                         */
    unsigned long int number_of_rows;
    unsigned long int number_of_columns;

    /*  Boolean for keeping track of errors.                                  */
    tmpl_Bool error_occurred;

    /*  And an error message in case an error does occur.                     */
    char *error_message;
} tmpl_PolynomialZMatrix;

typedef struct _tmpl_PolynomialQ {
    tmpl_RationalNumber *coeffs;
    unsigned long int degree;
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_PolynomialQ;

typedef struct _tmpl_PolynomialQMatrix {
    tmpl_PolynomialQ **data;
    unsigned long int number_of_rows;
    unsigned long int number_of_columns;
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_PolynomialQMatrix;

typedef struct _tmpl_PolynomialR {
    double *coeffs;
    unsigned long int degree;
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_PolynomialR;

typedef struct _tmpl_PolynomialC {
    tmpl_ComplexDouble *coeffs;
    unsigned long int degree;
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_PolynomialC;

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Create_Zero_PolynomialZ                                          *
 *  Purpose:                                                                  *
 *      Creates a polynomial in Z[x] with the coefficients set to zero.       *
 *  Arguments:                                                                *
 *      degree (unsigned long int).                                           *
 *          The degree of the polynomial. Mathematically, since all of the    *
 *          coefficients are zero, the degree is zero. But computer-wise      *
 *          the coeffs pointer will have degree + 1 elements allocated to it. *
 *  Output:                                                                   *
 *      poly (tmpl_PolynomialZ *):                                            *
 *          A pointer to a polynomial with all coefficients set to zero.      *
 *  Notes:                                                                    *
 *      If malloc fails this function returns NULL. If calloc fails, the      *
 *      pointer has the error_occurred Boolean set to True.                   *
 *  Source Code:                                                              *
 *      libtmpl/src/polynomial/tmpl_create_zero_polynomial_z.c                *
 ******************************************************************************/
extern tmpl_PolynomialZ *
tmpl_Create_Zero_PolynomialZ(unsigned long int degree);

extern tmpl_PolynomialQ *
tmpl_Create_Zero_PolynomialQ(unsigned long int degree);

extern tmpl_PolynomialR *
tmpl_Create_Zero_PolynomialR(unsigned long int degree);

extern tmpl_PolynomialC *
tmpl_Create_Zero_PolynomialC(unsigned long int degree);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Create_Empty_PolynomialZ                                         *
 *  Purpose:                                                                  *
 *      Creates an empty polynomial in Z[x]. The coeffs pointer is NULL and   *
 *      the degree is set to zero.                                            *
 *  Arguments:                                                                *
 *      None (void).                                                          *
 *  Output:                                                                   *
 *      poly (tmpl_PolynomialZ *):                                            *
 *          A pointer to a polynomial with coefficiets set to NULL.           *
 *  Notes:                                                                    *
 *      If malloc fails this function returns NULL.                           *
 *  Source Code:                                                              *
 *      libtmpl/src/polynomial/tmpl_create_empty_polynomial_z.c               *
 ******************************************************************************/
extern tmpl_PolynomialZ *
tmpl_Create_Empty_PolynomialZ(void);

extern tmpl_PolynomialQ *
tmpl_Create_Empty_PolynomialQ(void);

extern tmpl_PolynomialR *
tmpl_Create_Empty_PolynomialR(void);

extern tmpl_PolynomialC *
tmpl_Create_Empty_PolynomialC(void);

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
 *      libtmpl/src/polynomial/tmpl_destroy_polynomial_z.c                    *
 ******************************************************************************/
extern void
tmpl_Destroy_PolynomialZ(tmpl_PolynomialZ **poly_ptr);

extern void
tmpl_Destroy_PolynomialQ(tmpl_PolynomialQ **poly_ptr);

extern void
tmpl_Destroy_PolynomialR(tmpl_PolynomialR **poly_ptr);

extern void
tmpl_Destroy_PolynomialC(tmpl_PolynomialC **poly_ptr);

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
extern char *
tmpl_PolynomialZ_Get_String(tmpl_PolynomialZ *poly);

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

#endif
