#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <unordered_map>
#include <stack>

using namespace std;
class Solution
{
      public:
        Solution(unordered_map<int, vector<int>> graph);
        unordered_map<int, vector<int>> graph;
        vector<int> find_cycle();
};

Solution::Solution(unordered_map<int, vector<int>> graph) : graph(graph) {}

vector<int> Solution::find_cycle()
{
        //cout << "Implement me!" << endl;

        int flag=0; int pre;
        stack<int> *Snode=new stack<int>();
        vector<int> record(graph.size(),-1);

        int start_node=0;
        Snode->push(start_node);
        record[start_node]=0;

        while(!Snode->empty()) {
                int tmp = Snode->top();
                vector<int> *tmpVec;
                vector<int> result;

                Snode->pop();
                tmpVec = &(graph[tmp]);

                if (tmpVec->empty()) {}

                else {
                        int size = tmpVec->size();
                        for (int i = size-1; i >= 0; i--) {
                                int ii = (*tmpVec)[i];
                                if (record[ii] == -1 && ii!=record[tmp] ) {
                                        record[ii] = tmp;
                                        Snode->push(ii);
                                } else if (record[ii] != -1 && ii!=record[tmp] ) {
                                        record[record[ii]]=ii;
                                        record[ii]=tmp;
                                        int m=ii;
                                        result.push_back(m);
                                        m=record[m];
                                        while (m != ii) {
                                                result.push_back(m);
                                                m = record[m];
                                        }

                                        return result;
                                }
                        }
                }
                if (Snode->empty()) {
                        for (int i = flag; i < record.size(); i++) {
                                flag++;
                                if (record[i] == -1) {
                                        Snode->push(i);
                                        break;
                                }
                        }
                }
                tmpVec= nullptr;

        }


        delete(Snode);
        Snode=nullptr;

        return {};
}