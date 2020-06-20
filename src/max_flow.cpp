#include "max_flow.hpp"
#include <queue>
#include <algorithm>
#include <numeric>
#include <climits>

/**
 * Reads a directed graph into #g.
 * @see Graph::read
 * @param[in] bipartite Indicates whether the graph to be read is weighted or bipartite.
 * @param[in] sink_source Indicates whether the input has a sink and a source.
 */
void MaxFlow::read(bool bipartite, bool sink_source)
{
    Input in;
    std::string ssrc, ssnk;
    if(sink_source)
        in >> ssrc >> ssnk;
    g.read(bipartite);
    if(sink_source)
        g.source = g.compress.at(ssrc), g.sink = g.compress.at(ssnk);
}

/**
 * A utility BFS function for use by compute(). Finds a path from source to sink.
 * @param[in] ver Vertex to start the BFS from.
 */
std::vector<Edge*> MaxFlow::util_bfs(int ver)
{
    std::vector<bool> vis(g.node_count);
    std::queue<int> q;
    q.push(ver);
    std::vector<std::pair<int, Edge*>> parent(g.node_count, {-1, NULL});
    vis.at(ver) = true;
    while(q.size() and ver != g.sink)
    {
        ver = q.front(), q.pop();
        for(Edge* edge : g.adj.at(ver))
        {
            int u = edge -> u, v = edge -> v;
            long capacity = edge -> capacity, flow = edge -> flow;
            if(u == ver)
            {
                if(not vis.at(v) and flow < capacity)
                    vis.at(v) = true, q.push(v), parent.at(v) = {u, edge};
            }
            else
            {
                if(not vis.at(u) and flow > 0)
                    vis.at(u) = true, q.push(u), parent.at(u) = {v, edge};
            }
        }
    }
    std::vector<Edge*> path;
    if(q.empty() and ver != g.sink)
        return path;
    while(true)
    {
        vis.at(ver) = true;
        path.push_back(parent.at(ver).second);
        ver = parent.at(ver).first;
        if(ver == g.source)
            break;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

/**
 * Augments the given path.
 * @param[in] path Path to augment.
 * return Bottleneck of the path.
 */
long MaxFlow::augment(std::vector<Edge*>& path)
{
    int ver = g.source;
    long bottleneck = LONG_LONG_MAX;
    for(Edge* edge : path)
    {
        int u = edge -> u, v = edge -> v;
        long capacity = edge -> capacity, flow = edge -> flow;
        if(ver == u)
            bottleneck = std::min(bottleneck, capacity-flow), ver = v;
        else
            bottleneck = std::min(bottleneck, flow), ver = u;
    }
    ver = g.source;
    for(Edge* edge : path)
    {
        int u = edge -> u, v = edge -> v;
        long &capacity = edge -> capacity, &flow = edge -> flow;
        if(ver == u)
            flow += bottleneck, ver = v;
        else
            flow -= bottleneck, ver = u;
    }
    return bottleneck;
}

/**
 * Computes the maximum flow of the graph represented by #g using the
 * Ford-Fulkerson algorithm.
 * @return Maximum flow of the graph.
 */
long MaxFlow::compute()
{
    long maxflow = 0;
    while(true)
    {
        std::vector<Edge*> path = util_bfs(g.source);
        if(path.empty())
            break;
        long bottleneck = augment(path);
        if(bottleneck == 0)
            break;
        maxflow += bottleneck;
    }
    return maxflow;
}


/**
 * A utility DFS function for use by st_cut(). Visits all reachable vertices 
 * after the cut.
 * @param[in] u Vertex to start the BFS from.
 * @param[out] vis Vector of boolean values with visited nodes set as true.
 */
void MaxFlow::util_dfs(int u, std::vector<bool>& vis)
{
    vis.at(u) = true;
    for(Edge* edge : g.adj.at(u))
        if(not vis.at(edge -> v) and edge -> flow < edge -> capacity)
            util_dfs(edge -> v, vis);
}

/**
 * Computes the number of vertices reachable from source of the graph
 * represented by #g after a min s-t cut.
 * @return Number of vertices in the min s-t cut.
 */
int MaxFlow::st_cut()
{
    std::vector<bool> vis(g.node_count);
    util_dfs(g.source, vis);
    return std::accumulate(vis.begin(), vis.end(), 0);
}
