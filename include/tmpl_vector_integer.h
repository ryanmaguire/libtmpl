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
 *                            tmpl_vector_integer                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide tools for working with vectors with integer, rational, real,  *
 *      or complex entries.                                                   *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) stdef.h:                                                              *
 *          Standard header file with size_t typedef.                         *
 *  1.) tmpl_bool.h:                                                          *
 *          Header file which typedef's Boolean types for C89/C90 compilers.  *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 13, 2021                                                  *
 ******************************************************************************
 *                              Revision History                              *
 ******************************************************************************
 *  2022/02/01: Ryan Maguire                                                  *
 *      Getting rid of -Wreserved-identifier warnings with clang.             *
 *  2022/12/22: Ryan Maguire                                                  *
 *      Splitting vector code into integer, real, and complex versions.       *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VECTOR_INTEGER_H
#define TMPL_VECTOR_INTEGER_H

/*  If using with C++ (and not C), wrap the entire header file in an extern   *
 *  "C" statement. Check if C++ is being used with __cplusplus.               */
#ifdef __cplusplus
extern "C" {
#endif

/*  size_t typedef given here.                                                */
#include <stddef.h>

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/******************************************************************************
 *                         Integer Valued Vectors                             *
 ******************************************************************************/

typedef struct tmpl_CharVector_Def {
    char *data;
    size_t length;

    /*  In the event of an error, this Boolean is set to true and a string    *
     *  detailing the error is stored in the error_message pointer.           */
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_CharVector;

typedef struct tmpl_UCharVector_Def {
    unsigned char *data;
    size_t length;
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_UCharVector;

typedef struct tmpl_ShortVector_Def {
    short int *data;
    size_t length;
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_ShortVector;

typedef struct tmpl_UShortVector_Def {
    unsigned short int *data;
    size_t length;
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_UShortVector;

typedef struct tmpl_IntVector_Def {
    int *data;
    size_t length;
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_IntVector;

typedef struct tmpl_UIntVector_Def {
    unsigned int *data;
    size_t length;
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_UIntVector;

typedef struct tmpl_LongVector_Def {
    long int *data;
    size_t length;
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_LongVector;

typedef struct tmpl_ULongVector_Def {
    unsigned long int *data;
    size_t length;
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_ULongVector;

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Create_Empty_IntVector                                           *
 *  Purpose:                                                                  *
 *      Creates a tmpl_FloatVector and allocates memory for the data.         *
 *  Arguments:                                                                *
 *      length (size_t):                                                      *
 *          The desired length of the vector.                                 *
 *  Output:                                                                   *
 *    vec (tmpl_FloatVector *):                                               *
 *        A pointer to a tmpl_FloatVector with memory allocated for the       *
 *        data. The data is not initialized.                                  *
 *  Called Functions:                                                         *
 *      malloc      (stdlib.h)                                                *
 *      tmpl_strdup (tmpl_string.h)                                           *
 *  Source Code:                                                              *
 *      libtmpl/src/vector/tmpl_create_empty_real_vector.c                    *
 *      libtmpl/src/vector/tmpl_create_empty_char_vector.c                    *
 *      libtmpl/src/vector/tmpl_create_empty_short_vector.c                   *
 *      libtmpl/src/vector/tmpl_create_empty_int_vector.c                     *
 *      libtmpl/src/vector/tmpl_create_empty_long_vector.c                    *
 ******************************************************************************/
TMPL_EXPORT externmpl_CharVector *tmpl_Create_Empty_CharVector(size_t length);
TMPL_EXPORT externmpl_UCharVector *tmpl_Create_Empty_UCharVector(size_t length);
TMPL_EXPORT externmpl_ShortVector *tmpl_Create_Empty_ShortVector(size_t length);
TMPL_EXPORT externmpl_UShortVector *tmpl_Create_Empty_UShortVector(size_t length);
TMPL_EXPORT externmpl_IntVector *tmpl_Create_Empty_IntVector(size_t length);
TMPL_EXPORT externmpl_UIntVector *tmpl_Create_Empty_UIntVector(size_t length);
TMPL_EXPORT externmpl_LongVector *tmpl_Create_Empty_LongVector(size_t length);
TMPL_EXPORT externmpl_ULongVector *tmpl_Create_Empty_ULongVector(size_t length);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Create_FloatVector_From_Data                                     *
 *  Purpose:                                                                  *
 *      Creates a tmpl_FloatVector from a pointer to a float array.           *
 *      Double, long double, int, short, and long equivalents are provided.   *
 *  Arguments:                                                                *
 *      arr (float *):                                                        *
 *          A pointer to a float array containing the data to be stored in    *
 *          the vector.                                                       *
 *      length (unsigned long int):                                           *
 *          The length of the float array.                                    *
 *  Output:                                                                   *
 *    vec (tmpl_FloatVector *):                                               *
 *          A pointer to a tmpl_FloatVector which contains the float array    *
 *          pointed to by arr as its data.                                    *
 *  Called Functions:                                                         *
 *      malloc      (stdlib.h):                                               *
 *      tmpl_strdup (tmpl_string.h)                                           *
 *  Notes:                                                                    *
 *      The data pointed to by arr is COPIED, not stolen. You will still need *
 *      to free arr if malloc was used with it. If length is non-zero, but    *
 *      arr is NULL, the data is set to NULL and an error message is stored   *
 *      in the vector.                                                        *
 *  Source Code:                                                              *
 *      libtmpl/src/vector/tmpl_create_real_vector_from_data.c                *
 ******************************************************************************/
TMPL_EXPORT externmpl_CharVector *
tmpl_Create_CharVector_From_Data(char *v, size_t length);

TMPL_EXPORT externmpl_UCharVector *
tmpl_Create_UCharVector_From_Data(unsigned char *v, size_t length);

TMPL_EXPORT externmpl_ShortVector *
tmpl_Create_ShortVector_From_Data(short int *v, size_t length);

TMPL_EXPORT externmpl_UShortVector *
tmpl_Create_UShortVector_From_Data(unsigned short int *v, size_t length);

TMPL_EXPORT externmpl_IntVector *
tmpl_Create_IntVector_From_Data(int *v, unsigned long length);

TMPL_EXPORT externmpl_UIntVector *
tmpl_Create_UIntVector_From_Data(unsigned int *v, size_t length);

TMPL_EXPORT externmpl_LongVector *
tmpl_Create_LongVector_From_Data(long int *v, size_t length);

TMPL_EXPORT externmpl_ULongVector *
tmpl_Create_ULongVector_From_Data(unsigned long int *v, size_t length);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Create_Zero_FloatVector                                          *
 *  Purpose:                                                                  *
 *      Creates a tmpl_FloatVector and set all the entries to zero.           *
 *  Arguments:                                                                *
 *      length (unsigned long int):                                           *
 *          The desired length of the vector.                                 *
 *  Output:                                                                   *
 *    vec (tmpl_FloatVector *):                                               *
 *        A pointer to a tmpl_FloatVector with all entries set to zero.       *
 *  Called Functions:                                                         *
 *      malloc      (stdlib.h)                                                *
 *      tmpl_strdup (tmpl_string.h)                                           *
 *  Source Code:                                                              *
 *      libtmpl/src/vector/tmpl_create_zero_real_vector.c                     *
 *      libtmpl/src/vector/tmpl_create_zero_char_vector.c                     *
 *      libtmpl/src/vector/tmpl_create_zero_short_vector.c                    *
 *      libtmpl/src/vector/tmpl_create_zero_int_vector.c                      *
 *      libtmpl/src/vector/tmpl_create_zero_long_vector.c                     *
 ******************************************************************************/
TMPL_EXPORT externmpl_CharVector *tmpl_Create_Zero_CharVector(size_t length);
TMPL_EXPORT externmpl_UCharVector *tmpl_Create_Zero_UCharVector(size_t length);
TMPL_EXPORT externmpl_ShortVector *tmpl_Create_Zero_ShortVector(size_t length);
TMPL_EXPORT externmpl_UShortVector *tmpl_Create_Zero_UShortVector(size_t length);
TMPL_EXPORT externmpl_IntVector *tmpl_Create_Zero_IntVector(size_t length);
TMPL_EXPORT externmpl_UIntVector *tmpl_Create_Zero_UIntVector(size_t length);
TMPL_EXPORT externmpl_LongVector *tmpl_Create_Zero_LongVector(size_t length);
TMPL_EXPORT externmpl_ULongVector *tmpl_Create_Zero_ULongVector(size_t length);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Destroy_FloatVector                                              *
 *  Purpose:                                                                  *
 *      Frees all memory allocated to a tmpl_FloatVector. It sets the data    *
 *      pointer to NULL and then sets the pointer to the struct to NULL.      *
 *  Arguments:                                                                *
 *      vec (tmpl_FloatVector **):                                            *
 *          A pointer to a pointer to a tmpl_FloatVector struct. Given a      *
 *          tmpl_FloatVector pointer vec, pass it to this function with &vec. *
 *  Output:                                                                   *
 *    None (void):                                                            *
 *  Called Functions:                                                         *
 *      free      (stdlib.h)                                                  *
 *  Source Code:                                                              *
 *      libtmpl/src/vector/tmpl_destroy_real_vector.c                         *
 *      libtmpl/src/vector/tmpl_destroy_char_vector.c                         *
 *      libtmpl/src/vector/tmpl_destroy_short_vector.c                        *
 *      libtmpl/src/vector/tmpl_destroy_int_vector.c                          *
 *      libtmpl/src/vector/tmpl_destroy_long_vector.c                         *
 ******************************************************************************/
TMPL_EXPORT externoid tmpl_Destroy_CharVector(tmpl_CharVector **v);
TMPL_EXPORT externoid tmpl_Destroy_UCharVector(tmpl_UCharVector **v);
TMPL_EXPORT externoid tmpl_Destroy_IntVector(tmpl_IntVector **v);
TMPL_EXPORT externoid tmpl_Destroy_UIntVector(tmpl_UIntVector **v);
TMPL_EXPORT externoid tmpl_Destroy_LongVector(tmpl_LongVector **v);
TMPL_EXPORT externoid tmpl_Destroy_ULongVector(tmpl_ULongVector **v);
TMPL_EXPORT externoid tmpl_Destroy_ShortVector(tmpl_ShortVector **v);
TMPL_EXPORT externoid tmpl_Destroy_UShortVector(tmpl_UShortVector **v);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_FloatVector_Add                                                  *
 *  Purpose:                                                                  *
 *      Adds to FloatVectors and stores the result in sum.                    *
 *  Arguments:                                                                *
 *      v (tmpl_FloatVector *):                                               *
 *          A pointer to a tmpl_FloatVector struct.                           *
 *      u (tmpl_FloatVector *):                                               *
 *          A pointer to a tmpl_FloatVector struct.                           *
 *      sum (tmpl_FloatVector *):                                             *
 *          A pointer to a tmpl_FloatVector struct with entries set to        *
 *          sum[k] = v[k] + u[k].                                             *
 *  Output:                                                                   *
 *    None (void):                                                            *
 *  Called Functions:                                                         *
 *      tmpl_strdup   (tmpl_string.h)                                         *
 ******************************************************************************/
TMPL_EXPORT externoid
tmpl_ULongVector_Add(tmpl_ULongVector *v,
                     tmpl_ULongVector *u, tmpl_ULongVector *sum);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_UIntVector_GCD                                                   *
 *  Purpose:                                                                  *
 *      Computes the multi-variable GCD of a vector of integers.              *
 *  Arguments:                                                                *
 *      arr (tmpl_UIntVector *):                                              *
 *          An array of unsigned integer.                                     *
 *  Output:                                                                   *
 *      GCD (unsigned int):                                                   *
 *          The greatest common denominator of the array.                     *
 ******************************************************************************/
TMPL_EXPORT externnsigned int tmpl_UIntVector_GCD(tmpl_UIntVector *arr);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Sieve_of_Eratosthenes                                            *
 *  Purpose:                                                                  *
 *      Computes the first N prime numbers using the Sieve of Eratosthenes.   *
 *  Arguments:                                                                *
 *      N (size_t):                                                           *
 *          The number of primes to compute.                                  *
 *  Output:                                                                   *
 *      arr (tmpl_ULongVector *):                                             *
 *          The first N primes in order.                                      *
 ******************************************************************************/
TMPL_EXPORT externmpl_ULongVector *tmpl_ULong_Sieve_of_Eratosthenes(unsigned long int N);

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
/*  End of include guard.                                                     */
