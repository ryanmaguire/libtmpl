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
 *                              tmpl_vector                                   *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide tools for working with vectors with integer, rational, real,  *
 *      or complex entries.                                                   *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file which typedef's Boolean types for C89/C90 compilers.  *
 *  2.) tmpl_complex.h:                                                       *
 *          Header file with complex data types.                              *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       May 13, 2021                                                  *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2022/02/01: Ryan Maguire                                                  *
 *      Getting rid of -Wreserved-identifier warnings with clang.             *
 *  2022/12/22: Ryan Maguire                                                  *
 *      Splitting vector code into integer, real, and complex versions.       *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VECTOR_REAL_H
#define TMPL_VECTOR_REAL_H

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
 *                          Real Valued Vectors                               *
 ******************************************************************************/

/*  Single-precision vector with real entries.                                */
typedef struct tmpl_FloatVector_Def {
    float *data;
    unsigned long int length;

    /*  In the event of an error, this Boolean is set to true and a string    *
     *  detailing the error is stored in the error_message pointer.           */
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_FloatVector;

/*  Double-precision vector with real entries.                                */
typedef struct tmpl_DoubleVector_Def {
    double *data;
    unsigned long int length;

    /*  In the event of an error, this Boolean is set to true and a string    *
     *  detailing the error is stored in the error_message pointer.           */
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_DoubleVector;

/*  Long double-precision vector with real entries.                           */
typedef struct tmpl_LongDoubleVector_Def {
    long double *data;
    unsigned long int length;

    /*  In the event of an error, this Boolean is set to true and a string    *
     *  detailing the error is stored in the error_message pointer.           */
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_LongDoubleVector;

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Create_Empty_FloatVector                                         *
 *  Purpose:                                                                  *
 *      Creates a tmpl_FloatVector and allocates memory for the data.         *
 *      Integer, double, and long double equivalents are provided.            *
 *  Arguments:                                                                *
 *      length (unsigned long int):                                           *
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
 ******************************************************************************/
TMPL_EXPORT externmpl_FloatVector *
tmpl_Create_Empty_FloatVector(unsigned long int length);

TMPL_EXPORT externmpl_DoubleVector *
tmpl_Create_Empty_DoubleVector(unsigned long int length);

TMPL_EXPORT externmpl_LongDoubleVector *
tmpl_Create_Empty_LongDoubleVector(unsigned long int length);

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
TMPL_EXPORT externmpl_FloatVector *
tmpl_Create_FloatVector_From_Data(float *arr, unsigned long int length);

TMPL_EXPORT externmpl_DoubleVector *
tmpl_Create_DoubleVector_From_Data(double *arr, unsigned long int length);

TMPL_EXPORT externmpl_LongDoubleVector *
tmpl_Create_LongDoubleVector_From_Data(long double *arr,
                                       unsigned long int length);

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
TMPL_EXPORT externmpl_FloatVector *
tmpl_Create_Zero_FloatVector(unsigned long int length);

TMPL_EXPORT externmpl_DoubleVector *
tmpl_Create_Zero_DoubleVector(unsigned long int length);

TMPL_EXPORT externmpl_LongDoubleVector *
tmpl_Create_Zero_LongDoubleVector(unsigned long int length);

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
TMPL_EXPORT externoid
tmpl_Destroy_FloatVector(tmpl_FloatVector **v);

TMPL_EXPORT externoid
tmpl_Destroy_DoubleVector(tmpl_DoubleVector **v);

TMPL_EXPORT externoid
tmpl_Destroy_LongDoubleVector(tmpl_LongDoubleVector **v);

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
tmpl_FloatVector_Add(tmpl_FloatVector *v,
                     tmpl_FloatVector *u, tmpl_FloatVector *sum);

TMPL_EXPORT externoid
tmpl_DoubleVector_Add(tmpl_DoubleVector *v,
                      tmpl_DoubleVector *u, tmpl_DoubleVector *sum);

TMPL_EXPORT externoid
tmpl_LDoubleVector_Add(tmpl_LongDoubleVector *v,
                       tmpl_LongDoubleVector *u, tmpl_LongDoubleVector *sum);

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
