# LiteGraph

LiteGraph is a small C++11 graph library for storing weighted graphs in compressed sparse row (CSR) format. It provides a general undirected graph type, a bipartite graph type, helpers for reading Matrix Market files, and binary read/write utilities for faster reloads.

The library is templated, so callers can choose the value, node-id, and edge-count types used by a graph:

```cpp
LightGraph<> graph;                                  // float, unsigned int, unsigned int
LightGraph<double, uint32_t, uint64_t> largeGraph;   // custom types
BptGraph<double, uint32_t, uint64_t> bipartiteGraph;
```

## Repository Layout

```text
include/LightGraph/
  graph.h        Graph data structures and CSR utilities
  input.h        Matrix Market and binary graph I/O

src/
  graph.cpp      Library translation unit
  input.cpp      Library translation unit

app/
  test_simple.cpp
  test_templates.cpp
  test_graph.cpp
  test_bpt_graph.cpp

data/
  graph.mtx       Sample weighted undirected graph
  bptgraph.mtx    Sample weighted bipartite graph

CMakeLists.txt   Top-level CMake project
```

Most implementation lives in the headers because the main APIs are templates.

## Graph Types

`LightGraph<VAL_T, NODE_T, EDGE_T>` stores a general graph as symmetric CSR arrays:

- `A`: edge weights
- `IA`: row offsets
- `JA`: adjacent vertex ids
- `RA`: optional reference array for symmetric edge entries
- `invRA`: optional inverse reference array

`BptGraph<VAL_T, NODE_T, EDGE_T>` stores a bipartite graph in CSR form with row-side and column-side node counts.

## Build

From the repository root:

```sh
cmake -S . -B build
cmake --build build
```

This builds the `litegraph` static library and the example test executables in `build/app/`.

## Run Examples

```sh
./build/app/test_simple
./build/app/test_templates
./build/app/test_graph data/graph.mtx
./build/app/test_bpt_graph data/bptgraph.mtx
```

`test_graph` reads a general `.mtx` or `.bin` graph and prints graph metadata plus CSR entries. `test_bpt_graph` reads a bipartite `.mtx` graph and prints row/column vertex counts, edge count, and CSR entries.

## Basic Usage

```cpp
#include "LightGraph/graph.h"
#include "LightGraph/input.h"

int main()
{
    LightGraph<> graph;
    Input input;

    input.readGraphGen("data/graph.mtx", graph);

    graph.sortGraph();
    graph.printGraph();

    return 0;
}
```

To construct a graph manually with allocated CSR storage:

```cpp
LightGraph<float, unsigned int, unsigned int> graph(10, 20);

graph.setNumberNodes(10);
graph.setNumberEdges(20);
```

The sized `LightGraph` constructor allocates storage for an undirected graph, using `2 * m` entries for symmetric CSR adjacency.

## Reading Matrix Market Files

General graphs can be read from `.mtx` files:

```cpp
LightGraph<> graph;
Input input;

input.readMtx("data/graph.mtx", graph);
```

Bipartite graphs can be read with:

```cpp
BptGraph<> graph;
Input input;

input.readMtxBpt("data/bptgraph.mtx", graph);
```

The Matrix Market readers ignore non-positive weights. For general graphs, only one triangular direction is accepted from the file and the reverse edge is added automatically.

Random weights can be generated while reading:

```cpp
input.readMtx("data/graph.mtx", graph, true, 1234, 0.1f, 1.0f);
```

## Binary I/O

LiteGraph can write and read its own binary CSR format:

```cpp
Input input;
LightGraph<> graph;

input.readGraphGen("data/graph.mtx", graph);
input.wrtBinGen("graph.bin", graph);

LightGraph<> reloaded;
input.readBinGen("graph.bin", reloaded);
```

For bipartite graphs:

```cpp
BptGraph<> graph;

input.readMtxBpt("data/bptgraph.mtx", graph);
input.wrtBinBpt("bipartite.bin", graph);
```

## Utility Operations

`LightGraph` supports:

- `numberOfNodes()` and `numberOfEdges()`
- `sortGraph()` to sort each CSR row by adjacent vertex id
- `printGraph()` to print graph metadata and CSR entries
- `createEdgeList(...)` to create weighted or compact edge lists
- `createRefArray(...)` to build references between symmetric CSR entries

`BptGraph` supports:

- `numberOfNodesA()` and `numberOfNodesB()`
- `numberOfEdges()`
- `sortGraph()`
- `printGraph()` to print bipartite graph metadata and CSR entries

## Use From Another CMake Project

The easiest way to use LiteGraph in another C++ project is to add this repository as a subdirectory:

```text
MyProject/
  CMakeLists.txt
  main.cpp
  external/
    LiteGraph/
```

Then in `MyProject/CMakeLists.txt`:

```cmake
cmake_minimum_required(VERSION 3.10)
project(MyProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(external/LiteGraph)

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE litegraph)
```

In C++ code, include the public headers:

```cpp
#include "LightGraph/graph.h"
#include "LightGraph/input.h"
```

## Requirements

- CMake 3.10 or newer
- A C++11-compatible compiler
