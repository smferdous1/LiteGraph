#pragma once

#include <string>
#include "graph.h"

class Input
{
  std::string fileName;
  std::string weightType; //this could be pattern(unweighted) or real(weighted)

  public:
      void readMtx(std::string ,LightGraph& ,bool=false, long=0,VAL_T=0,VAL_T=0);
      void readMtxBpt(std::string ,BptGraph& ,int=0, long int=0,VAL_T=0,VAL_T=0);
      void readGraphGen(std::string ,LightGraph& ,int=0, long int=0,VAL_T=0,VAL_T=0);
      
      void readBinBpt(std::string , BptGraph &);
      void wrtBinBpt(std::string , BptGraph &);
      void readBinGen(std::string , LightGraph &);
      void wrtBinGen(std::string , LightGraph &);
      Input()
      {
      
      }
      
      Input(std::string givenFile)
      {
        fileName = givenFile;
      }
};


