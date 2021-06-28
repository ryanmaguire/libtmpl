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
 ******************************************************************************
 *                                tmpl_svg                                    *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide tools for creating SVG files.                                 *
 *  Data Types:                                                               *
 *      tmpl_TwoVector:                                                       *
 *          Primary tool for two-dimensional/planar geometry and drawing. It  *
 *          is a data type used to represent the ordered pair (x, y).         *
 *      tmpl_TwoByTwoMatrix:                                                  *
 *          A data type representing a 2x2 matrix. Used for applying linear   *
 *          transformations to a tmpl_TwoVector.                              *
 *      tmpl_Canvas:                                                          *
 *          A struct which contains all of the necessary data to transform    *
 *          the intrinsic geometry of the output file (.ps, .svg, or whatever *
 *          is being produced) to the coordinate geometry of the user.        *
 *      tmpl_Path2D:                                                          *
 *          A struct containing a pointer to a tmpl_TwoVector, as well as     *
 *          data for the drawing like color, line width, etc.                 *
 *      tmpl_Pen:                                                             *
 *          A struct containing red, green, and blue values (r g, b). The     *
 *          values use real numbers between 0 and 1, and not chars between 0  *
 *          and 255. It contains information about the transparency of the    *
 *          object and it's linewidth.                                        *
 *      tmpl_SVG_Palette:                                                     *
 *          A struct with lots of data about how to draw an object. This      *
 *          includes line pens, fill pens, tick marks, labels, arrows, etc.   *
 *      tmpl_ArrowType:                                                       *
 *          An integer corresponding to various arrow styles.                 *
 *      tmpl_Arrow:                                                           *
 *          A struct containing data pertaining to arrows stored in paths.    *
 *          This includes size, color, fill color, and more.                  *
 *      tmpl_Circle:                                                          *
 *          Data structure for circles, including a tmpl_TwoVector for the    *
 *          center and a double for the radius. In addition it contains data  *
 *          for drawing the circle.                                           *
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) stdio.h:                                                              *
 *          Standard C library containing the FILE data type.                 *
 *  2.) tmpl_bool.h:                                                          *
 *          Header file defining Booleans.                                    *
 *  3.) tmpl_euclidean_planar_geometry.h:                                     *
 *          Header file providing two-dimensional vectors.                    *
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
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       June 19 2021                                                  *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_SVG_H
#define TMPL_SVG_H

#include <stdio.h>
#include <libtmpl/include/tmpl_bool.h>
#include <libtmpl/include/tmpl_euclidean_planar_geometry.h>

/*  Enumerated list of arrow types. Currently only three are provided, which  *
 *  are modeled after the tikz arrows. A no-arrow option is also provided. If *
 *  you want to flip the direction, use the Reverse option, i.e. something    *
 *  like tmpl_SVG_Reverse_Stealth_Arrow.                                      */
typedef enum {
    tmpl_SVG_No_Arrow,
    tmpl_SVG_Stealth_Arrow,
    tmpl_SVG_Reverse_Stealth_Arrow,
    tmpl_SVG_Triangular_Arrow,
    tmpl_SVG_Reverse_Triangular_Arrow,
    tmpl_SVG_Latex_Arrow,
    tmpl_SVG_Reverse_Latex_Arrow
} tmpl_SVG_ArrowType;

/*  Struct for adding text and labelling things in the drawing.               */
typedef struct _tmpl_SVG_Label {
    char *string;
    tmpl_TwoVector anchor;
    tmpl_TwoVector shift;
    unsigned int fontsize;
    tmpl_Bool is_italic;
    tmpl_Bool is_bold;
} tmpl_SVG_Label;

/*  Simple struct for working with colors. Stores the RGB value of the color, *
 *  and allows for opacity with values between 0 and 1.                       */
typedef struct _tmpl_SVG_Color {
    unsigned char red, green, blue;
    double opacity;
} tmpl_SVG_Color;

/*  Useful colors to have predefined.                                         */
extern const tmpl_SVG_Color tmpl_SVG_Black;
extern const tmpl_SVG_Color tmpl_SVG_White;
extern const tmpl_SVG_Color tmpl_SVG_Red;
extern const tmpl_SVG_Color tmpl_SVG_Green;
extern const tmpl_SVG_Color tmpl_SVG_Blue;
extern const tmpl_SVG_Color tmpl_SVG_Yellow;

/*  This is the primary structure for using colors in drawings. It contains a *
 *  color, which allows for opacity (see above), a linewidth, and a string    *
 *  for optional dashed lines.                                                */
typedef struct _tmpl_SVG_Pen {
    tmpl_SVG_Color color;
    double linewidth;
    char *dash_array;
} tmpl_SVG_Pen;

/*  Macros for working with pens.                                             */
#define tmpl_SVG_AXES_PEN 1.0
#define tmpl_SVG_THIN_PEN 0.2
#define tmpl_SVG_THICK_PEN 0.8
#define tmpl_SVG_DEFAULT_PEN 0.4
#define tmpl_SVG_PEN_RED(pen) (((pen)->color).red)
#define tmpl_SVG_PEN_GREEN(pen) (((pen)->color).green)
#define tmpl_SVG_PEN_BLUE(pen) (((pen)->color).blue)
#define tmpl_SVG_PEN_OPACITY(pen) (((pen)->color).opacity)
#define tmpl_SVG_PEN_LINEWIDTH(pen) ((pen)->linewidth)

/*  Common pens.                                                              */
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_Blue;
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_Green;
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_Red;
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_Black;
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_White;
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_DarkGray;
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_Gray;
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_LightGray;
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_Aqua;
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_Purple;
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_Violet;
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_Pink;
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_Yellow;
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_Crimson;
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_DarkGreen;
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_Orange;
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_LightBlue;
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_Teal;
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_DarkBlue;
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_Lavender;
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_Magenta;
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_DeepPink;
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_Marine;
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_Lime;
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_Carrot;
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_Brown;
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_Azure;
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_Silver;
extern const tmpl_SVG_Pen *tmpl_SVG_Pen_Sand;

/*  Struct containing all of the information for arrows.                      */
typedef struct _tmpl_SVG_Arrow {

    /*  The type of arrow to draw. (Stealth, triangle, LaTeX, or none).       */
    tmpl_SVG_ArrowType arrow_type;

    /*  The position of the arrow, which should be number between 0 and 1.    */
    double arrow_pos;

    /*  Boolean for determining if an error occured.                          */
    tmpl_Bool error_occured;

    /*  An error message which is set by various functions if an error occurs.*/
    char *error_message;

    /*  The color of the interior of the arrow drawn.                         */
    tmpl_SVG_Pen *fill_pen;

    /*  The color of the outline of the arrow.                                */
    tmpl_SVG_Pen *line_pen;

    /*  The radius of the arrow head. The arrow head is defined by three      *
     *  points on a circle about the point corresponding to the arrow_pos.    */
    double arrow_size;
} tmpl_SVG_Arrow;

/*  This struct is required for most routines and is included as an attribute *
 *  of several data types. It is used to convert between the geometry of the  *
 *  actual output file and the coordinates we use for computations.           */
typedef struct _tmpl_SVG_Canvas tmpl_SVG_Canvas;

/*  This function pointer is stored inside a _tmpl_SVG_Canvas struct. The     *
 *  function takes in the canvas and a double and transforms the user's       *
 *  coordinates to the coordinates of the actual file.                        */
typedef double (*tmpl_SVG_Canvas_Transform)(tmpl_SVG_Canvas *, double);

/*  Actual definition of _tmpl_SVG_Canvas struct.                             */
struct _tmpl_SVG_Canvas {
    /*  The size of the SVG, in pixels.                                       */
    unsigned int width, height;

    /*  x_shift and y_shift are used to center the figure. The center is not  *
     *  taken to be (0, 0), but rather the value corresponding to             *
     *  (width, height) / 2.                                                  */
    double x_shift, y_shift;

    /*  x_scale and y_scale are the scales applied to the user's coordinates  *
     *  so that the image is the correct size in the actual file.             */
    double x_scale, y_scale;

    /*  The background color of the SVG.                                      */
    tmpl_SVG_Color background;

    /*  The outline color and thickness for the SVG.                          */
    tmpl_SVG_Pen outline;

    /*  Transform functions are stored inside the canvas for ease of access.  */
    tmpl_SVG_Canvas_Transform X_Transform;
    tmpl_SVG_Canvas_Transform Y_Transform;
};
/*  End of _tmpl_SVG_Canvas definition.                                       */

/*  Struct stored in paths and circles containing all of the info on how to   *
 *  draw the object.                                                          */
typedef struct _tmpl_SVG_Palette {

    /*  Boolean for determining if there are lables along the path.           */
    tmpl_Bool has_labels;

    /*  Pointer to the labels of the path.                                    */
    tmpl_SVG_Label **labels;

    /*  The number of labels on the path.                                     */
    unsigned int N_Labels;

    /*  Boolean for determining if the region enclosed should be filled in.   *
     *  Default is set to false. If this Boolean is set to true, the various  *
     *  drawing routines will automatically set is_closed to true.            */
    tmpl_Bool has_fill_draw;

    /*  Boolean for determining if the path has arrows on it.                 */
    tmpl_Bool has_arrows;

    /*  Pointer to the arrows stored on the path.                             */
    tmpl_SVG_Arrow **arrows;

    /*  The number of arrows.                                                 */
    unsigned int N_Arrows;

    /*  The color of the interior of the region enclosed by the path. This is *
     *  only used if the has_fill_draw Boolean is set.                        */
    tmpl_SVG_Pen *fill_pen;

    /*  The color of the path.                                                */
    tmpl_SVG_Pen *line_pen;

    /*  Where the ticks should start. This is parameterized by the arc length *
     *  of the object. That is, if you set tick_start = 0 there will be a     *
     *  tick at the very start of the path.                                   */
    double tick_start;

    /*  Where the tick marks stop.                                            */
    double tick_finish;

    /*  Boolean for use of tick marks. Default is False.                      */
    tmpl_Bool has_ticks;

    /*  Boolean for only having ticks "above" the axis. For the x-axis, where *
     *  tick_start is to the left of tick_finish, the ticks will indeed be    *
     *  pointing "up". For the y-axis, with tick_start below tick_finish, the *
     *  ticks will point to the "left" since this is just a rotation of the   *
     *  x-axis. Keep this in mind when drawing. If you want up ticks for the  *
     *  x-axis but right ticks for the y-axis, use down_ticks for y.          */
    tmpl_Bool up_ticks;

    /*  Like up_ticks, but used to point the ticks "down".                    */
    tmpl_Bool down_ticks;

    /*  The distance between ticks. This should be either 0.25, 0.5, 1.0, or  *
     *  some integer. This is to get full use of tick_height,                 *
     *  tick_semi_height, and tick_semi_semi_height which plots ticks of      *
     *  different heights on a cycle of four. Any value is allowed, however.  */
    double tick_dx;

    /*  The major height of the ticks. This is the height of every fourth     *
     *  tick mark. That is, when the tick number is divisible by four, this   *
     *  height is used.                                                       */
    double tick_height;

    /*  The tick height for the ticks whose number is even, but not divisible *
     *  by four.                                                              */
    double tick_semi_height;

    /*  The tick height for the odd-numbered ticks.                           */
    double tick_semi_semi_height;

    /**************************************************************************
     *  Below is an example of what the ticks will look like. The tallest     *
     *  are the ticks_height, smallest are ticks_semi_semi_height, and the    *
     *  middle is the ticks_semi_height. Note, by default when an axis is     *
     *  created the three ticks values are set to be the same.                *
     *                                                                        *
     *  |                               |                               |     *
     *  |               |               |               |               |     *
     *  |_______|_______|_______|_______|_______|_______|_______|_______|     *
     **************************************************************************/

    /*  The color of the ticks. Default is black.                             */
    tmpl_SVG_Pen *tick_pen;

    /*  The canvas of the entire drawing.                                     */
    tmpl_SVG_Canvas *canvas;
} tmpl_SVG_Palette;

typedef struct _tmpl_SVG {
    FILE *fp;
    tmpl_SVG_Canvas *canvas;
} tmpl_SVG;

/*  This is the primary data type used for drawing 2 dimensional figures.     */
typedef struct _tmpl_SVG_Path2D {

    /*  This pointer contains all of the points of the path.                  */
    tmpl_TwoVector *data;

    /*  The number of points in the data pointer.                             */
    unsigned long int N_Pts;

    /*  Boolean for determining if an error occured.                          */
    tmpl_Bool error_occured;

    /*  An error message which is set by various functions if an error occurs.*/
    char *error_message;

    /*  Boolean for determining if the object is meant to be closed or not.   *
     *  If you wish to use fill draw with the object, this must be true.      */
    tmpl_Bool is_closed;

    /*  Data for how to draw the path and the geometry of the page.           */
    tmpl_SVG_Palette *palette;
} tmpl_SVG_Path2D;

/*  This is the primary structure for working with and drawing circles. It    *
 *  contains geometric data as well as visual data for how to draw it.        */
typedef struct _tmpl_SVG_Circle {

    /*  The geometrical data of the circle. We need the center and the radius.*/
    tmpl_Circle2D *data;

    /*  Data for how to draw the path and the geometry of the page.           */
    tmpl_SVG_Palette *palette;
} tmpl_SVG_Circle;

/*  Macros for SVG circles.                                                   */
#define tmpl_SVG_CIRCLE_CENTER(circle) (((circle)->data).center)
#define tmpl_SVG_CIRCLE_RADIUS(circle) ((circle)->radius)
#define tmpl_SVG_CIRCLE_IS_LINE(circle) ((circle)->is_line)
#define tmpl_SVG_CIRCLE_POINT(circle) (((circle)->data).line.P)
#define tmpl_SVG_CIRCLE_TANGENT(circle) (((circle)->data).line.V)

/*  A data type for conviently dealing with lines.                            */
typedef struct _tmpl_SVG_Line {

    /*  A point that lies on the line.                                        */
    tmpl_TwoVector P;

    /*  The tangent/velocity vector of the line. That is, the direction the   *
     *  line points in.                                                       */
    tmpl_TwoVector V;

    /*  Boolean for determining if an error occured.                          */
    tmpl_Bool error_occured;

    /*  An error message which is set by various functions if an error occurs.*/
    char *error_message;

    /*  Data for how to draw the path and the geometry of the page.           */
    tmpl_SVG_Palette *palette;
} tmpl_SVG_Line;

/*  Macros for working with SVG lines.                                        */
#define tmpl_SVG_LINE_POINT(L) ((L)->P)
#define tmpl_SVG_LINE_TANGENT(L) ((L)->V)

/*  The following macros are universal all of the data types where the        *
 *  attribute applies.                                                        */
#define tmpl_HAS_ERROR(obj) ((obj)->error_occured)
#define tmpl_GET_PALETTE(obj) ((obj)->palette)
#define tmpl_SET_PALETTE(obj, palette) ((obj)->palette = palette)
#define tmpl_SET_ERROR(obj, error) ((obj)->error_occured = error)
#define tmpl_ERROR_MESSAGE(obj) ((obj)->error_message)

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Create_SVG_Canvas                                                *
 *  Purpose:                                                                  *
 *      Creates a canvas for an SVG file.                                     *
 *  Arguments:                                                                *
 *      width (unsigned int):                                                 *
 *          The width of the SVG, in pixels.                                  *
 *      height (unsigned int):                                                *
 *          The height of the SVG, in pixels.                                 *
 *      x_min (double):                                                       *
 *          The smallest value on the x-axis that is plotted.                 *
 *      x_max (double):                                                       *
 *          The largest value on the x-axis that is plotted.                  *
 *      y_min (double):                                                       *
 *          The smallest value on the y-axis that is plotted.                 *
 *      y_max (double):                                                       *
 *          The largest value on the y-axis that is plotted.                  *
 *      background (tmpl_SVG_Color):                                          *
 *          The color of the background of the SVG.                           *
 *      outline (tmpl_SVG_Pen):                                               *
 *          The color of the outline of the SVG.                              *
 *      use_one_to_one_aspect_ratio (tmpl_Bool):                              *
 *          Boolean for determining if a 1:1 aspect ratio should be forced.   *
 *  Output:                                                                   *
 *      canvas (tmpl_SVG_Canvas *):                                           *
 *          A pointer to an SVG canvas.                                       *
 *  Notes:                                                                    *
 *      If malloc fails, the resulting pointer is NULL. To avoid segfaults,   *
 *      check that the resulting pointer is not NULL before using it.         *
 *  Source Code:                                                              *
 *      libtmpl/src/svg/tmpl_create_svg_canvas.c                              *
 *  Examples:                                                                 *
 *                                                                            *
 ******************************************************************************/
extern tmpl_SVG_Canvas *
tmpl_Create_SVG_Canvas(unsigned int width, unsigned int height,
                       double x_min, double x_max, double y_min, double y_max,
                       tmpl_SVG_Color background, tmpl_SVG_Pen outline,
                       tmpl_Bool use_one_to_one_aspect_ratio);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Destory_SVG_Canvas                                               *
 *  Purpose:                                                                  *
 *      Destory a canvas for an SVG file.                                     *
 *  Arguments:                                                                *
 *      canvas_ptr (tmpl_SVG_Canvas **):                                      *
 *          A pointer to a pointer to a tmpl_SVG_Canvas struct. This is the   *
 *          canvas that needs it memory freed.                                *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      This function must be called when terminating an SVG program, or you  *
 *      may have a memory leak. In reality, your operating will free all      *
 *      memory allocated by the program once you are done, but still it's     *
 *      better to be on the safe side.                                        *
 *  Source Code:                                                              *
 *      libtmpl/src/svg/tmpl_destroy_svg_canvas.c                             *
 *  Examples:                                                                 *
 *                                                                            *
 ******************************************************************************/
extern void tmpl_Destroy_SVG_Canvas(tmpl_SVG_Canvas **canvas_ptr);

extern tmpl_SVG *
tmpl_Create_SVG(const char *filename, tmpl_SVG_Canvas *canvas);

extern void
tmpl_Destroy_SVG(tmpl_SVG **svg_ptr);

extern void
tmpl_SVG_Set_Arrow_Type(tmpl_SVG_Arrow *arrow, tmpl_SVG_ArrowType type);

extern void
tmpl_SVG_Set_Arrow_Pos(tmpl_SVG_Arrow *arrow, double pos);

extern void
tmpl_SVG_Set_Arrow_Size(tmpl_SVG_Arrow *arrow, double size);

extern tmpl_SVG_Arrow *
tmpl_SVG_Create_Arrow(double pos, double arrow_size, tmpl_SVG_Color *fill_color,
                      tmpl_SVG_Pen *line_pen, tmpl_SVG_ArrowType type);

extern tmpl_SVG_Circle *
tmpl_Create_SVG_Circle(tmpl_TwoVector P, double r, tmpl_SVG_Palette *palette);

extern void
tmpl_Circle2D_As_Line(tmpl_Circle2D *circle,
                      tmpl_TwoVector P, tmpl_TwoVector V);

extern void
tmpl_Reset_Circle2D(tmpl_Circle2D *circle, tmpl_TwoVector P, double r);

extern void
tmpl_Destroy_Circle2D(tmpl_Circle2D **circle);

extern tmpl_SVG_Line *
tmpl_Create_SVG_Line_From_Two_Points(tmpl_TwoVector P, tmpl_TwoVector Q,
                                     tmpl_SVG_Palette *palette);

extern tmpl_SVG_Line *
tmpl_Create_SVG_Line_From_Point_And_Tangent(tmpl_TwoVector P,
                                            tmpl_TwoVector V,
                                            tmpl_SVG_Palette *palette);

extern void
tmpl_Destroy_SVG_Line(tmpl_SVG_Line **line_pointer);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Create_Pen                                                       *
 *  Purpose:                                                                  *
 *      Create a tmpl_Color from three doubles.                               *
 *  Arguments:                                                                *
 *      double red:                                                           *
 *          The amount of red in the color.                                   *
 *      double green:                                                         *
 *          The amount of green in the color.                                 *
 *      double blue:                                                          *
 *          The amount of blue in the color.                                  *
 *  Outputs:                                                                  *
 *      tmpl_Color color:                                                     *
 *          The color with rgb value (red, green, blue).                      *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 *  NOTE:                                                                     *
 *      Malloc is used in this file to allocate the appropriate memory. You   *
 *      must called kissvg_DestroyColor when you are done with the color.     *
 ******************************************************************************/
extern tmpl_SVG_Pen *
tmpl_Create_SVG_Pen(unsigned char red, unsigned char green, unsigned char blue,
                    double linewidth, tmpl_Bool transparent, double opacity);

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_DestroyColor                                                   *
 *  Purpose:                                                                  *
 *      Destroy a kissvg_Color and free its memory.                           *
 *  Arguments:                                                                *
 *      kissvg_Color color:                                                   *
 *          The color to be destroyed.                                        *
 *  Outputs:                                                                  *
 *      None, this is a void function.                                        *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 *  NOTE:                                                                     *
 *      This function must be called if kissvg_CreateColor was used.          *
 ******************************************************************************/
extern void
tmpl_Destroy_SVG_Pen(tmpl_SVG_Pen **color_pointer);

extern void
tmpl_SVG_Pen_Change_Linewidth(tmpl_SVG_Pen *pen, double linewidth);

extern void
tmpl_SVG_Pen_Change_Transparency(tmpl_SVG_Pen *pen, double alpha);

#endif
/*  End of include guard.                                                     */
