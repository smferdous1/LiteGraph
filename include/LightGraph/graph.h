#pragma once

#include<vector>
#include<algorithm>

//user-defined types. 
//
//Change this to float/double if the weight of the graph is real  
typedef float VAL_T;
//Change this to long if number of nodes does not fit into integer
typedef  unsigned int NODE_T;
//Change this to long if number of edges does not fit into integer
typedef  unsigned int EDGE_T;

//Type of the sum of the weight of the edges
typedef double SUM_T;

// An edge
struct Edge
{
    NODE_T u;
    NODE_T v;
};

// weighted edge
struct WeightEdgeSim
{

    NODE_T u;
    NODE_T v;
    VAL_T weight;
};

struct RefEdge
{
    WeightEdgeSim we;
    EDGE_T ref;
};

//This is the simplest and most memory efficient version of an edge.
//If we know the five array: IA,JA,A, RA,invRA: to retrive a specific information efficiently these two entities are sufficient.
struct SimEdge
{
    NODE_T u;
    EDGE_T index;
};

//adjacent edge
struct Adj
{
    //adjacent vertex id
    NODE_T adjV;
    VAL_T adjW;
    Adj(){}
    Adj(NODE_T adjVa,VAL_T adjWa)
        :adjV(adjVa),adjW(adjWa){}
    bool operator==(const Adj& adj) const
    { 
        return (this->adjV == adj.adjV); 
    } 
    bool operator<(const Adj& adj) const
    { 
        return (this->adjV < adj.adjV); 
    } 
};
// user-defined type to hold the edge related structures.
typedef std::vector<Edge> EdgeList;
//typedef std::vector<WeightEdge> WeightEdgeList;
typedef std::vector<WeightEdgeSim> WeightEdgeSimList;
typedef std::vector<SimEdge> SimEdgeList;
typedef std::vector<VAL_T> WeightList;

typedef struct Adj Adjacent;

class LightGraph
{

    //number of nodes in the graph
    NODE_T n; 
    //number of row nodes if the graph is bpt but read as non-bpt
    NODE_T nRow;
    NODE_T nCol;
    //number of edges in the graph
    EDGE_T m;

    //Avoid double free of the pointers
    bool is_destroyed;

    public:  
    //default constructor
    LightGraph()
    {
        A = 0;
        IA = 0;
        JA = 0;
        RA = 0;
        invRA = 0;
        is_destroyed = false;
    }

    //constructor
    LightGraph(NODE_T n1, EDGE_T m1)
    {
        n = n1;
        m = m1;
        is_destroyed = false;

        //allocate memory for A,IA and JA
        //graph is recorded as a symmetric matrix. thats why we need 2*m entries.
        A = new VAL_T[2*m];
        IA = new NODE_T[n+1];
        JA = new NODE_T[2*m];
        //RA is a reference array. Given a undirected graph as an edgeList, it creates the references needed to go back and forth to the three arrays and edgeList.
        RA = new EDGE_T[2*m];
    }
    //delete the graph
    ~LightGraph()
    {
        if(is_destroyed == false)
        {
            n = 0;
            m = 0;
            is_destroyed=true;
            if(A!=0) delete []A;
            if(IA!=0) delete []IA;
            if(JA!=0)delete []JA;
            if(RA != 0) delete []RA;
            if(invRA != 0) delete []invRA;
        }
    }


    //Graph is always in CSR format
    VAL_T *A;
    NODE_T *IA;
    NODE_T *JA;
    EDGE_T *RA;
    EDGE_T *invRA;

    void setNumberEdges(EDGE_T m1)
    {
        m = m1;
    }
    EDGE_T numberOfEdges()
    {
        return m;
    }

    void setNumberNodes(NODE_T n1)
    {
        n = n1;
    }
    NODE_T numberOfNodes()
    {
        return n;
    }

    void setNumberNodesRow(NODE_T n1)
    {
        nRow = n1;
    }
    NODE_T numberOfNodesRow()
    {
        return nRow;
    }
    void setNumberNodesCol(NODE_T n1)
    {
        nCol = n1;
    }
    NODE_T numberOfNodesCol()
    {
        return nCol;
    }

    void createEdgeList(WeightEdgeSimList &);
    void createEdgeList(SimEdgeList &);
    void printGraph();
    void printGraph(NODE_T);
    void createRefArray(bool=false);
    void sortGraph();

};

class BptGraph
{
    //number of nodes in the graph
    NODE_T nA;
    NODE_T nB;
    //number of edges in the graph
    EDGE_T m;
    bool is_destroyed;

    public:  
    //default constructor
    BptGraph()
    {
        A= 0;
        IA = 0;
        JA = 0;
        is_destroyed = false;
    }
    //constructor
    BptGraph(NODE_T n1, NODE_T n2, EDGE_T m1)
    {
        nA = n1;
        nB = n2;
        m = m1;
        is_destroyed = false;

        //allocate memory for A,IA and JA
        A = new VAL_T[m+5];
        IA = new NODE_T[nA+5];
        JA = new NODE_T[m];
    }
    //delete the graph
    ~BptGraph()
    {
        if(is_destroyed == false)
        {
            nA = 0;
            nB = 0;
            m = 0;
            is_destroyed=true;
            if(A!=0) delete []A;
            if(IA!=0) delete []IA;
            if(JA!=0)delete []JA;
        }
    }

    //Graph is always in CSR format
    VAL_T *A;
    NODE_T *IA;
    NODE_T *JA;

    void setNumberEdges(EDGE_T m1)
    {
        m = m1;
    }
    EDGE_T numberOfEdges()
    {
        return m;
    }

    void setNumberNodes(NODE_T n1,NODE_T n2)
    {
        nA = n1;
        nB = n2;
    }
    NODE_T numberOfNodesA()
    {
        return nA;
    }

    NODE_T numberOfNodesB()
    {
        return nB;
    }
    void printGraph();
    void sortGraph();
};

