#include <chrono>
#include "max_flow.hpp"
#include "io.hpp"

int main()
{
    Output out;
    MaxFlow maxflow;
    maxflow.read(false, true);
    clock_t t0 = clock();
    out <<   "Maximum flow:           " << maxflow.compute();
    out << "\nVertices in s-t cut:    " << maxflow.st_cut();
    clock_t t1 = clock();
    out << "\nRunning time (input):   " << int(1000 * t0 / CLOCKS_PER_SEC) << " ms";
    out << "\nRunning time (algo):    " << int(1000 * (t1 - t0) / CLOCKS_PER_SEC) << " ms\n";
    return 0;
}