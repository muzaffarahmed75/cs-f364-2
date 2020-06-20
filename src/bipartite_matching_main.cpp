#include <chrono>
#include "bipartite_matching.hpp"

int main()
{
    Output out;
    BipartiteMatching bipartite_matching;
    bipartite_matching.read();
    clock_t t0 = clock();
    out <<   "Maximum size of bipartite matching: " << bipartite_matching.compute();
    clock_t t1 = clock();
    out << "\nRunning time (input):               " << int(1000 * t0 / CLOCKS_PER_SEC) << " ms";
    out << "\nRunning time (algo):                " << int(1000 * (t1 - t0) / CLOCKS_PER_SEC) << " ms\n";
    return 0;
}