#include <cstdio>
#include <cstdlib>
#include <libtmpl/include/tmpl_sort.h>
#include <ctime>
#include <algorithm>

static double rand_real(void)
{
    int n = std::rand();
    return static_cast<double>(n) / static_cast<double>(RAND_MAX);
}

int main(void)
{
    const size_t len = static_cast<size_t>(1E7);
    double *arrtmpl = static_cast<double *>(std::malloc(sizeof(*arrtmpl)*len));
    double *arrcpp = static_cast<double *>(std::malloc(sizeof(*arrcpp)*len));
    size_t n;
    int success;
    clock_t t1, t2;

    for (n = 0; n < len; ++n)
    {
        double x = rand_real();
        arrtmpl[n] = x;
        arrcpp[n] = x;
    }

    t1 = std::clock();
    success = tmpl_Double_Merge_Sort(arrtmpl, len);
    t2 = std::clock();

    if (!success)
    {
        std::puts("tmpl_Double_Merge_Sort failed, malloc returned NULL.\n");
        return -1;
    }
    std::printf("libtmpl: %f\n", static_cast<double>(t2 - t1)/CLOCKS_PER_SEC);

    t1 = std::clock();
    std::sort(arrcpp, arrcpp + n);
    t2 = std::clock();
    std::printf("C++:     %f\n", static_cast<double>(t2 - t1)/CLOCKS_PER_SEC);

    for (n = 0; n < len; ++n)
    {
        if (arrtmpl[n] != arrcpp[n])
        {
            std::puts("FAIL");
            return -1;
        }
    }
    std::puts("PASS");
    return 0;
}
