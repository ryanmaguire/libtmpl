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
 *                              tmpl_polynomial                               *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide data types for working with polynomials.                      *
 ******************************************************************************
 *                                DEPENDENCIES                                *
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
 *                             A NOTE ON COMMENTS                             *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                             A FRIENDLY WARNING                             *
 ******************************************************************************
 *  This code is compatible with the C89/C90 standard. The setup script that  *
 *  is used to compile this in make.sh uses gcc and has the                   *
 *  -pedantic and -std=c89 flags to check for compliance. If you edit this to *
 *  use C99 features (built-in complex, built-in booleans, C++ style comments *
 *  and etc.), or GCC extensions, you will need to edit the config script.    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 15, 2021                                                 *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/02/01: Ryan Maguire                                                  *
 *      Getting rid of -Wreserved-identifier warnings with clang.             *
 *  2022/02/15: Ryan Maguire                                                  *
 *      Changing overall layout of polynomials.                               *
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

/*  Polynomials with integer coefficients, elements of Z[x].                  */
typedef struct tmpl_PolynomialZ_Def {

    /*  A pointer to a SIGNED long int array containing the coefficients.     */
    signed long int *coeffs;

    /*  The number of elements in the coeffs array.                           */
    unsigned long int number_of_coeffs;

    /*  The smallest degree in the polynomial. The degree of the nth term in  *
     *  the coeffs array is min_degree + n;                                   */
    unsigned long int min_degree;

    /*  Boolean for keeping track of the coeffs pointer.                      */
    tmpl_Bool coeffs_can_be_freed;

    /*  Boolean for keeping track of the entire polynomial.                   */
    tmpl_Bool poly_can_be_freed;

    /*  Boolean for keeping track of errors.                                  */
    tmpl_Bool error_occurred;

    /*  And an error message in case an error does occur.                     */
    char *error_message;
} tmpl_PolynomialZ;

/*  Polynomials with rational coefficients, elements of Q[x].                 */
typedef struct tmpl_PolynomialQ_Def {

    /*  A pointer to a rational number array containing the coefficients.     */
    tmpl_RationalNumber *coeffs;

    /*  The number of elements in the coeffs array.                           */
    unsigned long int number_of_coeffs;

    /*  The smallest degree in the polynomial. The degree of the nth term in  *
     *  the coeffs array is min_degree + n;                                   */
    unsigned long int min_degree;

    /*  Boolean for keeping track of the coeffs pointer.                      */
    tmpl_Bool coeffs_can_be_freed;

    /*  Boolean for keeping track of the entire polynomial.                   */
    tmpl_Bool poly_can_be_freed;

    /*  Boolean for keeping track of errors.                                  */
    tmpl_Bool error_occurred;

    /*  And an error message in case an error does occur.                     */
    char *error_message;
} tmpl_PolynomialQ;

/*  Polynomials with real coefficients, elements of R[x].                     */
typedef struct tmpl_PolynomialR_Def {

    /*  A pointer to a real number array containing the coefficients.         */
    double *coeffs;

    /*  The number of elements in the coeffs array.                           */
    unsigned long int number_of_coeffs;

    /*  The smallest degree in the polynomial. The degree of the nth term in  *
     *  the coeffs array is min_degree + n;                                   */
    unsigned long int min_degree;

    /*  Boolean for keeping track of the coeffs pointer.                      */
    tmpl_Bool coeffs_can_be_freed;

    /*  Boolean for keeping track of the entire polynomial.                   */
    tmpl_Bool poly_can_be_freed;

    /*  Boolean for keeping track of errors.                                  */
    tmpl_Bool error_occurred;

    /*  And an error message in case an error does occur.                     */
    char *error_message;
} tmpl_PolynomialR;

/*  Polynomials with complex coefficients, elements of R[x].                  */
typedef struct tmpl_PolynomialC_Def {

    /*  A pointer to a complex number array containing the coefficients.      */
    tmpl_ComplexDouble *coeffs;

    /*  The number of elements in the coeffs array.                           */
    unsigned long int number_of_coeffs;

    /*  The smallest degree in the polynomial. The degree of the nth term in  *
     *  the coeffs array is min_degree + n;                                   */
    unsigned long int min_degree;

    /*  Boolean for keeping track of the coeffs pointer.                      */
    tmpl_Bool coeffs_can_be_freed;

    /*  Boolean for keeping track of the entire polynomial.                   */
    tmpl_Bool poly_can_be_freed;

    /*  Boolean for keeping track of errors.                                  */
    tmpl_Bool error_occurred;

    /*  And an error message in case an error does occur.                     */
    char *error_message;
} tmpl_PolynomialC;

/*  Data type for working with elements of Z[x] that are of a high degree     *
 *  where most of the coefficients are zero. This method saves on memory.     */
typedef struct tmpl_SparsePolynomialZ_Def {

    /*  A pointer to all of the terms. The degree of the terms is stored in   *
     *  the next pointer.                                                     */
    signed long int *terms;

    /*  A pointer for the degrees of all of the terms.                        */
    unsigned long int *degree_of_term;

    /*  The number of non-zero terms.                                         */
    unsigned long int number_of_terms;

    /*  Boolean for keeping track of the terms pointer.                       */
    tmpl_Bool terms_can_be_freed;

    /*  Boolean for keeping track of the entire polynomial.                   */
    tmpl_Bool poly_can_be_freed;

    /*  Boolean for keeping track of errors.                                  */
    tmpl_Bool error_occurred;

    /*  And an error message in case an error does occur.                     */
    char *error_message;
} tmpl_SparsePolynomialZ;

/*  Data type for working with elements of Q[x] that are of a high degree     *
 *  where most of the coefficients are zero. This method saves on memory.     */
typedef struct tmpl_SparsePolynomialQ_Def {

    /*  A pointer to all of the terms. The degree of the terms is stored in   *
     *  the next pointer.                                                     */
    tmpl_RationalNumber *terms;

    /*  A pointer for the degrees of all of the terms.                        */
    unsigned long int *degree_of_term;

    /*  The number of non-zero terms.                                         */
    unsigned long int number_of_terms;

    /*  Boolean for keeping track of the terms pointer.                       */
    tmpl_Bool terms_can_be_freed;

    /*  Boolean for keeping track of the entire polynomial.                   */
    tmpl_Bool poly_can_be_freed;

    /*  Boolean for keeping track of errors.                                  */
    tmpl_Bool error_occurred;

    /*  And an error message in case an error does occur.                     */
    char *error_message;
} tmpl_SparsePolynomialQ;

/*  Data type for working with elements of R[x] that are of a high degree     *
 *  where most of the coefficients are zero. This method saves on memory.     */
typedef struct tmpl_SparsePolynomialR_Def {

    /*  A pointer to all of the terms. The degree of the terms is stored in   *
     *  the next pointer.                                                     */
    double *terms;

    /*  A pointer for the degrees of all of the terms.                        */
    unsigned long int *degree_of_term;

    /*  The number of non-zero terms.                                         */
    unsigned long int number_of_terms;

    /*  Boolean for keeping track of the terms pointer.                       */
    tmpl_Bool terms_can_be_freed;

    /*  Boolean for keeping track of the entire polynomial.                   */
    tmpl_Bool poly_can_be_freed;

    /*  Boolean for keeping track of errors.                                  */
    tmpl_Bool error_occurred;

    /*  And an error message in case an error does occur.                     */
    char *error_message;
} tmpl_SparsePolynomialR;

/*  Data type for working with elements of C[x] that are of a high degree     *
 *  where most of the coefficients are zero. This method saves on memory.     */
typedef struct tmpl_SparsePolynomialC_Def {

    /*  A pointer to all of the terms. The degree of the terms is stored in   *
     *  the next pointer.                                                     */
    tmpl_ComplexDouble *terms;

    /*  A pointer for the degrees of all of the terms.                        */
    unsigned long int *degree_of_term;

    /*  The number of non-zero terms.                                         */
    unsigned long int number_of_terms;

    /*  Boolean for keeping track of the terms pointer.                       */
    tmpl_Bool terms_can_be_freed;

    /*  Boolean for keeping track of the entire polynomial.                   */
    tmpl_Bool poly_can_be_freed;

    /*  Boolean for keeping track of errors.                                  */
    tmpl_Bool error_occurred;

    /*  And an error message in case an error does occur.                     */
    char *error_message;
} tmpl_SparsePolynomialC;

/*  Data type for matrices of polynomials in Z[x].                            */
typedef struct tmpl_PolynomialZMatrix_Def {

    /*  An array of polynomials, representing the matrix.                     */
    tmpl_PolynomialZ *data;

    /*  The number of rows and columns, respectively.                         */
    unsigned long int number_of_rows;
    unsigned long int number_of_columns;

    /*  Boolean for keeping track of the data pointer.                        */
    tmpl_Bool data_can_be_freed;

    /*  Boolean for keeping track of the entire matrix.                       */
    tmpl_Bool matrix_can_be_freed;

    /*  Boolean for keeping track of errors.                                  */
    tmpl_Bool error_occurred;

    /*  And an error message in case an error does occur.                     */
    char *error_message;
} tmpl_PolynomialZMatrix;

/*  Data type for matrices of polynomials in Q[x].                            */
typedef struct tmpl_PolynomialQMatrix_Def {

    /*  An array of polynomials, representing the matrix.                     */
    tmpl_PolynomialQ *data;

    /*  The number of rows and columns, respectively.                         */
    unsigned long int number_of_rows;
    unsigned long int number_of_columns;

    /*  Boolean for keeping track of the data pointer.                        */
    tmpl_Bool data_can_be_freed;

    /*  Boolean for keeping track of the entire matrix.                       */
    tmpl_Bool matrix_can_be_freed;

    /*  Boolean for keeping track of errors.                                  */
    tmpl_Bool error_occurred;

    /*  And an error message in case an error does occur.                     */
    char *error_message;
} tmpl_PolynomialQMatrix;

/*  Data type for matrices of polynomials in R[x].                            */
typedef struct tmpl_PolynomialRMatrix_Def {

    /*  An array of polynomials, representing the matrix.                     */
    tmpl_PolynomialR *data;

    /*  The number of rows and columns, respectively.                         */
    unsigned long int number_of_rows;
    unsigned long int number_of_columns;

    /*  Boolean for keeping track of the data pointer.                        */
    tmpl_Bool data_can_be_freed;

    /*  Boolean for keeping track of the entire matrix.                       */
    tmpl_Bool matrix_can_be_freed;

    /*  Boolean for keeping track of errors.                                  */
    tmpl_Bool error_occurred;

    /*  And an error message in case an error does occur.                     */
    char *error_message;
} tmpl_PolynomialRMatrix;

/*  Data type for matrices of polynomials in C[x].                            */
typedef struct tmpl_PolynomialCMatrix_Def {

    /*  An array of polynomials, representing the matrix.                     */
    tmpl_PolynomialC *data;

    /*  The number of rows and columns, respectively.                         */
    unsigned long int number_of_rows;
    unsigned long int number_of_columns;

    /*  Boolean for keeping track of the data pointer.                        */
    tmpl_Bool data_can_be_freed;

    /*  Boolean for keeping track of the entire matrix.                       */
    tmpl_Bool matrix_can_be_freed;

    /*  Boolean for keeping track of errors.                                  */
    tmpl_Bool error_occurred;

    /*  And an error message in case an error does occur.                     */
    char *error_message;
} tmpl_PolynomialCMatrix;


/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_PolynomialZ_Create_Empty                                         *
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
extern tmpl_PolynomialZ *tmpl_PolynomialZ_Create_Empty(void);
extern tmpl_PolynomialQ *tmpl_PolynomialQ_Create_Empty(void);
extern tmpl_PolynomialR *tmpl_PolynomialR_Create_Empty(void);
extern tmpl_PolynomialC *tmpl_PolynomialC_Create_Empty(void);

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

#endif
