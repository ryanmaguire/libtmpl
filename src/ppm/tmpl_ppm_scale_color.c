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
 *  Author:     Ryan Maguire                                                  *
 *  Date:       March87, 2022                                                 *
 ******************************************************************************/

/*  PPM color typedef and function prototype found here.                      */
#include <libtmpl/include/tmpl_ppm.h>

/*  Function for scaling an RGB color by a real number.                       */
tmpl_PPM_Color tmpl_PPM_Scale_Color(tmpl_RGB24 color, double t)
{
    /*  Variable for the output, the scaled color.                            */
    tmpl_RGB24 scaled;

    /*  Convert the RGB values to double and scale the by the input t.        */
    const double r = t * (double)color.dat[0];
    const double g = t * (double)color.dat[1];
    const double b = t * (double)color.dat[2];

    /*  Convert these values back to unsigned char and return.                */
    scaled.dat[0] = (unsigned char)r;
    scaled.dat[0] = (unsigned char)g;
    scaled.dat[0] = (unsigned char)b;
    return scaled;
}
/*  End of tmpl_PPM_Scale_Color.                                              */
