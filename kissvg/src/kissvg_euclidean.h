
#ifndef _KISSVG_EUCLIDEAN_H_
#define _KISSVG_EUCLIDEAN_H_

#include "kissvg_defs.h"


/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_Euclidean_Orthogonal_Vector_2D                                 *
 *  Purpose:                                                                  *
 *      Compute a vector which is orthogonal to the input.                    *
 *  Arguments:                                                                *
 *      kissvg_TwoVector V:                                                   *
 *          A kissvg_TwoVector.                                               *
 *  Outputs:                                                                  *
 *      kissvg_TwoVector orth:                                                *
 *          A vector orthogonal to V.                                         *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 ******************************************************************************/
extern kissvg_TwoVector
kissvg_Euclidean_Orthogonal_Vector_2D(kissvg_TwoVector V);

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_EuclideanFindCenter2D                                          *
 *  Purpose:                                                                  *
 *      Find the center of three kissvg_TwoVector's. If the points are        *
 *      collinear the return is (inf, inf). In other words, three collinear   *
 *      points have their center "at infinity."                               *
 *  Arguments:                                                                *
 *      kissvg_TwoVector A:                                                   *
 *          A kissvg_TwoVector.                                               *
 *      kissvg_TwoVector B:                                                   *
 *          Another vector.                                                   *
 *      kissvg_TwoVector C:                                                   *
 *          A third vector.                                                   *
 *  Outputs:                                                                  *
 *      kissvg_Circle circle:                                                 *
 *          The circle containing A, B, and C. If A, B, and C are collinear,  *
 *          the circle is set to the line containing them. If all three are   *
 *          equal an error_occured Boolean is set to true.                    *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 ******************************************************************************/
extern kissvg_Circle *kissvg_Euclidean_Find_Center_2D(kissvg_TwoVector A,
                                                      kissvg_TwoVector B,
                                                      kissvg_TwoVector C);

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_PlaneToDiskHomeo                                               *
 *  Purpose:                                                                  *
 *      Transform, smoothly, the plane to the unit disk. This is the inverse  *
 *      of the diffeomorphism:                                                *
 *                                                                            *
 *                                  2 (x, y)                                  *
 *          f(x, y) =  -----------------------------------                    *
 *                      (1 - ||(x, y)||) (1 + ||(x, y)||)                     *
 *                                                                            *
 *      which stetches the unit disk out to the entire plane.                 *
 *  Arguments:                                                                *
 *      kissvg_TwoVector A:                                                   *
 *          A kissvg_TwoVector.                                               *
 *  Outputs:                                                                  *
 *      kissvg_Twovector B:                                                   *
 *          B transformed to the unit disk.                                   *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 ******************************************************************************/
extern kissvg_TwoVector kissvg_Plane_To_Disk_Homeo(kissvg_TwoVector P);

extern kissvg_TwoVector *
kissvg_Circle_Intersection(kissvg_Circle *C1, kissvg_Circle *C2);

extern kissvg_Circle **
kissvg_Apollonius_Problem(kissvg_Circle *circle1, kissvg_Circle *circle2,
                          kissvg_Circle *circle3);

extern kissvg_TwoVector
kissvg_Closest_Point_On_Circle(kissvg_Circle *C, kissvg_TwoVector P);

extern kissvg_TwoVector
kissvg_Furthest_Point_On_Circle(kissvg_Circle *C, kissvg_TwoVector P);

extern kissvg_TwoVector
kissvg_Closest_Point_On_Line2D(kissvg_Line2D *L, kissvg_TwoVector P);

/******************************************************************************
 *  Function:                                                                 *
 *      kissvg_Line2D_Intersection                                            *
 *  Purpose:                                                                  *
 *      Returns the point of intersection of two lines L0 and L1.             *
 *  Arguments:                                                                *
 *      kissvg_Line2D *L0:                                                    *
 *          A pointer to the first line.                                      *
 *      kissvg_Line2D *L1:                                                    *
 *          A pointer to the second line.                                     *
 *  Output:                                                                   *
 *      kissvg_TwoVector kissvg_TwoVector:                                    *
 *          The point of intersection of the two lines. If the lines are      *
 *          parallel, or if they are the same line, this returns the "point"  *
 *          (+infinity, +infinity).                                           *
 *  Location:                                                                 *
 *      The source code is contained in src/kissvg.c                          *
 ******************************************************************************/
extern kissvg_TwoVector
kissvg_Line2D_Intersection(kissvg_Line2D *L0, kissvg_Line2D *L1);

#endif
