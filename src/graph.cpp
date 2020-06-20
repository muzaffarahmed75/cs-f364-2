#include "graph.hpp"

/**
 * Reads directed graph given as an edge list from STDIN.
 * Compresses the IDs of nodes to the range 0 to #node_count-1.
 * Constructs the adjacency list #adj isomorphic to the input graph.
 * @param[in] bipartite Specifies whether the graph to be read is weighted or
 * bipartite. Edges of bipartite graphs have weight 1.
 */
void Graph::read(bool bipartite)
{
    Input in;
    std::string su, sv, ssrc, ssnk;
    std::vector<std::tuple<int, int, long>> edges;
    while(in >> su >> sv)
    {
        int u, v;
        long w = 1;
        if(bipartite)
            sv += '#';
        else
            in >> w;
        if(compress.count(su))
            u = compress.at(su);
        else
            u = compress[su] = int(compress.size()), decompress.push_back(su);
        if(compress.count(sv))
            v = compress.at(sv);
        else
            v = compress[sv] = int(compress.size()), decompress.push_back(sv);
        edges.push_back({u, v, w});
    }
    node_count = int(compress.size());
    edge_count = int(edges.size());
    adj.resize(node_count+2);
    for(auto [u, v, w] : edges)
    {
        Edge* e = new Edge(u, v, w);
        adj.at(u).push_back(e);
        adj.at(v).push_back(e);
    }
}