/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_WHERE_H
#define TMPL_WHERE_H

#include <stddef.h>

extern size_t **
tmpl_Where_Lesser_Char(char *data, size_t dim, double threshold);

extern size_t **
tmpl_Where_Lesser_UChar(unsigned char *data, size_t dim, double threshold);

extern size_t **
tmpl_Where_Lesser_Short(short *data, size_t dim, double threshold);

extern size_t **
tmpl_Where_Lesser_UShort(unsigned short *data, size_t dim, double threshold);

extern size_t **
tmpl_Where_Lesser_Int(int *data, size_t dim, double threshold);

extern size_t **
tmpl_Where_Lesser_UInt(unsigned int *data, size_t dim, double threshold);

extern size_t **
tmpl_Where_Lesser_Long(long *data, size_t dim, double threshold);

extern size_t **
tmpl_Where_Lesser_ULong(unsigned long *data, size_t dim, double threshold);

extern size_t **
tmpl_Where_Lesser_Float(float *data, size_t dim, float threshold);

extern size_t **
tmpl_Where_Lesser_Double(double *data, size_t dim, double threshold);

extern size_t **
tmpl_Where_Lesser_LDouble(long double *data, size_t dim, long double threshold);

extern size_t **
tmpl_Where_Greater_Char(char *data, size_t dim, double threshold);

extern size_t **
tmpl_Where_Greater_UChar(unsigned char *data, size_t dim, double threshold);

extern size_t **
tmpl_Where_Greater_Short(short *data, size_t dim, double threshold);

extern size_t **
tmpl_Where_Greater_UShort(unsigned short *data, size_t dim, double threshold);

extern size_t **
tmpl_Where_Greater_Int(int *data, size_t dim, double threshold);

extern size_t **
tmpl_Where_Greater_UInt(unsigned int *data, size_t dim, double threshold);

extern size_t **
tmpl_Where_Greater_Long(long *data, size_t dim, double threshold);

extern size_t **
tmpl_Where_Greater_ULong(unsigned long *data, size_t dim, double threshold);

extern size_t **
tmpl_Where_Greater_Float(float *data, size_t dim, float threshold);

extern size_t **
tmpl_Where_Greater_Double(double *data, size_t dim, double threshold);

extern size_t **
tmpl_Where_Greater_LDouble(long double *data, size_t dim,
                           long double threshold);

extern size_t **
tmpl_Where_LesserGreater_Char(char *data, size_t dim,
                              double lower, double upper);

extern size_t **
tmpl_Where_LesserGreater_UChar(unsigned char *data, size_t dim,
                               double lower, double upper);

extern size_t **
tmpl_Where_LesserGreater_Short(short *data, size_t dim,
                               double lower, double upper);

extern size_t **
tmpl_Where_LesserGreater_UShort(unsigned short *data, size_t dim,
                                double lower, double upper);

extern size_t **
tmpl_Where_LesserGreater_Int(int *data, size_t dim,
                             double lower, double upper);

extern size_t **
tmpl_Where_LesserGreater_UInt(unsigned int *data, size_t dim,
                              double lower, double upper);

extern size_t **
tmpl_Where_LesserGreater_Long(long *data, size_t dim,
                              double lower, double upper);

extern size_t **
tmpl_Where_LesserGreater_ULong(unsigned long *data, size_t dim,
                               double lower, double upper);

extern size_t **
tmpl_Where_LesserGreater_Float(float *data, size_t dim,
                               float lower, float upper);

extern size_t **
tmpl_Where_LesserGreater_Double(double *data, size_t dim,
                                double lower, double upper);

extern size_t **
tmpl_Where_LesserGreater_LDouble(long double *data, size_t dim,
                                 long double lower, long double upper);

#endif
/*  End of include guard.                                                     */
