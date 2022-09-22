#ifndef TMPL_MATH_ARCTAN_TABLE_H
#define TMPL_MATH_ARCTAN_TABLE_H

/*  Formula 4.4.34 from Abramowitz and Stegun states:                         *
 *                                                                            *
 *                                     u - v                                  *
 *          atan(u) = atan(v) + atan( -------- )                              *
 *                                     1 + uv                                 *
 *                                                                            *
 *  The values v and atan(v) are pre-computed below for the calculation.      */
static const float tmpl_atan_float_v[8] = {
    0.05F,
    0.18F,
    0.35F,
    0.72F,
    1.35F,
    2.5F,
    4.0F,
    8.0F
};

static const float tmpl_atan_float_atan_of_v[8] = {
    0.0499583957219427614100063F,
    0.178092938231197549667920F,
    0.336674819386727181396699F,
    0.624023052976756847589791F,
    0.933247528656203869893663F,
    1.19028994968253173292773F,
    1.32581766366803246505924F,
    1.44644133224813518419997F
};

static const double tmpl_atan_double_v[8] = {
    0.05,
    0.18,
    0.35,
    0.72,
    1.35,
    2.5,
    4.0,
    8.0
};

static const double tmpl_atan_double_atan_of_v[8] = {
    0.0499583957219427614100063,
    0.178092938231197549667920,
    0.336674819386727181396699,
    0.624023052976756847589791,
    0.933247528656203869893663,
    1.19028994968253173292773,
    1.32581766366803246505924,
    1.44644133224813518419997
};

#endif
