# Library source files
set(LITEGRAPH_SOURCES
    graph.cpp
    input.cpp
)

# Create library
add_library(litegraph ${LITEGRAPH_SOURCES})

# Set public include directory for the library
target_include_directories(litegraph PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

# Export the library for use in parent CMakeLists
set(LITEGRAPH_LIBRARY litegraph PARENT_SCOPE)
