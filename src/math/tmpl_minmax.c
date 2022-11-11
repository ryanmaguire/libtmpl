/*  Prototypes for these functions declared here.                             */
#include <libtmpl/include/tmpl_math.h>

#define MinFuncFromType(type, Type)                                            \
type tmpl_Min_##Type(type *arr, unsigned long n_elements)                      \
{                                                                              \
    type min = arr[0];                                                         \
    unsigned long i;                                                           \
    for (i = 1; i < n_elements; ++i)                                           \
    {                                                                          \
        if (arr[i] < min)                                                      \
            min = arr[i];                                                      \
    }                                                                          \
                                                                               \
    return min;                                                                \
}

MinFuncFromType(char, Char)
MinFuncFromType(unsigned char, UChar)
MinFuncFromType(short, Short)
MinFuncFromType(unsigned short, UShort)
MinFuncFromType(int, Int)
MinFuncFromType(unsigned int, UInt)
MinFuncFromType(long, Long)
MinFuncFromType(unsigned long, ULong)

#define MaxFuncFromType(type, Type)                                            \
type tmpl_Max_##Type(type *arr, unsigned long n_elements)                      \
{                                                                              \
    type max = arr[0];                                                         \
    unsigned long i;                                                           \
    for (i = 1; i < n_elements; ++i)                                           \
    {                                                                          \
        if (max < arr[i])                                                      \
            max = arr[i];                                                      \
    }                                                                          \
                                                                               \
    return max;                                                                \
}

MaxFuncFromType(char, Char)
MaxFuncFromType(unsigned char, UChar)
MaxFuncFromType(short, Short)
MaxFuncFromType(unsigned short, UShort)
MaxFuncFromType(int, Int)
MaxFuncFromType(unsigned int, UInt)
MaxFuncFromType(long, Long)
MaxFuncFromType(unsigned long, ULong)
