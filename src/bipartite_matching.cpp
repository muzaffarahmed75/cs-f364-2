#include "bipartite_matching.hpp"

/**
 * Reads a bipartite graph into #maxflow.
 * @see Graph::read
 */
void BipartiteMatching::read()
{
    maxflow.read(true, false);
}

/**
 * Computes the size of the maximum bipartite matching of the graph represented by
 * maxflow.g by converting it to a Maximum Flow problem.
 * @return Size of the maximum bipartite matching of the graph.
 */
int BipartiteMatching::compute()
{
    Output out;
    int n = maxflow.g.node_count;
    maxflow.g.source = n;
    maxflow.g.sink = n+1;
    std::vector<bool> set1(n), set2(n);
    for(int u = 0; u < n; ++u)
        for(Edge* edge : maxflow.g.adj.at(u))
            set1[edge -> u] = true, set2[edge -> v] = true;
    for(int i = 0; i < n; ++i)
    {
        int u, v;
        if(set1[i])
            u = maxflow.g.source, v = i;
        if(set2[i])
            u = i, v = maxflow.g.sink;
        Edge* e = new Edge(u, v, 1);
        maxflow.g.adj.at(u).push_back(e);
        maxflow.g.adj.at(v).push_back(e);
    }
    maxflow.g.node_count += 2;
    return (int) maxflow.compute();
}
