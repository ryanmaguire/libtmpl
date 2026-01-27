#if defined(_WIN32) || defined(_WIN64) || defined(_MSC_VER)
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/types/tmpl_svg_type.h>
#include <libtmpl/include/tmpl_svg.h>
#include <libtmpl/include/constants/tmpl_svg_canvas_default_constants.h>
#include <stdio.h>

void
tmpl_SVG_Init(tmpl_SVG *svg,
              const char * const filename,
              const tmpl_SVGCanvas * const canvas)
{
    /*  Make sure the input isn't a NULL pointer.                             */
    if (!svg)
        return;

    /*  If the user supplied an invalid string for the file name, treat this  *
     *  as an error. Do no attempt to create a new file.                      */
    if (!filename)
    {
        /*  Create an error message for the caller.                           */
        svg->error_occurred = tmpl_True;
        svg->error_message =
            "Error Encountered: libtmpl\n"
            "\ttmpl_SVG_Init_Default\n\n"
            "Input file name is NULL.\n";

        /*  Initialize the remaining variables to their zero values.          */
        svg->fp = NULL;
        svg->canvas = NULL;
        return;
    }

    /*  Check for a valid canvas. NULL pointers are treated as an error.      */
    if (!canvas)
    {
        /*  Create an error message for the caller.                           */
        svg->error_occurred = tmpl_True;
        svg->error_message =
            "Error Encountered: libtmpl\n"
            "\ttmpl_SVG_Init_Default\n\n"
            "Input canvas is NULL.\n";

        /*  Initialize the remaining variables to their zero values.          */
        svg->fp = NULL;
        svg->canvas = NULL;
        return;
    }

    /*  Try to open a new file and give it write permissions.                 */
    svg->fp = fopen(filename, "w");

    /*  Check if fopen failed. It returns NULL on failure.                    */
    if (!svg->fp)
    {
        /*  Again, indicate to the caller that the function failed.           */
        svg->error_occurred = tmpl_True;
        svg->error_message =
            "Error Encountered: libtmpl\n"
            "\ttmpl_SVG_Create_Default\n\n"
            "fopen returned NULL. Cannot create SVG file.\n";

        /*  Set the remaining variables to their zero values and abort.       */
        svg->fp = NULL;
        svg->canvas = NULL;
        return;
    }

    /*  Everything passed, set the error variables to their zero values.      */
    svg->error_occurred = tmpl_False;
    svg->error_message = NULL;

    /*  The canvas for the drawing is the user-supplied struct.               */
    svg->canvas = canvas;
}
