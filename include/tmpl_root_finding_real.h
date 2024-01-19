
#ifndef TMPL_ROOT_FINDING_REAL_H
#define TMPL_ROOT_FINDING_REAL_H

extern float
tmpl_Newton_Raphson_Float(float x, float (*f)(float), float (*f_prime)(float),
                          unsigned int max_iters, float eps);

extern double
tmpl_Newton_Raphson_Double(double x, double (*f)(double),
                           double (*f_prime)(double),
                           unsigned int max_iters, double eps);

extern long double
tmpl_Newton_Raphson_LDouble(long double x, long double (*f)(long double),
                            long double (*f_prime)(long double),
                            unsigned int max_iters, long double eps);

extern float
tmpl_Halleys_Method_Float(float x, float (*f)(float),
                          float (*f_prime)(float),
                          float (*f_2prime)(float),
                          unsigned int max_iters, float eps);

extern double
tmpl_Halleys_Method_Double(double x, double (*f)(double),
                           double (*f_prime)(double),
                           double (*f_2prime)(double),
                           unsigned int max_iters, double eps);

extern long double
tmpl_Halleys_Method_LDouble(long double x, long double (*f)(long double),
                            long double (*f_prime)(long double),
                            long double (*f_2prime)(long double),
                            unsigned int max_iters, long double eps);

#endif
