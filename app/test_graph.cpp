#include <iostream>
#include "LiteGraph/graph.h"
#include "LiteGraph/input.h"

/**
 * Read a graph file passed on the command line and print its CSR entries.
 *
 * @param argc Number of command-line arguments.
 * @param argv Command-line arguments; argv[1] must be a .mtx or .bin graph path.
 * @return Zero when the graph is loaded and printed, or one for invalid usage.
 */
int main(int argc, char **argv)
{
    if(argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << " <graph.mtx|graph.bin>" << std::endl;
        return 1;
    }

    Input input;
    LiteGraph<> graph;

    input.readGraphGen(argv[1], graph);
    graph.printGraph();

    return 0;
}
