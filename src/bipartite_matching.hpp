#include "max_flow.hpp"
#include <vector>

/**
 * Implements a solution to the Maximum Bipartite Matching problem which converts
 * it into a maxmimum flow problem.
 */
class BipartiteMatching
{
    MaxFlow maxflow;    ///< MaxFlow instance which stores the modified bipartite graph.
public:
    void read();
    int compute();
};
