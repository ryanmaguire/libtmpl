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
 ******************************************************************************
 *                               DEPENDENCIES                                 *
 ******************************************************************************
 *  1.) stdio.h:                                                              *
 *          Standard C library containing the FILE data type.                 *
 *  2.) tmpl_bool.h:                                                          *
 *          Header file defining Booleans.                                    *
 *  3.) tmpl_vec2.h:                                                          *
 *          Header file providing two-dimensional vectors.                    *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       June 19, 2021                                                 *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_SVG_H
#define TMPL_SVG_H

/*  Standard library header containing the FILE data type.                    */
#include <stdio.h>

/*  Booleans found here.                                                      */
#include <libtmpl/include/tmpl_bool.h>

/*  2D vectors found here.                                                    */
#include <libtmpl/include/tmpl_vec2.h>

/*  Enumerated list of arrow types. Currently only three are provided, which  *
 *  are modeled after the tikz arrows. A no-arrow option is also provided. If *
 *  you want to flip the direction, use the Reverse option, i.e. something    *
 *  like tmpl_SVG_Reverse_Stealth_Arrow.                                      */
typedef enum tmpl_SVG_ArrowType_Def {
    tmpl_SVG_No_Arrow,
    tmpl_SVG_Stealth_Arrow,
    tmpl_SVG_Reverse_Stealth_Arrow,
    tmpl_SVG_Triangular_Arrow,
    tmpl_SVG_Reverse_Triangular_Arrow,
    tmpl_SVG_Latex_Arrow,
    tmpl_SVG_Reverse_Latex_Arrow
} tmpl_SVG_ArrowType;

/*  Struct for adding text and labelling things in the drawing.               */
typedef struct tmpl_SVG_Label_Def {
    char *content;
    tmpl_TwoVector anchor;
    tmpl_TwoVector shift;
    unsigned int fontsize;
    tmpl_Bool is_italic;
    tmpl_Bool is_bold;
} tmpl_SVG_Label;

/*  Macros for working with SVG labels.                                       */
#define tmpl_SVG_LABEL_FONTSIZE(label) ((label)->fontsize)
#define tmpl_SVG_LABEL_ANCHOR(label) ((label)->anchor)
#define tmpl_SVG_LABEL_SHIFT(label) ((label)->shift)
#define tmpl_SVG_LABEL_CONTENT(label) ((label)->content)
#define tmpl_SVG_LABEL_IS_BOLD(label) ((label)->is_bold)
#define tmpl_SVG_LABEL_IS_ITALIC(label) ((label)->is_italic)

/*  Simple struct for working with colors. Stores the RGB value of the color, *
 *  and allows for opacity with values between 0 and 1.                       */
typedef struct tmpl_SVG_Color_Def {
    unsigned char red, green, blue;
    double opacity;
} tmpl_SVG_Color;

/*  Useful colors to have predefined.                                         */
extern const tmpl_SVG_Color tmpl_SVG_Black;
extern const tmpl_SVG_Color tmpl_SVG_White;
extern const tmpl_SVG_Color tmpl_SVG_Red;
extern const tmpl_SVG_Color tmpl_SVG_Green;
extern const tmpl_SVG_Color tmpl_SVG_Blue;
extern const tmpl_SVG_Color tmpl_SVG_Cyan;
extern const tmpl_SVG_Color tmpl_SVG_Yellow;
extern const tmpl_SVG_Color tmpl_SVG_Magenta;

/*  This is the primary structure for using colors in drawings. It contains a *
 *  color, which allows for opacity (see above), a linewidth, and a string    *
 *  for optional dashed lines.                                                */
typedef struct tmpl_SVG_Pen_Def {
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
#define tmpl_SVG_DASH_ARRAY(pen) ((pen)->dash_array)

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
typedef struct tmpl_SVG_Arrow_Def {

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

/*  Arrows are stored in the palette for drawing later. These macros are for  *
 *  accessing the data an arrow contains.                                     */
#define tmpl_SVG_ARROW_TYPE(arrow) ((arrow)->arrow_type)
#define tmpl_SVG_ARROW_POSITION(arrow) ((arrow)->arrow_pos)
#define tmpl_SVG_ARROW_SIZE(arrow) ((arrow)->arrow_size)
#define tmpl_SVG_ARROW_COLOR(arrow) ((arrow)->line_pen)
#define tmpl_SVG_ARROW_FILL(arrow) ((arrow)->fill_pen)

/*  Various defaults for things like line width and arrow sizes.              */
#define tmpl_DEFAULT_ARROW_SIZE 0.1
#define tmpl_DEFAULT_ARROW_LINEWIDTH 0.05
#define tmpl_DEFAULT_TICK_SIZE 0.2
#define tmpl_DEFAULT_TICK_DIST 1.0
#define tmpl_DEFAULT_TICK_HEIGHT 0.1
#define tmpl_DEFAULT_LABEL_FONT_SIZE 10

/*  This struct is required for most routines and is included as an attribute *
 *  of several data types. It is used to convert between the geometry of the  *
 *  actual output file and the coordinates we use for computations.           */
typedef struct tmpl_SVG_Canvas_Def tmpl_SVG_Canvas;

/*  This function pointer is stored inside a tmpl_SVG_Canvas struct. The      *
 *  function takes in the canvas and a double and transforms the user's       *
 *  coordinates to the coordinates of the actual file.                        */
typedef double (*tmpl_SVG_Canvas_Transform)(tmpl_SVG_Canvas *, double);

/*  Actual definition of tmpl_SVG_Canvas struct.                              */
struct tmpl_SVG_Canvas_Def {

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
/*  End of tmpl_SVG_Canvas definition.                                        */

/*  Use these macros to access the data in a pointer to tmpl_SVG_Canvas.      */
#define tmpl_SVG_CANVAS_WIDTH(canvas) ((canvas)->width)
#define tmpl_SVG_CANVAS_HEIGHT(canvas) ((canvas)->height)
#define tmpl_SVG_CANVAS_X_SCALE(canvas) ((canvas)->x_scale)
#define tmpl_SVG_CANVAS_Y_SCALE(canvas) ((canvas)->y_scale)
#define tmpl_SVG_CANVAS_X_SHIFT(canvas) ((canvas)->x_shift)
#define tmpl_SVG_CANVAS_Y_SHIFT(canvas) ((canvas)->y_shift)
#define tmpl_SVG_CANVAS_X_TRANSFORM(canvas) ((canvas)->X_Transform)
#define tmpl_SVG_CANVAS_Y_TRANSFORM(canvas) ((canvas)->Y_Transform)
#define tmpl_SVG_CANVAS_BACKGROUND(canvas) ((canvas)->background)
#define tmpl_SVG_CANVAS_OUTLINE(canvas) ((canvas)->outline)

/*  Struct stored in paths and circles containing all of the info on how to   *
 *  draw the object.                                                          */
typedef struct tmpl_SVG_Palette_Def {

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

/*  These macros are for accessing data inside the actual palette.            */
#define tmpl_SVG_PALETTE_ARROWS(palette) ((palette)->arrows)
#define tmpl_SVG_PALETTE_CANVAS(palette) ((palette)->canvas)
#define tmpl_SVG_PALETTE_FILL_PEN(palette) ((palette)->fill_pen)
#define tmpl_SVG_PALETTE_LINE_PEN(palette) ((palette)->line_pen)
#define tmpl_SVG_PALETTE_LABELS(palette) ((palette)->labels)
#define tmpl_SVG_PALETTE_NUMBER_OF_ARROWS(palette) ((palette)->N_Arrows)
#define tmpl_SVG_PALETTE_NUMBER_OF_LABELS(palette) ((palette)->N_Labels)
#define tmpl_SVG_PALETTE_HAS_FILL_DRAW(palette) ((palette)->has_fill_draw)
#define tmpl_SVG_PALETTE_HAS_ARROWS(palette) ((palette)->has_arrows)
#define tmpl_SVG_PALETTE_HAS_LABELS(palette) ((palette)->has_labels)
#define tmpl_SVG_PALETTE_HAS_TICKS(palette) ((palette)->has_ticks)
#define tmpl_SVG_PALETTE_HAS_UPTICKS(palette) ((palette)->up_ticks)
#define tmpl_SVG_PALETTE_HAS_DOWNTICKS(palette) ((palette)->down_ticks)
#define tmpl_SVG_PALETTE_TICK_PEN(palette) ((palette)->tick_pen)
#define tmpl_SVG_PALETTE_TICK_START(palette) ((palette)->tick_start)
#define tmpl_SVG_PALETTE_TICK_FINISH(palette) ((palette)->tick_finish)
#define tmpl_SVG_PALETTE_TICK_DISTANCE(palette) ((palette)->tick_dx)
#define tmpl_SVG_PALETTE_TICK_HEIGHT(palette) ((palette)->tick_height)
#define tmpl_SVG_PALETTE_TICK_SEMIHEIGHT(palette) ((palette)->tick_semi_height)
#define tmpl_SVG_PALETTE_TICK_SEMISEMIHEIGHT(palette) \
    ((palette)->tick_semi_semi_height)

/*  Struct for working with SVG files.                                        */
typedef struct tmpl_SVG_Def {
    FILE *fp;
    tmpl_SVG_Canvas *canvas;
} tmpl_SVG;

/*  This is the primary data type used for drawing 2 dimensional figures.     */
typedef struct tmpl_SVG_Path2D_Def {

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

#define tmpl_SVG_PATH_DATA(path) ((path)->data)
#define tmpl_SVG_PATH_NUMBER_OF_POINTS(path) ((path)->N_Pts)

/*  This is the primary structure for working with and drawing circles. It    *
 *  contains geometric data as well as visual data for how to draw it.        */
typedef struct tmpl_SVG_Circle_Def {

    /*  The geometrical data of the circle. We need the center and the radius.*/
    tmpl_2DCircle *data;

    /*  Data for how to draw the path and the geometry of the page.           */
    tmpl_SVG_Palette *palette;
} tmpl_SVG_Circle;

/*  Macros for SVG circles.                                                   */
#define tmpl_SVG_CIRCLE_DATA(circle) ((circle)->data)
#define tmpl_SVG_CIRCLE_PALETTE(circle) ((circle)->palette)

/*  A data type for conviently dealing with lines.                            */
typedef struct tmpl_SVG_Line_Def {

    /*  The data for the line.                                                */
    tmpl_2DLine *data;

    /*  Boolean for determining if an error occured.                          */
    tmpl_Bool error_occured;

    /*  An error message which is set by various functions if an error occurs.*/
    char *error_message;

    /*  Data for how to draw the path and the geometry of the page.           */
    tmpl_SVG_Palette *palette;
} tmpl_SVG_Line;

/*  Macros for working with SVG lines.                                        */
#define tmpl_SVG_LINE_DATA(line) ((line)->data)
#define tmpl_SVG_LINE_PALETTE(line) ((line)->palette)

/*  The following macros are universal for all of the data types where the    *
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
                       tmpl_SVG_Color background, tmpl_SVG_Pen outline);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Destroy_SVG_Canvas                                               *
 *  Purpose:                                                                  *
 *      Destroy a canvas for an SVG file.                                     *
 *  Arguments:                                                                *
 *      canvas_ptr (tmpl_SVG_Canvas **):                                      *
 *          A pointer to a pointer to a tmpl_SVG_Canvas struct. This is the   *
 *          canvas that needs it memory freed.                                *
 *  Output:                                                                   *
 *      None (void).                                                          *
 *  Notes:                                                                    *
 *      This function must be called when terminating an SVG program, or you  *
 *      may have a memory leak. In reality, your operating system will free   *
 *      all memory allocated by the program once you are done, but still it's *
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

extern tmpl_SVG_Palette *
tmpl_SVG_Create_Palette(tmpl_SVG_Pen *line_pen, tmpl_SVG_Canvas *canvas);

extern void
tmpl_SVG_Palette_Set_Fill_Pen(tmpl_SVG_Palette *palette, tmpl_SVG_Pen *fpen);

extern void
tmpl_SVG_Palette_Add_Arrow(tmpl_SVG_Palette *palette,
                           double pos,
                           double arrow_size,
                           tmpl_SVG_Pen *fill_pen,
                           tmpl_SVG_Pen *line_pen,
                           tmpl_SVG_ArrowType type);

extern void tmpl_SVG_Palette_Add_Ticks(tmpl_SVG_Palette *palette,
                                       double tick_start,
                                       double tick_end,
                                       tmpl_SVG_Pen *tick_pen,
                                       double tick_dist,
                                       double tick_height,
                                       double tick_semi_height,
                                       double tick_semi_semi_height);

extern void
tmpl_SVG_Palette_Use_Up_Ticks(tmpl_SVG_Palette *palette);

extern void
tmpl_SVG_Palette_Use_Down_Ticks(tmpl_SVG_Palette *palette);

extern void
tmpl_SVG_Destroy_Palette(tmpl_SVG_Palette *palette);

extern tmpl_SVG_Label *
tmpl_Create_SVG_Label(const char *label_content,
                      tmpl_TwoVector anchor,
                      tmpl_SVG_Canvas *canvas);

extern void
tmpl_Destroy_SVG_Label(tmpl_SVG_Label *label);

extern void
tmpl_Reset_SVG_Label_Content(tmpl_SVG_Label *label, const char *content);

extern void
tmpl_Set_SVG_Label_Anchor(tmpl_SVG_Label *label, tmpl_TwoVector anchor);

extern void
tmpl_Set_SVG_Label_Shift(tmpl_SVG_Label *label, tmpl_TwoVector shift);

extern void
tmpl_Set_SVG_Label_FontSize(tmpl_SVG_Label *label, unsigned int font_size);


extern void
tmpl_Draw_SVG_Label(tmpl_SVG *svg, tmpl_SVG_Label *label);

extern tmpl_SVG_Path2D *
tmpl_Create_SVG_Path(tmpl_TwoVector start, tmpl_SVG_Palette *canvas);

extern void tmpl_Append_Path2D(tmpl_SVG_Path2D *path, tmpl_TwoVector P);
extern void tmpl_Close_Path2D(tmpl_SVG_Path2D *path);
extern void tmpl_Destroy_Path2D(tmpl_SVG_Path2D **path_pointer);

extern tmpl_SVG_Line *
ttmpl_CreateLineFromTwoPoints(tmpl_TwoVector P,
                              tmpl_TwoVector Q,
                              tmpl_SVG_Palette *palette);

extern tmpl_SVG_Line *
tmpl_CreateLineFromPointAndTangent(tmpl_TwoVector P,
                                   tmpl_TwoVector V,
                                   tmpl_SVG_Palette *palette);

extern void
tmpl_Destroy_Line(tmpl_SVG_Line *L);

extern void
tmpl_DrawPolygon2D(tmpl_SVG *svg, tmpl_SVG_Path2D *path);

extern void
tmpl_FillDrawPolygon2D(tmpl_SVG *svg, tmpl_SVG_Path2D *path);

extern void
tmpl_DrawCircle2D(tmpl_SVG *svg, tmpl_SVG_Circle *circle);

extern void
tmpl_FillDrawCircle2D(tmpl_SVG *svg, tmpl_SVG_Circle *circle);

extern void
tmpl_DrawLine2D(tmpl_SVG *cr, tmpl_SVG_Line *line, double t0, double t1);

extern void
tmpl_GenerateFile(char *filename, void (*instruction)(tmpl_SVG *),
                  double x_inches, double y_inches);

#endif
/*  End of include guard.                                                     */
