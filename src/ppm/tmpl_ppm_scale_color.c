/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
 *  under the terms of the GNU General Public License as published by         *
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
 ******************************************************************************
 *                            tmpl_ppm_scale_color                            *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Scales the RGB values of a color by a real numbe.                     *
 ******************************************************************************
 *                             DEFINED FUNCTIONS                              *
 ******************************************************************************
 *  Function Name:                                                            *
 *      tmpl_PPM_Scale_Color                                                  *
 *  Purpose:                                                                  *
 *      Scale the individual components of an RGB color by a real number.     *
 *  Arguments:                                                                *
 *      color (tmpl_PPM_Color):                                               *
 *          The color being scaled.                                           *
 *      t (double):                                                           *
 *          The number being used to scale the color.                         *
 *  Output:                                                                   *
 *      scaled (tmpl_PPM_Color):                                              *
 *          The scaled color. The components (r, g, b) become (tr, tg, tb).   *
 *  Called Functions:                                                         *
 *      None.                                                                 *
 *  Method:                                                                   *
 *      Multiply the individual components by t and convert back to char's.   *
 *  Notes:                                                                    *
 *      If t*r, t*g, or t*b overflow, the result is mod UCHAR_MAX. For 8-bit  *
 *      unsigned char, this is 255.                                           *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) tmpl_ppm.h:                                                           *
 *          Header file containing function prototype and PPM color data type.*
 ******************************************************************************
 *                            A NOTE ON COMMENTS                              *
 ******************************************************************************
 *  It is anticipated that many users of this code will have experience in    *
 *  either Python or IDL, but not C. Many comments are left to explain as     *
 *  much as possible. Vagueness or unclear code should be reported to:        *
 *  https://github.com/ryanmaguire/libtmpl/issues                             *
 ******************************************************************************
 *                            A FRIENDLY WARNING                              *
 ******************************************************************************
 *  This code is compatible with the C89/C90 standard. The setup script that  *
 *  is used to compile this in make.sh uses gcc and has the                   *
 *  -pedantic and -std=c89 flags to check for compliance. If you edit this to *
 *  use C99 features (built-in complex, built-in booleans, C++ style comments *
 *  and etc.), or GCC extensions, you will need to edit the config script.    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March87, 2022                                                 *
 ******************************************************************************/

/*  PPM color typedef and function prototype found here.                      */
#include <libtmpl/include/tmpl_ppm.h>

/*  Function for scaling an RGB color by a real number.                       */
tmpl_PPM_Color tmpl_PPM_Scale_Color(tmpl_PPM_Color color, double t)
{
    /*  Variable for the output, the scaled color.                            */
    tmpl_PPM_Color scaled;

    /*  Convert the RGB values to double and scale the by the input t.        */
    const double r = t * (double)color.red;
    const double g = t * (double)color.green;
    const double b = t * (double)color.blue;

    /*  Convert these values back to unsigned char and return.                */
    scaled.red = (unsigned char)r;
    scaled.green = (unsigned char)g;
    scaled.blue = (unsigned char)b;
    return scaled;
}
/*  End of tmpl_PPM_Scale_Color.                                              */
