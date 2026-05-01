#include <iostream>
#include "LiteGraph/graph.h"
#include "LiteGraph/input.h"

/**
 * Read a bipartite graph file passed on the command line and print its CSR entries.
 *
 * @param argc Number of command-line arguments.
 * @param argv Command-line arguments; argv[1] must be a .mtx graph path.
 * @return Zero when the graph is loaded and printed, or one for invalid usage.
 */
int main(int argc, char **argv)
{
    if(argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <bptgraph.mtx>" << std::endl;
        return 1;
    }

    Input input;
    BptGraph<> graph;

    input.readMtxBpt(argv[1], graph);
    graph.printGraph();

    return 0;
}
