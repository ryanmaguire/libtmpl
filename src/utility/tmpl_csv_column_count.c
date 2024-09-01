#include <libtmpl/include/tmpl_utility.h>
#include <stdio.h>

size_t tmpl_CSV_Column_Count(FILE* file)
{
    char buffer[4096];
    const size_t zero = (size_t)0;
    size_t counter = (size_t)1;
    size_t n, chars_read;

    if (!file)
        return zero;

    while (1)
    {
        chars_read = fread(buffer, 1, sizeof(buffer), file);

        if (ferror(file))
        {
            counter = zero;
            goto FINISH;
        }

        for(n = zero; n < chars_read; n++)
        {
            if (buffer[n] == ',')
                counter++;

            else if (buffer[n] == '\n')
                goto FINISH;
        }

        if (feof(file))
            goto FINISH;
    }

FINISH:
    rewind(file);
    return counter;
}
