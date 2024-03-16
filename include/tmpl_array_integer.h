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
 *                             tmpl_array_integer                             *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provides routines for working with integer-valued arrays.             *
 ******************************************************************************
 *                                DEPENDENCIES                                *
 ******************************************************************************
 *  1.) tmpl_inttype.h:                                                       *
 *          Header file with the TMPL_HAS_LONGLONG macro.                     *
 *  2.) stddef.h:                                                             *
 *          Standard header file where size_t is declared.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March 6, 2024                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_ARRAY_INTEGER_H
#define TMPL_ARRAY_INTEGER_H

/*  If using with C++ (and not C), wrap the entire header file in an extern   *
 *  "C" statement. Check if C++ is being used with __cplusplus.               */
#ifdef __cplusplus
extern "C" {
#endif

/*  TMPL_HAS_LONGLONG macro provided here indicating long long support.       */
#include <libtmpl/include/tmpl_inttype.h>

/*  size_t typedef provided here.                                             */
#include <stddef.h>

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Int_Array_Double_Average                                         *
 *  Purpose:                                                                  *
 *      Computes the average of an array of ints outputting a double.         *
 *  Arguments:                                                                *
 *      arr (const signed int * const):                                       *
 *          An array of ints.                                                 *
 *      len (size_t):                                                         *
 *          The number of elements in the array.                              *
 *  Output:                                                                   *
 *      avg (double):                                                         *
 *          The average of arr.                                               *
 *  Notes:                                                                    *
 *      char, short, and long versions are provided as well. Long long is     *
 *      provided if support is available and requested by the Makefile.       *
 ******************************************************************************/
extern double
tmpl_Char_Array_Double_Average(const signed char * const arr, size_t len);

extern double
tmpl_UChar_Array_Double_Average(const unsigned char * const arr, size_t len);

extern double
tmpl_Short_Array_Double_Average(const signed short int * const arr, size_t len);

extern double
tmpl_UShort_Array_Double_Average(const unsigned short * const arr, size_t len);

extern double
tmpl_Int_Array_Double_Average(const signed int * const arr, size_t len);

extern double
tmpl_UInt_Array_Double_Average(const unsigned int * const arr, size_t len);

extern double
tmpl_Long_Array_Double_Average(const signed long int * const arr, size_t len);

extern double
tmpl_ULong_Array_Double_Average(const unsigned long int * const arr,
                                size_t len);

/*  Long long functions if support is available.                              */
#if TMPL_HAS_LONGLONG == 1

extern double
tmpl_LLong_Array_Double_Average(const signed long long int * const arr,
                                size_t len);

extern double
tmpl_ULLong_Array_Double_Average(const unsigned long long int * const arr,
                                 size_t len);

#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Int_Array_Double_Total                                           *
 *  Purpose:                                                                  *
 *      Computes the sum of an array of ints outputting a double.             *
 *  Arguments:                                                                *
 *      arr (const signed int * const):                                       *
 *          An array of ints.                                                 *
 *      len (size_t):                                                         *
 *          The number of elements in the array.                              *
 *  Output:                                                                   *
 *      sum (double):                                                         *
 *          The sum of arr.                                                   *
 *  Notes:                                                                    *
 *      char, short, and long versions are provided as well. Long long is     *
 *      provided if support is available and requested by the Makefile.       *
 ******************************************************************************/
extern double
tmpl_Char_Array_Double_Total(const signed char * const arr, size_t len);

extern double
tmpl_UChar_Array_Double_Total(const unsigned char * const arr, size_t len);

extern double
tmpl_Short_Array_Double_Total(const signed short int * const arr, size_t len);

extern double
tmpl_UShort_Array_Double_Total(const unsigned short * const arr, size_t len);

extern double
tmpl_Int_Array_Double_Total(const signed int * const arr, size_t len);

extern double
tmpl_UInt_Array_Double_Total(const unsigned int * const arr, size_t len);

extern double
tmpl_Long_Array_Double_Total(const signed long int * const arr, size_t len);

extern double
tmpl_ULong_Array_Double_Total(const unsigned long int * const arr, size_t len);

/*  Long long functions if support is available.                              */
#if TMPL_HAS_LONGLONG == 1

extern double
tmpl_LLong_Array_Double_Total(const signed long long int * const arr,
                              size_t len);

extern double
tmpl_ULLong_Array_Double_Total(const unsigned long long int * const arr,
                               size_t len);

#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Int_Array_Float_Total                                            *
 *  Purpose:                                                                  *
 *      Computes the sum of an array of ints outputting a float.              *
 *  Arguments:                                                                *
 *      arr (const signed int * const):                                       *
 *          An array of ints.                                                 *
 *      len (size_t):                                                         *
 *          The number of elements in the array.                              *
 *  Output:                                                                   *
 *      sum (float):                                                          *
 *          The sum of arr.                                                   *
 *  Notes:                                                                    *
 *      char, short, and long versions are provided as well. Long long is     *
 *      provided if support is available and requested by the Makefile.       *
 ******************************************************************************/
extern float
tmpl_Char_Array_Float_Total(const signed char * const arr, size_t len);

extern float
tmpl_UChar_Array_Float_Total(const unsigned char * const arr, size_t len);

extern float
tmpl_Short_Array_Float_Total(const signed short int * const arr, size_t len);

extern float
tmpl_UShort_Array_Float_Total(const unsigned short * const arr, size_t len);

extern float
tmpl_Int_Array_Float_Total(const signed int * const arr, size_t len);

extern float
tmpl_UInt_Array_Float_Total(const unsigned int * const arr, size_t len);

extern float
tmpl_Long_Array_Float_Total(const signed long int * const arr, size_t len);

extern float
tmpl_ULong_Array_Float_Total(const unsigned long int * const arr, size_t len);

/*  Long long functions if support is available.                              */
#if TMPL_HAS_LONGLONG == 1

extern float
tmpl_LLong_Array_Float_Total(const signed long long int * const arr,
                             size_t len);

extern float
tmpl_ULLong_Array_Float_Total(const unsigned long long int * const arr,
                              size_t len);

#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Int_Array_LDouble_Total                                          *
 *  Purpose:                                                                  *
 *      Computes the sum of an array of ints outputting a long double.        *
 *  Arguments:                                                                *
 *      arr (const signed int * const):                                       *
 *          An array of ints.                                                 *
 *      len (size_t):                                                         *
 *          The number of elements in the array.                              *
 *  Output:                                                                   *
 *      sum (long double):                                                    *
 *          The sum of arr.                                                   *
 *  Notes:                                                                    *
 *      char, short, and long versions are provided as well. Long long is     *
 *      provided if support is available and requested by the Makefile.       *
 ******************************************************************************/
extern long double
tmpl_Char_Array_LDouble_Total(const signed char * const arr, size_t len);

extern long double
tmpl_UChar_Array_LDouble_Total(const unsigned char * const arr, size_t len);

extern long double
tmpl_Short_Array_LDouble_Total(const signed short int * const arr, size_t len);

extern long double
tmpl_UShort_Array_LDouble_Total(const unsigned short * const arr, size_t len);

extern long double
tmpl_Int_Array_LDouble_Total(const signed int * const arr, size_t len);

extern long double
tmpl_UInt_Array_LDouble_Total(const unsigned int * const arr, size_t len);

extern long double
tmpl_Long_Array_LDouble_Total(const signed long int * const arr, size_t len);

extern long double
tmpl_ULong_Array_LDouble_Total(const unsigned long int * const arr, size_t len);

/*  Long long functions if support is available.                              */
#if TMPL_HAS_LONGLONG == 1

extern long double
tmpl_LLong_Array_LDouble_Total(const signed long long int * const arr,
                               size_t len);

extern long double
tmpl_ULLong_Array_LDouble_Total(const unsigned long long int * const arr,
                                size_t len);

#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Int_Array_Max                                                    *
 *  Purpose:                                                                  *
 *      Compute the maximum of an array of ints.                              *
 *  Arguments:                                                                *
 *      arr (const signed int * const):                                       *
 *          An array of ints.                                                 *
 *      len (size_t):                                                         *
 *          The number of elements in the array.                              *
 *  Output:                                                                   *
 *      max (signed int):                                                     *
 *          The maximum of arr.                                               *
 *  Notes:                                                                    *
 *      char, short, and long versions are provided as well. Long long is     *
 *      provided if support is available and requested by the Makefile.       *
 ******************************************************************************/
extern signed char
tmpl_Char_Array_Max(const signed char * const arr, size_t len);

extern unsigned char
tmpl_UChar_Array_Max(const unsigned char * const arr, size_t len);

extern signed short int
tmpl_Short_Array_Max(const signed short int * const arr, size_t len);

extern unsigned short int
tmpl_UShort_Array_Max(const unsigned short * const arr, size_t len);

extern signed int
tmpl_Int_Array_Max(const signed int * const arr, size_t len);

extern unsigned int
tmpl_UInt_Array_Max(const unsigned int * const arr, size_t len);

extern signed long int
tmpl_Long_Array_Max(const signed long int * const arr, size_t len);

extern unsigned long int
tmpl_ULong_Array_Max(const unsigned long int * const arr, size_t len);

/*  Long long functions if support is available.                              */
#if TMPL_HAS_LONGLONG == 1

extern signed long long int
tmpl_LLong_Array_Max(const signed long long int * const arr, size_t len);

extern unsigned long long int
tmpl_ULLong_Array_Max(const unsigned long long int * const arr, size_t len);

#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Int_Array_Max_Index                                              *
 *  Purpose:                                                                  *
 *      Compute the index of the maximum of an array of ints.                 *
 *  Arguments:                                                                *
 *      arr (const signed int * const):                                       *
 *          An array of ints.                                                 *
 *      len (size_t):                                                         *
 *          The number of elements in the array.                              *
 *  Output:                                                                   *
 *      ind (size_t):                                                         *
 *          The index of the maximum element of arr.                          *
 *  Notes:                                                                    *
 *      char, short, and long versions are provided as well. Long long is     *
 *      provided if support is available and requested by the Makefile.       *
 ******************************************************************************/
extern size_t
tmpl_Char_Array_Max_Index(const signed char * const arr, size_t len);

extern size_t
tmpl_UChar_Array_Max_Index(const unsigned char * const arr, size_t len);

extern size_t
tmpl_Short_Array_Max_Index(const signed short int * const arr, size_t len);

extern size_t
tmpl_UShort_Array_Max_Index(const unsigned short * const arr, size_t len);

extern size_t
tmpl_Int_Array_Max_Index(const signed int * const arr, size_t len);

extern size_t
tmpl_UInt_Array_Max_Index(const unsigned int * const arr, size_t len);

extern size_t
tmpl_Long_Array_Max_Index(const signed long int * const arr, size_t len);

extern size_t
tmpl_ULong_Array_Max_Index(const unsigned long int * const arr, size_t len);

/*  Long long functions if support is available.                              */
#if TMPL_HAS_LONGLONG == 1

extern size_t
tmpl_LLong_Array_Max_Index(const signed long long int * const arr, size_t len);

extern size_t
tmpl_ULLong_Array_Max_Index(const unsigned long long int * const arr,
                            size_t len);

#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Int_Array_Min                                                    *
 *  Purpose:                                                                  *
 *      Compute the minimum of an array of ints.                              *
 *  Arguments:                                                                *
 *      arr (const signed int * const):                                       *
 *          An array of ints.                                                 *
 *      len (size_t):                                                         *
 *          The number of elements in the array.                              *
 *  Output:                                                                   *
 *      min (signed int):                                                     *
 *          The minimum of arr.                                               *
 *  Notes:                                                                    *
 *      char, short, and long versions are provided as well. Long long is     *
 *      provided if support is available and requested by the Makefile.       *
 ******************************************************************************/
extern signed char
tmpl_Char_Array_Min(const signed char * const arr, size_t len);

extern unsigned char
tmpl_UChar_Array_Min(const unsigned char * const arr, size_t len);

extern signed short int
tmpl_Short_Array_Min(const signed short int * const arr, size_t len);

extern unsigned short int
tmpl_UShort_Array_Min(const unsigned short * const arr, size_t len);

extern signed int
tmpl_Int_Array_Min(const signed int * const arr, size_t len);

extern unsigned int
tmpl_UInt_Array_Min(const unsigned int * const arr, size_t len);

extern signed long int
tmpl_Long_Array_Min(const signed long int * const arr, size_t len);

extern unsigned long int
tmpl_ULong_Array_Min(const unsigned long int * const arr, size_t len);

/*  Long long functions if support is available.                              */
#if TMPL_HAS_LONGLONG == 1

extern signed long long int
tmpl_LLong_Array_Min(const signed long long int * const arr, size_t len);

extern unsigned long long int
tmpl_ULLong_Array_Min(const unsigned long long int * const arr, size_t len);

#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Int_Array_Min_Index                                              *
 *  Purpose:                                                                  *
 *      Compute the index of the minimum of an array of ints.                 *
 *  Arguments:                                                                *
 *      arr (const signed int * const):                                       *
 *          An array of ints.                                                 *
 *      len (size_t):                                                         *
 *          The number of elements in the array.                              *
 *  Output:                                                                   *
 *      ind (size_t):                                                         *
 *          The index of the minimum element of arr.                          *
 *  Notes:                                                                    *
 *      char, short, and long versions are provided as well. Long long is     *
 *      provided if support is available and requested by the Makefile.       *
 ******************************************************************************/
extern size_t
tmpl_Char_Array_Min_Index(const signed char * const arr, size_t len);

extern size_t
tmpl_UChar_Array_Min_Index(const unsigned char * const arr, size_t len);

extern size_t
tmpl_Short_Array_Min_Index(const signed short int * const arr, size_t len);

extern size_t
tmpl_UShort_Array_Min_Index(const unsigned short * const arr, size_t len);

extern size_t
tmpl_Int_Array_Min_Index(const signed int * const arr, size_t len);

extern size_t
tmpl_UInt_Array_Min_Index(const unsigned int * const arr, size_t len);

extern size_t
tmpl_Long_Array_Min_Index(const signed long int * const arr, size_t len);

extern size_t
tmpl_ULong_Array_Min_Index(const unsigned long int * const arr, size_t len);

/*  Long long functions if support is available.                              */
#if TMPL_HAS_LONGLONG == 1

extern size_t
tmpl_LLong_Array_Min_Index(const signed long long int * const arr, size_t len);

extern size_t
tmpl_ULLong_Array_Min_Index(const unsigned long long int * const arr,
                            size_t len);

#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Int_Array_MinMax                                                 *
 *  Purpose:                                                                  *
 *      Compute the min and max of an array of ints.                          *
 *  Arguments:                                                                *
 *      arr (const signed int * const):                                       *
 *          An array of ints.                                                 *
 *      len (size_t):                                                         *
 *          The number of elements in the array.                              *
 *      min (signed int *):                                                   *
 *          A pointer to an int, the min is stored here.                      *
 *      max (signed int *):                                                   *
 *          A pointer to an int, the max is stored here.                      *
 *  Output:                                                                   *
 *      None (void).                                                          *
 ******************************************************************************/
extern void
tmpl_Char_Array_MinMax(const signed char * const arr,
                       size_t len,
                       signed char *min,
                       signed char *max);

extern void
tmpl_UChar_Array_MinMax(const unsigned char * const arr,
                        size_t len,
                        unsigned char *min,
                        unsigned char *max);

extern void
tmpl_Short_Array_MinMax(const signed short int * const arr,
                        size_t len,
                        signed short int *min,
                        signed short int *max);

extern void
tmpl_UShort_Array_MinMax(const unsigned short int * const arr,
                         size_t len,
                         unsigned short int * min,
                         unsigned short int *max);

extern void
tmpl_Int_Array_MinMax(const signed int * const arr,
                      size_t len,
                      signed int *min,
                      signed int *max);

extern void
tmpl_UInt_Array_MinMax(const unsigned int * const arr,
                       size_t len,
                       unsigned int *min,
                       unsigned int *max);

extern void
tmpl_Long_Array_MinMax(const signed long int * const arr,
                       size_t len,
                       signed long int *min,
                       signed long int *max);

extern void
tmpl_ULong_Array_MinMax(const unsigned long int * const arr,
                        size_t len,
                        unsigned long int *min,
                        unsigned long int *max);

/*  Long long functions if support is available.                              */
#if TMPL_HAS_LONGLONG == 1

extern void
tmpl_LLong_Array_MinMax(const signed long long int * const arr,
                        size_t len,
                        signed long long int *min,
                        signed long long int *max);

extern void
tmpl_ULLong_Array_MinMax(const unsigned long long int * const arr,
                         size_t len,
                         unsigned long long int *min,
                         unsigned long long int *max);

#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Int_Array_MinMax                                                 *
 *  Purpose:                                                                  *
 *      Compute the min and max of an array of ints.                          *
 *  Arguments:                                                                *
 *      arr (const signed int * const):                                       *
 *          An array of ints.                                                 *
 *      len (size_t):                                                         *
 *          The number of elements in the array.                              *
 *      min (signed int *):                                                   *
 *          A pointer to an int, the min is stored here.                      *
 *      max (signed int *):                                                   *
 *          A pointer to an int, the max is stored here.                      *
 *  Output:                                                                   *
 *      None (void).                                                          *
 ******************************************************************************/
extern void
tmpl_Char_Array_MinMax_Index(const signed char * const arr,
                             size_t len,
                             size_t *minind,
                             size_t *maxind);

extern void
tmpl_UChar_Array_MinMax_Index(const unsigned char * const arr,
                              size_t len,
                              size_t *minind,
                              size_t *maxind);

extern void
tmpl_Short_Array_MinMax_Index(const signed short int * const arr,
                              size_t len,
                              size_t *minind,
                              size_t *maxind);

extern void
tmpl_UShort_Array_MinMax_Index(const unsigned short int * const arr,
                               size_t len,
                               size_t *minind,
                               size_t *maxind);

extern void
tmpl_Int_Array_MinMax_Index(const signed int * const arr,
                            size_t len,
                            size_t *minind,
                            size_t *maxind);

extern void
tmpl_UInt_Array_MinMax_Index(const unsigned int * const arr,
                             size_t len,
                             size_t *minind,
                             size_t *maxind);

extern void
tmpl_Long_Array_MinMax_Index(const signed long int * const arr,
                             size_t len,
                             size_t *minind,
                             size_t *maxind);

extern void
tmpl_ULong_Array_MinMax_Index(const unsigned long int * const arr,
                              size_t len,
                              size_t *minind,
                              size_t *maxind);

/*  Long long functions if support is available.                              */
#if TMPL_HAS_LONGLONG == 1

extern void
tmpl_LLong_Array_MinMax_Index(const signed long long int * const arr,
                              size_t len,
                              size_t *minind,
                              size_t *maxind);

extern void
tmpl_ULLong_Array_MinMax_Index(const unsigned long long int * const arr,
                               size_t len,
                               size_t *minind,
                               size_t *maxind);

#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Int_Array_Total                                                  *
 *  Purpose:                                                                  *
 *      Computes the sum of an array of ints.                                 *
 *  Arguments:                                                                *
 *      arr (const signed int * const):                                       *
 *          An array of ints.                                                 *
 *      len (size_t):                                                         *
 *          The number of elements in the array.                              *
 *  Output:                                                                   *
 *      sum (signed int):                                                     *
 *          The sum of arr.                                                   *
 *  Notes:                                                                    *
 *      char, short, and long versions are provided as well. Long long is     *
 *      provided if support is available and requested by the Makefile.       *
 ******************************************************************************/
extern signed char
tmpl_Char_Array_Total(const signed char * const arr, size_t len);

extern unsigned char
tmpl_UChar_Array_Total(const unsigned char * const arr, size_t len);

extern signed short
tmpl_Short_Array_Total(const signed short int * const arr, size_t len);

extern unsigned short int
tmpl_UShort_Array_Total(const unsigned short * const arr, size_t len);

extern signed int
tmpl_Int_Array_Total(const signed int * const arr, size_t len);

extern unsigned int
tmpl_UInt_Array_Total(const unsigned int * const arr, size_t len);

extern signed long int
tmpl_Long_Array_Total(const signed long int * const arr, size_t len);

extern unsigned long int
tmpl_ULong_Array_Total(const unsigned long int * const arr, size_t len);

/*  Long long functions if support is available.                              */
#if TMPL_HAS_LONGLONG == 1

extern signed long long int
tmpl_LLong_Array_Total(const signed long long int * const arr, size_t len);

extern unsigned long long int
tmpl_ULLong_Array_Total(const unsigned long long int * const arr, size_t len);

#endif
/*  End of #if TMPL_HAS_LONGLONG == 1.                                        */

/*  TODO:
 *      Average
 *      GCD
 *      RMS
 *      Swap elements
 *      Pop (delete element)
 *      Resize
 *      Append
 *      Prepend
 *      Insert
 *      As Double
 *      Reverse
 */

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
/*  End of include guard.                                                     */
