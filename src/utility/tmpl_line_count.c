#include <libtmpl/include/tmpl_utility.h>
#include <stdio.h>

size_t tmpl_Line_Count(FILE* file)
{
    char buffer[4096];
    const size_t zero = (size_t)0;
    size_t counter = zero;
    size_t n, chars_read;

    if (!file)
        return zero;

    while (1)
    {
        chars_read = fread(buffer, 1, sizeof(buffer), file);

        if (ferror(file))
            return zero;

        for(n = zero; n < chars_read; n++)
        {
            if (buffer[n] == '\n')
                counter++;
        }

        if (feof(file))
            break;
    }

    rewind(file);
    return counter;
}
