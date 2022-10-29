/******************************************************************************
 *                                 LICENSE                                    *
 ******************************************************************************
 *  This file is part of libtmpl.                                             *
 *                                                                            *
 *  libtmpl is free software: you can redistribute it and/or modify it        *
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
 *                           tmpl_graph_theory                                *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Provide tools for various types of graphs arising in graph theory     *
 *      such as simple graphs, multi-graphs, signed graphs, and directed      *
 *      graphs. Many of these tools are used in knot theory as well.          *
 *  NOTES:                                                                    *
 *      This file is a fork of the complex library I wrote for rss_ringoccs.  *
 *      rss_ringoccs is also released under GPL 3.                            *
 ******************************************************************************
 *  Author:     Ryan Maguire, Dartmouth College                               *
 *  Date:       April 2, 2021                                                 *
 ******************************************************************************
 *                             Revision History                               *
 ******************************************************************************
 *  2021/03/02: Ryan Maguire                                                  *
 *      Created file.                                                         *
 ******************************************************************************/

/*  Include guard to prevent including this file twice.                       */
#ifndef TMPL_GRAPH_THEORY_H
#define TMPL_GRAPH_THEORY_H

#include "tmpl_exports.h"

#include <libtmpl/include/tmpl_bool.h>

/*  An edge is represented by an unordered pair of unsigned integers v0 and   *
 *  v1. We can represent the direction of an edge by whether or not we want   *
 *  to write (v0,v1) or (v1,v0). (v0,v1) represents forward and (v1,v0)       *
 *  represents reverse. Undirected means the edge has no direction, or        *
 *  equivalently that both directions are legal.                              */
typedef enum tmpl_GraphEdgeDirection {
    tmpl_UndirectedGraphEdge,
    tmpl_ForwardGraphEdge,
    tmpl_ReverseGraphEdge
} tmpl_GraphEdgeDirection;

/*  An edge in a graph will allow for multiplicity, signs, and directions.    *
 *  This will let us cut down the number of different structs we need to use  *
 *  for graphs.                                                               */
typedef struct tmpl_GraphEdge {

    /*  Vertices are represented by 32-bit unsigned integers. This means a    *
     *  graph can have, at a maximum, 2^32 = 4,294,967,296 vertices.          */
    unsigned long int v0;
    unsigned long int v1;

    /*  A 32-bit unsigned integer is used to represent multiplicity in a      *
     *  graph edge. If the multiplicity is 1, this is a simple edge.          */
    unsigned long int multiplicity;

    /*  For each multiplicity we need a graph direction corresponding to      *
     *  this edge. We'll use a pointer to the tmpl_GraphEdgeDirection enum    *
     *  data type to represent this.                                          */
    tmpl_GraphEdgeDirection *dirs;

    /*  For each multiplicity we can also assign weights to the corresponding *
     *  edge. This is done via a pointer to a double array.                   */
    double *weights;

    /*  Lastly, signed edges are useful in knot theory, and we'll allow for   *
     *  these via a pointer to a signed char to preserve memory. We only need *
     *  -1, 0, and 1. We'll need a sign for every multiplicity in the edge,   *
     *  so we use a pointer to a signed char array.                           */
    signed char *signs;

} tmpl_GraphEdge;

/*  A graph is a set of vertices and a set of edges. We'll define a struct    *
 *  to represent this notion.                                                 */
typedef struct tmpl_Graph {
    /*  The vertex set is represented by a single non-negative integer. For   *
     *  every non-negative integer less than this value  there exists a       *
     *  vertex in this graph. So, for example, if the vertex number is 5,     *
     *  then there are 5 vertices in the graph, and they are represented by   *
     *  the values 0, 1, 2, 3, 4. We could then ask if {0,3} is an edge in    *
     *  the graph. Asking about {2,7} or {1,5} is meaningless, since the      *
     *  values 5 and 7 do not correspond to vertices in the graph.            */
    unsigned long int vertex_number;

    /*  The total number of edges possible is n*(n+1)/2+n, where n is the     *
     *  vertex number. This corresponds to the complete graph K_n with        *
     *  self-edges. That is, every vertex is connected to every other vertex, *
     *  including an edge between a vertex an itself. Multiplicity is NOT     *
     *  included in this value. Multiplicity of an edge is recorded in the    *
     *  edge structure. The edge number simply keeps track of values (v0, v1),*
     *  with v0 <= v1, that exist as edges in the graph. Since the total      *
     *  number of vertices is bounded by a 32-bit number, a 64-bit number is  *
     *  large enough to store the maximum number of edges for any such graph. */
    unsigned long int edge_number;

    /*  We then use a pointer to the edge structure to record the edges.      */
    tmpl_GraphEdge *edges;

} tmpl_Graph;

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Sort_Graph_Edges                                                 *
 *  Purpose:                                                                  *
 *      Sorts the edges in a graph via lexicographic ordering of the          *
 *      vertices in an edge. That is, since an edge is an ordered pair of     *
 *      non-negative integers (m, n) we can produce a total order on the edge *
 *      set via lexicographic, also called "dictionary," ordering. This       *
 *      function sorts the edge set based on this ordering.                   *
 *  Arguments:                                                                *
 *      tmpl_Graph **G_ptr:                                                   *
 *          A pointer to a tmpl_Graph pointer. Given a tmpl_Graph pointer     *
 *          G, we can pass this to the function with &G.                      *
 *  Output:                                                                   *
 *      None (void)                                                           *
 ******************************************************************************/
TMPL_EXPORT extern void tmpl_Sort_Graph_Edges(tmpl_Graph **G);

extern tmpl_Graph *
tmpl_Create_Complete_Bipartite_Graph(unsigned long int m, unsigned long int n);

/******************************************************************************
 *  Function:                                                                 *
 *      tmpl_Create_Complete_Graph                                            *
 *  Purpose:                                                                  *
 *      Creates the complete graph on N vertices, K_N.                        *
 *  Arguments:                                                                *
 *      tmpl_uint32 N:                                                        *
 *          The number of vertices in the output graph.                       *
 *  Output:                                                                   *
 *      tmpl_Graph *G:                                                        *
 *          A pointer to a tmpl_Graph structure, the complete graph K_N.      *
 *  Warnings:                                                                 *
 *      This function uses malloc internally to allocate memory for the       *
 *      pointer that is returned. If malloc fails, this function will return  *
 *      NULL. It is the user's responsibility to check that malloc did not    *
 *      fail. Trying to access a NULL pointer may crash the program.          *
 ******************************************************************************/
extern tmpl_Graph *
tmpl_Create_Complete_Graph(unsigned long int N);

extern tmpl_Bool
tmpl_Is_Graph_Simple(tmpl_Graph *G);

extern unsigned long int
tmpl_Degree_of_Vertex(unsigned long int);

#endif
/*  End of include guard.                                                     */
