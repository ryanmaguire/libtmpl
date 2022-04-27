/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify           *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  libtmpl is distributed in the hope that it will be useful,                *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *
 ******************************************************************************/

#include <stdio.h>

int main(void)
{
    /*  Open the file include/tmpl_config.h using fopen and give the file     *
     *  write permissions. If using Windows, we'll need to use backslashes.   *
     *  Forward slashes fail to create the file.                              */
#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
    FILE *fp = fopen(".\\include\\tmpl_config.h", "w");
#else
    FILE *fp = fopen("./include/tmpl_config.h", "w");
#endif

    /*  If fopen fails, it returns NULL. Check that it did not.               */
    if (!fp)
    {
        puts("Error Encountered: libtmpl\n"
             "    det_inline.c\n"
             "fopen returned NULL for FILE *fp. Aborting.\n");
        return -1;
    }

    /*  Create the file include/tmpl_config.h and return.                     */
    fprintf(fp, "/******************************************************************************\n");
    fprintf(fp, " *                                  LICENSE                                   *\n");
    fprintf(fp, " ******************************************************************************\n");
    fprintf(fp, " *  This file is part of libtmpl.                                             *\n");
    fprintf(fp, " *                                                                            *\n");
    fprintf(fp, " *  libtmpl is free software: you can redistribute it and/or modify           *\n");
    fprintf(fp, " *  it under the terms of the GNU General Public License as published by      *\n");
    fprintf(fp, " *  the Free Software Foundation, either version 3 of the License, or         *\n");
    fprintf(fp, " *  (at your option) any later version.                                       *\n");
    fprintf(fp, " *                                                                            *\n");
    fprintf(fp, " *  libtmpl is distributed in the hope that it will be useful,                *\n");
    fprintf(fp, " *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *\n");
    fprintf(fp, " *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *\n");
    fprintf(fp, " *  GNU General Public License for more details.                              *\n");
    fprintf(fp, " *                                                                            *\n");
    fprintf(fp, " *  You should have received a copy of the GNU General Public License         *\n");
    fprintf(fp, " *  along with libtmpl.  If not, see <https://www.gnu.org/licenses/>.         *\n");
    fprintf(fp, " ******************************************************************************\n");
    fprintf(fp, " *                                tmpl_config                                 *\n");
    fprintf(fp, " ******************************************************************************\n");
    fprintf(fp, " *  Purpose:                                                                  *\n");
    fprintf(fp, " *      This file is created by the config.c file. It provides the macros     *\n");
    fprintf(fp, " *      TMPL_USE_INLINE, which is used by functions where the code might be   *\n");
    fprintf(fp, " *      inlined to increase performance, and TMPL_USE_MATH_ALGORITHMS, which  *\n");
    fprintf(fp, " *      determines if libtmpl's libm implementation should be used, or if the *\n");
    fprintf(fp, " *      C standard library math.h should be used.                             *\n");
    fprintf(fp, " ******************************************************************************/\n\n");
    fprintf(fp, "#ifndef TMPL_CONFIG_H\n");
    fprintf(fp, "#define TMPL_CONFIG_H\n\n");

#ifdef TMPL_SET_INLINE_TRUE
    fprintf(fp, "#define TMPL_USE_INLINE 1\n");
#else
    fprintf(fp, "#define TMPL_USE_INLINE 0\n");
#endif

#ifdef TMPL_SET_USE_MATH_TRUE
    fprintf(fp, "#define TMPL_USE_MATH_ALGORITHMS 1\n");
#else
    fprintf(fp, "#define TMPL_USE_MATH_ALGORITHMS 0\n");
#endif

    fprintf(fp, "#endif\n");
    fclose(fp);
    return 0;
}
