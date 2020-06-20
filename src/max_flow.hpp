#include "graph.hpp"

/**
 * Implements the Ford-Fulkerson algorithm to solve the maximum flow problem.
 */
class MaxFlow
{
    std::vector<Edge*> util_bfs(int);
    long augment(std::vector<Edge*>&);
    void util_dfs(int, std::vector<bool>&);
public:
    Graph g;    ///< Graph instance of which the maximum flow will be found.
    void read(bool, bool);
    long compute();
    int st_cut();
};