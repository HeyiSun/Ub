#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <queue>

using namespace std;
class Solution {
    private:
   	vector<int> m_outputDistances;
    unordered_map<int, vector<int> > graph;
    int start_node;

    public:
    Solution(int node, unordered_map<int, vector<int> > in_graph) {
        start_node = node;
        graph = in_graph;
        for(int i=0;i<graph.size();i++){
            m_outputDistances.push_back(-1);
        }
    }

    vector<int> outputDistances() {

        queue<int> *Qnode=new queue<int>();
        vector<bool> *visit=new vector<bool>(graph.size(),false);

        Qnode->push(start_node);
        (*visit)[start_node]=true;
        m_outputDistances[start_node]=0;

        while(!Qnode->empty()){
            int tmp=Qnode->front();
            vector<int> *nebr=&(graph[tmp]);
            int dis=m_outputDistances[tmp];

            Qnode->pop();

            if(nebr->empty()) {
                //m_outputDistances.push_back(0);
                return m_outputDistances;
            }
            for(int i=0;i<nebr->size();i++){
                int index=(*nebr)[i];
                if ((*visit)[index]==false){
                    (*visit)[index]=true;
                    Qnode->push(index);
                    m_outputDistances[index]=dis+1;
                }

            }
            nebr= nullptr;
        }
        delete visit;
        delete Qnode;
        visit=nullptr;
        Qnode= nullptr;

        return m_outputDistances;
    }
};