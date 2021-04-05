
#include <libtmpl/include/tmpl_integer.h>
#include <libtmpl/include/tmpl_graph_theory.h>
#include <stdlib.h>

tmpl_Graph * tmpl_Create_Complete_Graph(tmpl_uint32 N)
{
    tmpl_Graph *G;
    tmpl_uint32 k0, k1;
    tmpl_uint64 current_edge;
    tmpl_GraphEdge *E;

    G = malloc(sizeof(*G));
    G->vertex_number = N;
    G->edge_number   = N * (N + 1U) / 2U;

    G->edges = malloc(sizeof(*(G->edges)) * G->edge_number);
    E = G->edges;

    current_edge = 0UL;
    for (k1 = 1U; k1 < N; ++k1)
    {
        for (k0 = 0U; k0 < k1; ++k0)
        {
            E[current_edge].v0 = k0;
            E[current_edge].v1 = k1;
            E[current_edge].multiplicity = 1U;
            E[current_edge].dirs = NULL;
            E[current_edge].weights = NULL;
            E[current_edge].signs = NULL;
            current_edge++;
        }
    }

    return G;
}

