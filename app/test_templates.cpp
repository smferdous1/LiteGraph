#include <iostream>
#include "LiteGraph/graph.h"
#include "LiteGraph/input.h"

/**
 * Run template-instantiation checks for default and custom graph type aliases.
 *
 * @return Zero when all template construction checks complete successfully.
 */
int main() {
    // Test 1: Instantiate with default template parameters
    std::cout << "Test 1: Default graph types (float, unsigned int, unsigned int)" << std::endl;
    LiteGraph<> g1;
    std::cout << "  Created LiteGraph<> successfully" << std::endl;
    
    // Test 2: Instantiate with custom types
    std::cout << "\nTest 2: Custom graph types (double, uint32_t, uint64_t)" << std::endl;
    LiteGraph<double, uint32_t, uint64_t> g2;
    std::cout << "  Created LiteGraph<double, uint32_t, uint64_t> successfully" << std::endl;
    
    // Test 3: Bipartite graph with defaults
    std::cout << "\nTest 3: Default BptGraph types" << std::endl;
    BptGraph<> bp1;
    std::cout << "  Created BptGraph<> successfully" << std::endl;
    
    // Test 4: Bipartite graph with custom types
    std::cout << "\nTest 4: Custom BptGraph types" << std::endl;
    BptGraph<double, uint32_t, uint64_t> bp2;
    std::cout << "  Created BptGraph<double, uint32_t, uint64_t> successfully" << std::endl;
    
    // Test 5: GraphTypes struct
    std::cout << "\nTest 5: GraphTypes struct" << std::endl;
    using DefaultTypes = GraphTypes<>;
    std::cout << "  GraphTypes struct instantiated successfully" << std::endl;
    
    // Test 6: Constructor with parameters
    std::cout << "\nTest 6: Graph with size parameters" << std::endl;
    LiteGraph<float, unsigned int, unsigned int> g3(100, 500);
    std::cout << "  Created LiteGraph with n=100, m=500" << std::endl;
    std::cout << "  numberOfNodes() = " << g3.numberOfNodes() << std::endl;
    std::cout << "  numberOfEdges() = " << g3.numberOfEdges() << std::endl;
    
    std::cout << "\n✓ All template instantiation tests passed!" << std::endl;
    
    return 0;
}
