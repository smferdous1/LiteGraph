#include<iostream>
#include<fstream>
#include<cstdlib>
#include<math.h>
#include<vector>

#include "input.h"

#define DEBUG 1

//If the given file is not of a specific extension return false
bool static fileTypeCheck(std::string fn, std::string extension)
{
    if(fn.substr(fn.find_last_of(".") + 1) == extension) {
        return true;
    } else {
        return false;
    }
}

//General graph read. Graph can be either in mtx format or binary format
void Input::readGraphGen(std::string fileName, LightGraph &G,int is_random,long seed, VAL_T minW, VAL_T maxW)
{
    if(fileTypeCheck(fileName,"mtx")==true)
    {
        readMtx(fileName,G,is_random,seed,minW,maxW);
    }
    else if(fileTypeCheck(fileName,"bin") == true)
    {
        readBinGen(fileName,G);
    }
    else
    {
        std::cout<<"file must be either mtx or bin."<<std::endl;
        std::exit(1);
    }
}

// main workhorse of mtx symmetric graph reading.
void Input::readMtx(std::string fileName, LightGraph &G,bool is_random,long seed, VAL_T minW, VAL_T maxW)
{
    srand(seed);
    std::ifstream fileread(fileName.c_str());
    if(fileread.is_open()==false)
    {
        std::cout << "No file named "<<fileName<<std::endl;
        std::exit(1);
    }
    
    //Read the mtx header to determine file type 
    std::string header[6];
    fileread>>header[0]>>header[1]>>header[2]>>header[3]>>header[4];

    weightType = header[3];
    fileread.seekg(0, std::ios::beg); 
    //Ignore header and comments
    while (fileread.peek() == '%') fileread.ignore(2048, '\n');

    NODE_T nrow,ncol;
    EDGE_T nnz;
    fileread >> nrow >> ncol >> nnz;
    std::vector<std::vector<NODE_T> > adjList(nrow);
    std::vector<std::vector<VAL_T> > adjWeight(nrow);

    NODE_T u;
    NODE_T v;
    VAL_T weight;
    EDGE_T nEdge = 0;
    for(EDGE_T i=0;i<nnz;i++)
    {
        weight = 1.0;
        if(weightType.compare("pattern") != 0)
            fileread >> v >> u >> weight;
        else
            fileread >> v >> u;
        v--;
        u--;
        if(u<v && weight>0)
        {
            if(is_random==1)
            {
                weight =  minW + ((maxW-minW)*((double)rand()/(RAND_MAX)));
            }
            //std::cout<<weight<<std::endl;
            adjList[u].push_back(v);
            adjWeight[u].push_back(weight);

            //reverse edge
            adjList[v].push_back(u);
            adjWeight[v].push_back(weight);
            nEdge++;
        }
    }
    G.setNumberEdges(nEdge);
    G.setNumberNodes(nrow);

    G.A = new VAL_T[2*nEdge+5];
    G.IA = new NODE_T[nrow+5];
    G.JA = new NODE_T[2*nEdge];

    //second pass. Build the three arrays
    G.IA[0] = 0;
    EDGE_T k=0;
    for(NODE_T i=0;i<nrow;i++)
    {
        for(NODE_T j=0;j<adjList[i].size();j++)
        {

            G.A[k] = adjWeight[i][j];
            G.JA[k] = adjList[i][j];
            k++;
        }
        G.IA[i+1]= G.IA[i] + adjList[i].size();
    }

    //delete the vectors
    for(NODE_T i=0;i<nrow;i++) 
    {
        adjList[i].clear();
        std::vector<NODE_T>().swap(adjList[i]);

        adjWeight[i].clear();
        std::vector<VAL_T>().swap(adjWeight[i]);

    }

}

//read non-symmetric graph
void Input::readMtxBpt(std::string fileName, BptGraph &G,int is_random,long seed, VAL_T minW, VAL_T maxW)
{
    srand(seed);
    std::ifstream fileread(fileName.c_str());
    if(fileread.is_open()==false)
    {
        std::cout << "No file named "<<fileName<<std::endl;
        std::exit(1);
    }
    //Ignore header and comments
    while (fileread.peek() == '%') fileread.ignore(2048, '\n');

    NODE_T nrow,ncol;
    EDGE_T nnz;
    fileread >> nrow >> ncol >> nnz;
    if(DEBUG==1)
    {
        std::cout<<nrow<<" "<<ncol<<" "<<nnz<<std::endl;
    }

    //std::vector<NODE_T> adjList[nrow];
    //std::vector<VAL_T> adjWeight[nrow];
    std::vector<std::vector<NODE_T> > adjList(nrow);
    std::vector<std::vector<VAL_T> > adjWeight(nrow);

    NODE_T u;
    NODE_T v;
    VAL_T weight;
    EDGE_T nEdge = 0;
    for(EDGE_T i=0;i<nnz;i++)
    {
        fileread >> u >> v >> weight;
        //fileread >> u >> v;
        //weight = 1.0;
        v--;
        u--;
        if(DEBUG==2)
        {
            std::cout<<u<<" "<<v<<" "<<weight<<std::endl;
        }
        if(weight>0)
        {
            if(is_random==1)
            {
                weight =  minW + (int)((maxW-minW)*((double)rand()/(RAND_MAX)));
            }
            //std::cout<<weight<<std::endl;
            adjList[u].push_back(v);
            adjWeight[u].push_back(weight);
            nEdge++;
        }
    }
    G.setNumberEdges(nEdge);
    G.setNumberNodes(nrow,ncol);

    G.A = new VAL_T[nEdge+5];
    G.IA = new NODE_T[nrow+5];
    G.JA = new NODE_T[nEdge];

    //second pass. Build the three arrays
    G.IA[0] = 0;
    EDGE_T k=0;
    for(NODE_T i=0;i<nrow;i++)
    {
        for(NODE_T j=0;j<adjList[i].size();j++)
        {

            G.A[k] = adjWeight[i][j];
            G.JA[k] = adjList[i][j];
            k++;
        }
        G.IA[i+1]= G.IA[i] + adjList[i].size();
    }

    //delete the vectors
    for(NODE_T i=0;i<nrow;i++) 
    {
        adjList[i].clear();
        std::vector<NODE_T>().swap(adjList[i]);

        adjWeight[i].clear();
        std::vector<VAL_T>().swap(adjWeight[i]);

    }

}

void Input::readBinGen(std::string fileName, LightGraph &G)
{
    std::ifstream inf;
    NODE_T nA,nB;
    EDGE_T m;
    inf.open(fileName.c_str(),std::ios::in|std::ios::binary);
    if(inf.is_open()!=1) {
        std::cout<<"Can not open file "<<fileName<<std::endl;
        exit(1);                                
    }
    inf.read((char*)&nA, sizeof(NODE_T));
    inf.read((char*)&nB, sizeof(NODE_T));
    inf.read((char*)&m, sizeof(EDGE_T));
    //of.write((char*)&max, sizeof(unsigned int));

    G.A = new VAL_T[2*m];
    G.IA = new NODE_T[nA+1];
    G.JA = new NODE_T[2*m];

    G.setNumberEdges(m);
    G.setNumberNodes(nA);

    inf.read((char*)&G.IA[0], sizeof(NODE_T) * (nA+1));
    inf.read((char*)&G.JA[0], sizeof(NODE_T) * 2*m);
    inf.read((char*)&G.A[0], sizeof(VAL_T) * 2*m);
    inf.close();

}

void Input::wrtBinGen(std::string fileName, LightGraph &G)
{
    std::ofstream of;
    NODE_T nA = G.numberOfNodes();
    EDGE_T m = G.numberOfEdges();

    of.open(fileName.c_str(),std::ios::out|std::ios::binary);
    if(of.is_open()!=1) {
        std::cout<<"Can not open file "<<fileName<<std::endl;
        exit(1);                                
    }

    of.write((char*)&nA, sizeof(NODE_T));
    of.write((char*)&nA, sizeof(NODE_T));
    of.write((char*)&m, sizeof(EDGE_T));
    //of.write((char*)&max, sizeof(unsigned int));
    of.write((char*)&G.IA[0], sizeof(NODE_T) * (nA+1));
    of.write((char*)&G.JA[0], sizeof(NODE_T) *2*m);
    of.write((char*)&G.A[0], sizeof(VAL_T) * 2*m);
    of.close();

}
void Input::readBinBpt(std::string fileName, BptGraph &G)
{
    std::ifstream inf;
    NODE_T nA,nB;
    EDGE_T m;
    inf.open(fileName.c_str(),std::ios::in|std::ios::binary);
    if(inf.is_open()!=1) {
        std::cout<<"Can not open file "<<fileName<<std::endl;
        exit(1);                                
    }

    inf.read((char*)&nA, sizeof(NODE_T));
    inf.read((char*)&nB, sizeof(NODE_T));
    inf.read((char*)&m, sizeof(EDGE_T));
    //of.write((char*)&max, sizeof(unsigned int));

    G.A = new VAL_T[m];
    G.IA = new NODE_T[nA+1];
    G.JA = new NODE_T[m];

    G.setNumberEdges(m);
    G.setNumberNodes(nA,nB);

    inf.read((char*)&G.IA[0], sizeof(NODE_T) * (nA+1));
    inf.read((char*)&G.JA[0], sizeof(NODE_T) * m);
    inf.read((char*)&G.A[0], sizeof(VAL_T) * m);
    inf.close();

}

void Input::wrtBinBpt(std::string fileName, BptGraph &G)
{
    std::ofstream of;
    NODE_T nA = G.numberOfNodesA();
    NODE_T nB = G.numberOfNodesB();
    EDGE_T m = G.numberOfEdges();

    of.open(fileName.c_str(),std::ios::out|std::ios::binary);
    of.open(fileName.c_str(),std::ios::out|std::ios::binary);
    if(of.is_open()!=1) {
        std::cout<<"Can not open file "<<fileName<<std::endl;
        exit(1);                                
    }
    of.write((char*)&nA, sizeof(NODE_T));
    of.write((char*)&nB, sizeof(NODE_T));
    of.write((char*)&m, sizeof(EDGE_T));
    //of.write((char*)&max, sizeof(unsigned int));
    of.write((char*)&G.IA[0], sizeof(NODE_T) * (nA+1));
    of.write((char*)&G.JA[0], sizeof(NODE_T) * m);
    of.write((char*)&G.A[0], sizeof(VAL_T) * m);
    of.close();

}

