

#include <libtmpl/include/types/tmpl_svg_canvas.h>
#include <libtmpl/include/constants/tmpl_svg_canvas_default_constants.h>
#include <libtmpl/include/constants/tmpl_rgb24_constants.h>
#include <stddef.h>

const tmpl_SVGCanvas tmpl_SVGCanvas_Default = {

    /*  Width and height, in pixels.                                          */
    1024, 1024,

    /*  Scale factors for the x and y axes. Equal to length / (max - min)     *
     *  where length is the size of the axis, and max and min are the actual  *
     *  values in the plane (i.e., not the pixel count) for the boundaries.   */
    128.0, 128.0,

    /*  Shift factors for both axes. The default canvas is centered about the *
     *  origin, so the shift factors are just half the size of the axes.      */
    512.0, 512.0,

    /*  Background color, default canvas is white.                            */
    &tmpl_RGB24_White,

    /*  Default outline is invisible. Set pen to NULL.                        */
    NULL
};
