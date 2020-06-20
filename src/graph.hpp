#include <vector>
#include <unordered_map>
#include "io.hpp"

/**
 * Directed edge which also holds capacity(weight) and flow.
 * To be used by MaxFlow.
 */
struct Edge
{
    int u, v;
    long capacity, flow;
    Edge(int u, int v, long c, long f = 0) : u(u), v(v), capacity(c), flow(f) {}
};

/**
 * Represents a graph by adj (adjacency list). Also holds other metadata.
 */
class Graph
{
public:
    int node_count; ///< Number of nodes in the input graph.
    int edge_count; ///< Number of edges in the input graph (including repetitions).
    int source; ///< Source vertex, if provided.
    int sink;   ///< Sink vertex, if provided.
    std::vector<std::vector<Edge*>> adj;    ///< Adjacency list representing the graph.
    std::unordered_map<std::string, int> compress;  ///< Coordinate compression map.
    std::vector<std::string> decompress;    ///< Coordinate decompression, inverse of #compress.
    void read(bool);
};