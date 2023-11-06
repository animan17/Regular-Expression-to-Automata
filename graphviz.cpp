#include "graphviz.h"

void AdjLitoDo(map<int,multimap<char,int>> &adjLi, string dotName){
    int vertex;

    ofstream dotFile;
    dotFile.open("..\\"+dotName+".dot");

    if(!dotFile.is_open())
    {
        cout<<"Error opening DOT file for writing."<<endl;
        return;
    }

    dotFile<< "digraph G {rankdir=\"LR\";"<<endl;

    for(const auto& pair:adjLi) {
        int vert1=pair.first;
        multimap<char, int> innerMultiMap=pair.second;
        for(const auto& innerPair : innerMultiMap) {
            char trans= innerPair.first;
            int vert2= innerPair.second;
            dotFile<<"  "<<vert1<<" -> "<<vert2<<" [label=\""<<trans<<"\"];"<<endl;
        }
    }
    dotFile<<"}"<<endl;
    dotFile.close();
}


int drawGraph(map<int,multimap<char,int>> &adjList, string dotName)
{
    remove(("..\\"+dotName+".dot").c_str());
    AdjLitoDo(adjList, dotName);
    system(("..\\windows_10_msbuild_Release_graphviz-9.0.0-win32\\Graphviz\\bin\\dot -Tpng ..\\"+dotName+".dot -o ..\\"+dotName+".png").c_str());
    return 0;        
}