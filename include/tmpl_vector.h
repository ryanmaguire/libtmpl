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
 *      Provide tools for working with vectors with real entries.             *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_bool.h:                                                          *
 *          Header file which typedef's Boolean types for C89/C90 compilers.  *
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
 *  Date:       May 13, 2021                                                  *
 ******************************************************************************/

#ifndef TMPL_VECTOR_H
#define TMPL_VECTOR_H

#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_complex.h>

typedef struct tmpl_ComplexDoubleVector {
    tmpl_ComplexDouble *data;
    unsigned long length;
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_ComplexDoubleVector;

/******************************************************************************
 *                          Real Valued Vectors                               *
 ******************************************************************************/

/*  Single-precision vector with real entries.                                */
typedef struct _tmpl_FloatVector {
    float *data;
    unsigned long int length;

    /*  In the event of an error, this Boolean is set to true and a string    *
     *  detailing the error is stored in the error_message pointer.           */
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_FloatVector;

/*  Double-precision vector with real entries.                                */
typedef struct _tmpl_DoubleVector {
    double *data;
    unsigned long int length;

    /*  In the event of an error, this Boolean is set to true and a string    *
     *  detailing the error is stored in the error_message pointer.           */
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_DoubleVector;

/*  Long double-precision vector with real entries.                           */
typedef struct _tmpl_LongDoubleVector {
    long double *data;
    unsigned long int length;

    /*  In the event of an error, this Boolean is set to true and a string    *
     *  detailing the error is stored in the error_message pointer.           */
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_LongDoubleVector;

/******************************************************************************
 *                         Integer Valued Vectors                             *
 ******************************************************************************/

typedef struct _tmpl_CharVector {
    char *data;
    unsigned long int length;
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_CharVector;

typedef struct _tmpl_UCharVector {
    unsigned char *data;
    unsigned long int length;
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_UCharVector;

typedef struct _tmpl_ShortVector {
    short int *data;
    unsigned long int length;
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_ShortVector;

typedef struct _tmpl_UShortVector {
    unsigned short int *data;
    unsigned long int length;
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_UShortVector;

typedef struct _tmpl_IntVector {
    int *data;
    unsigned long int length;
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_IntVector;

typedef struct _tmpl_UIntVector {
    unsigned int *data;
    unsigned long int length;
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_UIntVector;

typedef struct _tmpl_LongVector {
    long int *data;
    unsigned long int length;
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_LongVector;

typedef struct _tmpl_ULongVector {
    unsigned long int *data;
    unsigned long int length;
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_ULongVector;

/******************************************************************************
 *                            Basic Routines                                  *
 ******************************************************************************/

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
extern tmpl_FloatVector *
tmpl_Create_FloatVector_From_Data(float *arr, unsigned long int length);

extern tmpl_DoubleVector *
tmpl_Create_DoubleVector_From_Data(double *arr, unsigned long int length);

extern tmpl_LongDoubleVector *
tmpl_Create_LongDoubleVector_From_Data(long double *arr,
                                       unsigned long int length);

extern tmpl_CharVector *
tmpl_Create_CharVector_From_Data(char *v, unsigned long length);

extern tmpl_UCharVector *
tmpl_Create_UCharVector_From_Data(unsigned char *v, unsigned long int length);

extern tmpl_ShortVector *
tmpl_Create_ShortVector_From_Data(short int *v, unsigned long length);

extern tmpl_UShortVector *
tmpl_Create_UShortVector_From_Data(unsigned short int *v,
                                   unsigned long int length);

extern tmpl_IntVector *
tmpl_Create_IntVector_From_Data(int *v, unsigned long length);

extern tmpl_UIntVector *
tmpl_Create_UIntVector_From_Data(unsigned int *v, unsigned long int length);

extern tmpl_LongVector *
tmpl_Create_LongVector_From_Data(long int *v, unsigned long int length);

extern tmpl_ULongVector *
tmpl_Create_ULongVector_From_Data(unsigned long int *v,
                                  unsigned long int length);

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
 *      libtmpl/src/vector/tmpl_create_empty_char_vector.c                    *
 *      libtmpl/src/vector/tmpl_create_empty_short_vector.c                   *
 *      libtmpl/src/vector/tmpl_create_empty_int_vector.c                     *
 *      libtmpl/src/vector/tmpl_create_empty_long_vector.c                    *
 ******************************************************************************/
extern tmpl_FloatVector *
tmpl_Create_Empty_FloatVector(unsigned long int length);

extern tmpl_DoubleVector *
tmpl_Create_Empty_DoubleVector(unsigned long int length);

extern tmpl_LongDoubleVector *
tmpl_Create_Empty_LongDoubleVector(unsigned long int length);

extern tmpl_CharVector *
tmpl_Create_Empty_CharVector(unsigned long int length);

extern tmpl_UCharVector *
tmpl_Create_Empty_UCharVector(unsigned long int length);

extern tmpl_ShortVector *
tmpl_Create_Empty_ShortVector(unsigned long int length);

extern tmpl_UShortVector *
tmpl_Create_Empty_UShortVector(unsigned long int length);

extern tmpl_IntVector *
tmpl_Create_Empty_IntVector(unsigned long int length);

extern tmpl_UIntVector *
tmpl_Create_Empty_UIntVector(unsigned long int length);

extern tmpl_LongVector *
tmpl_Create_Empty_LongVector(unsigned long int length);

extern tmpl_ULongVector *
tmpl_Create_Empty_ULongVector(unsigned long int length);

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
extern tmpl_FloatVector *
tmpl_Create_Zero_FloatVector(unsigned long int length);

extern tmpl_DoubleVector *
tmpl_Create_Zero_DoubleVector(unsigned long int length);

extern tmpl_LongDoubleVector *
tmpl_Create_Zero_LongDoubleVector(unsigned long int length);

extern tmpl_CharVector *
tmpl_Create_Zero_CharVector(unsigned long int length);

extern tmpl_UCharVector *
tmpl_Create_Zero_UCharVector(unsigned long int length);

extern tmpl_ShortVector *
tmpl_Create_Zero_ShortVector(unsigned long int length);

extern tmpl_UShortVector *
tmpl_Create_Zero_UShortVector(unsigned long int length);

extern tmpl_IntVector *
tmpl_Create_Zero_IntVector(unsigned long int length);

extern tmpl_UIntVector *
tmpl_Create_Zero_UIntVector(unsigned long int length);

extern tmpl_LongVector *
tmpl_Create_Zero_LongVector(unsigned long int length);

extern tmpl_ULongVector *
tmpl_Create_Zero_ULongVector(unsigned long int length);

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
extern void
tmpl_Destroy_FloatVector(tmpl_FloatVector **v);

extern void
tmpl_Destroy_DoubleVector(tmpl_DoubleVector **v);

extern void
tmpl_Destroy_LongDoubleVector(tmpl_LongDoubleVector **v);

extern void
tmpl_Destroy_CharVector(tmpl_CharVector **v);

extern void
tmpl_Destroy_UCharVector(tmpl_UCharVector **v);

extern void
tmpl_Destroy_IntVector(tmpl_IntVector **v);

extern void
tmpl_Destroy_UIntVector(tmpl_UIntVector **v);

extern void
tmpl_Destroy_LongVector(tmpl_LongVector **v);

extern void
tmpl_Destroy_ULongVector(tmpl_ULongVector **v);

extern void
tmpl_Destroy_ShortVector(tmpl_ShortVector **v);

extern void
tmpl_Destroy_UShortVector(tmpl_UShortVector **v);


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
extern void
tmpl_FloatVector_Add(tmpl_FloatVector *v,
                     tmpl_FloatVector *u, tmpl_FloatVector *sum);

extern void
tmpl_DoubleVector_Add(tmpl_DoubleVector *v,
                      tmpl_DoubleVector *u, tmpl_DoubleVector *sum);

extern void
tmpl_LDoubleVector_Add(tmpl_LongDoubleVector *v,
                       tmpl_LongDoubleVector *u, tmpl_LongDoubleVector *sum);

extern void
tmpl_ULongVector_Add(tmpl_ULongVector *v,
                     tmpl_ULongVector *u, tmpl_ULongVector *sum);

#endif

