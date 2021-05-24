
#include <libtmpl/include/tmpl_void_pointer.h>

void
tmpl_get_void_from_void_l2l(void *in, void *out,
                            unsigned long int dim,
                            long int (*f)(long int))
{
    unsigned long int n;
    long int *out_data = out;

#ifdef _OPENMP
#pragma omp parallel for
#endif
    for (n=0; n<dim; ++n)
        out_data[n] = f(((long *)in)[n]);
}

