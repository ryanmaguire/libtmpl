/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_VECTOR_COMPLEX_H
#define TMPL_VECTOR_COMPLEX_H

/*  If using with C++ (and not C), wrap the entire header file in an extern   *
 *  "C" statement. Check if C++ is being used with __cplusplus.               */
#ifdef __cplusplus
extern "C" {
#endif

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  Complex numbers here.                                                     */
#include <libtmpl/include/tmpl_complex.h>

/******************************************************************************
 *                        Complex Valued Vectors                              *
 ******************************************************************************/

/*  Single precision vector with complex entries.                             */
typedef struct tmpl_ComplexFloatVector_Def {
    tmpl_ComplexFloat *data;
    unsigned long int length;

    /*  In the event of an error, this Boolean is set to true and a string    *
     *  detailing the error is stored in the error_message pointer.           */
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_ComplexFloatVector;

/*  Double precision vector with complex entries.                             */
typedef struct tmpl_ComplexDoubleVector_Def {
    tmpl_ComplexDouble *data;
    unsigned long int length;

    /*  In the event of an error, this Boolean is set to true and a string    *
     *  detailing the error is stored in the error_message pointer.           */
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_ComplexDoubleVector;

/*  Extended precision vector with complex entries.                           */
typedef struct tmpl_ComplexLongDoubleVector_Def {
    tmpl_ComplexLongDouble *data;
    unsigned long int length;

    /*  In the event of an error, this Boolean is set to true and a string    *
     *  detailing the error is stored in the error_message pointer.           */
    tmpl_Bool error_occurred;
    char *error_message;
} tmpl_ComplexLongDoubleVector;

/*  End of extern "C" statement allowing C++ compatibility.                   */
#ifdef __cplusplus
}
#endif

#endif
/*  End of include guard.                                                     */
