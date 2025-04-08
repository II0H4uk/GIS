#include "pch.h"
#include "BruteForce.h"

std::vector<std::vector<int>> applyPermutation(std::vector<std::vector<int>> adjList, std::vector<int> perm);
bool isEqual(std::vector<std::vector<int>> adjList1,std::vector<std::vector<int>> adjList2);
namespace GIS_Algs {

    bool BruteForce::Start(const GIS_Data::Graph& graph1,const GIS_Data::Graph& graph2) {
        std::vector<std::vector<int>> adjList1,adjList2;
        std::vector<int> perm;
        adjList1=graph1.GetAdjList();
        adjList2=graph2.GetAdjList();
        for(int i=0;i<adjList1.size();i++){
            perm.push_back(i);
        }
        do {
            if(isEqual(applyPermutation(adjList1,perm),adjList2)){
                return true;
            }
        }while(std::next_permutation(perm.begin(), perm.end()));

        return false;
    }
}
std::vector<std::vector<int>> applyPermutation(std::vector<std::vector<int>> adjList, std::vector<int> perm) {
    std::vector<std::vector<int>> adjList2;
    for(int i=0;i<adjList.size();i++){
        std::vector<int> temp;
        int ti=-1; 
        for(int j=0;ti==-1&&j<perm.size();j++){
            if(i==perm[j]) ti=j;
        }
        for(int j=0;j<adjList[ti].size();j++){
            temp.push_back(perm[adjList[ti][j]]);
        }
        adjList2.push_back(temp);
    }
    return adjList2;
}
bool isEqual(std::vector<std::vector<int>> adjList1,std::vector<std::vector<int>> adjList2){
    if (adjList1.size()!=adjList2.size()) return false;
    for(int i=0;i<adjList1.size();i++){
        if(adjList1[i].size()!=adjList2[i].size())return false;
        for(int j=0;j<adjList1[i].size();j++){
            if(adjList1[i][j]!=adjList2[i][j])return false;
        }
    }
    return true;
}
