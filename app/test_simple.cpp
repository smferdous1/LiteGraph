#include <iostream>
#include "LiteGraph/graph.h"
#include "LiteGraph/input.h"

/**
 * Run smoke tests for default and explicitly typed LiteGraph construction.
 *
 * @return Zero when all construction checks complete, or one if an exception is caught.
 */
int main() {
    try {
        // Test 1: Simple instantiation
        std::cout << "Test 1: Attempting to create default graph..." << std::endl;
        {
            LiteGraph<> g1;
            std::cout << "  ✓ Created LiteGraph<> successfully" << std::endl;
        }
        
        // Test 2: Create with size (this calls the constructor with parameters)
        std::cout << "\nTest 2: Creating graph with explicit size..." << std::endl;
        {
            LiteGraph<float, unsigned int, unsigned int> g3(10, 20);
            std::cout << "  Graph created with n=" << g3.numberOfNodes() << ", m=" << g3.numberOfEdges() << std::endl;
            std::cout << "  ✓ Constructor with parameters works" << std::endl;
        }
        
        // Test 3: Test with custom types
        std::cout << "\nTest 3: Testing custom types..." << std::endl;
        {
            LiteGraph<double, uint32_t, uint64_t> g2;
            std::cout << "  ✓ Created LiteGraph<double, uint32_t, uint64_t>" << std::endl;
        }
        
        std::cout << "\n✓ All tests completed successfully!" << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
        return 1;
    }
}
