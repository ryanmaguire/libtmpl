

#include <libtmpl/include/tmpl_knots.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

tmpl_VirtualKnot *tmpl_Gauss_Code_From_String(char *str)
{
    size_t len, i, ind;
    tmpl_GaussTuple *T;
    tmpl_VirtualKnot *K;
    
    if (str == NULL)
        return NULL;

    len = strlen(str);
    
    K = malloc(sizeof(*K));
    
    if (K == NULL)
        return NULL;
    
    T = malloc(sizeof(*K) * len / 3);
    
    if (T == NULL)
    {
        free(K);
        return NULL;
    }
    
    i = 0;
    ind = 0;
    while (i < len)
    {
        switch(str[i])
        {
            case 'o':
            case 'O':
                T[ind].crossing_type = tmpl_OverCrossing;
                break;
            case 'u':
            case 'U':
                T[ind].crossing_type = tmpl_UnderCrossing;
                break;
            default:
                free(T);
                free(K);
                return NULL;
        }
        ++i;

        if isdigit(str[i])
        {
	        size_t k = i;
            while (isdigit(str[k]))
            {
                ++k;
            }

	        T[ind].crossing_number = (tmpl_uint64)atoi(str + i);
	        i = k;
        }
        else
        {
            free(T);
            free(K);
            return NULL;
        }

        switch(str[i])
        {
            case '+':
                T[ind].crossing_sign = tmpl_PositiveCrossing;
                break;
            case '-':
                T[ind].crossing_sign = tmpl_NegativeCrossing;
                break;
            default:
                free(T);
                free(K);
                return NULL;
        }
        ++i;

        ind ++;
    }

    K->number_of_crossings = (tmpl_uint64) (ind / 2);
    K->gauss_code = T;
    return K;
}

