#include <iostream>
#include "graph.h"

/*This function create an edgeList out of the graph. Remember 
 * the G.A,G.IA and G.JA must be set earlier */

void LightGraph::createEdgeList(WeightEdgeSimList &outList)
{
    //clearing the edgelist. EdgeList is given as a pointer
    //remember you have to give a preallocated address here. 
    outList.clear();

    //scan through the three arrays
    for(NODE_T i=0;i<n;i++)
    {
        for(NODE_T j=IA[i];j<IA[i+1];j++)
        {
            if(i<JA[j])
            {
                WeightEdgeSim we = {i,JA[j],A[j]};
                outList.push_back(we);
            }
        }
    }
}
void LightGraph::createEdgeList(SimEdgeList &outList)
{
    //clearing the edgelist. EdgeList is given as a pointer
    //remember you have to give a preallocated address here. 
    outList.clear();

    EDGE_T count = 0;
    //scan through the three arrays
    for(NODE_T i=0;i<n;i++)
    {
        for(NODE_T j=IA[i];j<IA[i+1];j++)
        {
            if(i<JA[j])
            {
                SimEdge  se = {i,j};
                outList.push_back(se);
            }
        }
    }
}

void LightGraph::createRefArray(bool is_invRef)
{
    RA = new EDGE_T[2*m];
    if(is_invRef) invRA = new EDGE_T[2*m];

    for(NODE_T i=0;i<n;i++)
    {
        for(NODE_T j=IA[i];j<IA[i+1];j++)
        {
            if(i<JA[j])
            {
                RA[j] = j;
                for(NODE_T jj=IA[JA[j]];jj<IA[JA[j]+1];jj++)
                {
                    if(JA[jj]==i)
                    {
                        RA[jj] = j;
                        if(is_invRef) 
                        {
                            invRA[j] = jj;
                            invRA[jj] = jj;
                        }
                    }
                }
            }
        }
    }

}
void LightGraph::printGraph(NODE_T offset)
{
    for(NODE_T i=0;i<n;i++)
    {
        for(NODE_T j=IA[i];j<IA[i+1];j++)
        {
            std::cout<<i+offset<<" "<<JA[j]<<" "<<A[j]<<std::endl; 
        }
    }
}
void BptGraph::printGraph()
{
    std::cout<<nA<<" "<<nB<<" "<<m<<std::endl;
    for(NODE_T i=0;i<nA;i++)
    {
        for(NODE_T j=IA[i];j<IA[i+1];j++)
        {
            std::cout<<i<<" "<<JA[j]<<" "<<A[j]<<std::endl; 
        }
    }
}
void LightGraph::printGraph()
{
    for(NODE_T i=0;i<n;i++)
    {
        for(NODE_T j=IA[i];j<IA[i+1];j++)
        {
            std::cout<<i<<" "<<JA[j]<<" "<<A[j]<<std::endl; 
        }
    }
}

void BptGraph::sortGraph()
{
    std::vector<std::pair<NODE_T,VAL_T> > sortInd;
    for (NODE_T i=0;i<nA;i++)
    {
        sortInd.resize(IA[i+1] - IA[i]);
        sortInd.shrink_to_fit();
        NODE_T count = 0;
        for(NODE_T j=IA[i];j<IA[i+1];j++)
        {
            sortInd[count] = std::make_pair(JA[j],A[j]);
            count++;
        }
        std::sort(sortInd.begin(),sortInd.end());
        count  = 0;
        for(NODE_T j=IA[i];j<IA[i+1];j++)
        {
            JA[j] = sortInd[count].first;
            A[j] = sortInd[count].second;
            count++;
        }
    }

}

void LightGraph::sortGraph()
{
    std::vector<std::pair<NODE_T,VAL_T> > sortInd;
    for (NODE_T i=0;i<n;i++)
    {
        sortInd.resize(IA[i+1] - IA[i]);
        sortInd.shrink_to_fit();
        for(NODE_T j=IA[i];j<IA[i+1];j++)
        {
            sortInd[count] = std::make_pair(JA[j],A[j]);
        }
        std::sort(sortInd.begin(),sortInd.end());
        for(NODE_T j=IA[i];j<IA[i+1];j++)
        {
            JA[j] = sortInd[count].first;
            A[j] = sortInd[count].second;
        }
    }

}

