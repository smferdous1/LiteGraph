# Get the library from src
set(LITEGRAPH_LIBRARY litegraph)

# Test executable 1: test_simple
add_executable(test_simple test_simple.cpp)
target_include_directories(test_simple PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)
target_link_libraries(test_simple ${LITEGRAPH_LIBRARY})

# Test executable 2: test_templates
add_executable(test_templates test_templates.cpp)
target_include_directories(test_templates PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)
target_link_libraries(test_templates ${LITEGRAPH_LIBRARY})

# Enable testing
enable_testing()
add_test(NAME simple_test COMMAND test_simple)
add_test(NAME template_test COMMAND test_templates)
