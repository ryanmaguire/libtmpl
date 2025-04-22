/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_WHERE_H
#define TMPL_WHERE_H

extern unsigned long **
tmpl_Where_Lesser_Char(char *data, unsigned long dim, double threshold);

extern unsigned long **
tmpl_Where_Lesser_UChar(unsigned char *data, unsigned long dim,
                        double threshold);

extern unsigned long **
tmpl_Where_Lesser_Short(short *data, unsigned long dim, double threshold);

extern unsigned long **
tmpl_Where_Lesser_UShort(unsigned short *data, unsigned long dim,
                         double threshold);

extern unsigned long **
tmpl_Where_Lesser_Int(int *data, unsigned long dim, double threshold);

extern unsigned long **
tmpl_Where_Lesser_UInt(unsigned int *data, unsigned long dim,
                       double threshold);

extern unsigned long **
tmpl_Where_Lesser_Long(long *data, unsigned long dim, double threshold);

extern unsigned long **
tmpl_Where_Lesser_ULong(unsigned long *data, unsigned long dim,
                        double threshold);

extern unsigned long **
tmpl_Where_Lesser_Float(float *data, unsigned long dim, float threshold);

extern unsigned long **
tmpl_Where_Lesser_Double(double *data, unsigned long dim,
                                      double threshold);

extern unsigned long **
tmpl_Where_Lesser_LDouble(long double *data, unsigned long dim,
                          long double threshold);

extern unsigned long **
tmpl_Where_Greater_Char(char *data, unsigned long dim, double threshold);

extern unsigned long **
tmpl_Where_Greater_UChar(unsigned char *data, unsigned long dim,
                        double threshold);

extern unsigned long **
tmpl_Where_Greater_Short(short *data, unsigned long dim, double threshold);

extern unsigned long **
tmpl_Where_Greater_UShort(unsigned short *data, unsigned long dim,
                         double threshold);

extern unsigned long **
tmpl_Where_Greater_Int(int *data, unsigned long dim, double threshold);

extern unsigned long **
tmpl_Where_Greater_UInt(unsigned int *data, unsigned long dim,
                       double threshold);

extern unsigned long **
tmpl_Where_Greater_Long(long *data, unsigned long dim, double threshold);

extern unsigned long **
tmpl_Where_Greater_ULong(unsigned long *data, unsigned long dim,
                        double threshold);

extern unsigned long **
tmpl_Where_Greater_Float(float *data, unsigned long dim, float threshold);

extern unsigned long **
tmpl_Where_Greater_Double(double *data, unsigned long dim,
                                      double threshold);

extern unsigned long **
tmpl_Where_Greater_LDouble(long double *data, unsigned long dim,
                          long double threshold);

extern unsigned long **
tmpl_Where_LesserGreater_Char(char *data, unsigned long dim,
                              double lower, double upper);

extern unsigned long **
tmpl_Where_LesserGreater_UChar(unsigned char *data, unsigned long dim,
                               double lower, double upper);

extern unsigned long **
tmpl_Where_LesserGreater_Short(short *data, unsigned long dim,
                               double lower, double upper);

extern unsigned long **
tmpl_Where_LesserGreater_UShort(unsigned short *data, unsigned long dim,
                                double lower, double upper);

extern unsigned long **
tmpl_Where_LesserGreater_Int(int *data, unsigned long dim,
                             double lower, double upper);

extern unsigned long **
tmpl_Where_LesserGreater_UInt(unsigned int *data, unsigned long dim,
                              double lower, double upper);

extern unsigned long **
tmpl_Where_LesserGreater_Long(long *data, unsigned long dim,
                              double lower, double upper);

extern unsigned long **
tmpl_Where_LesserGreater_ULong(unsigned long *data, unsigned long dim,
                               double lower, double upper);

extern unsigned long **
tmpl_Where_LesserGreater_Float(float *data, unsigned long dim,
                               float lower, float upper);

extern unsigned long **
tmpl_Where_LesserGreater_Double(double *data, unsigned long dim,
                                double lower, double upper);

extern unsigned long **
tmpl_Where_LesserGreater_LDouble(long double *data, unsigned long dim,
                                 long double lower, long double upper);

#endif
/*  End of include guard.                                                     */
