#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

class Solution {

	/*
	* Class data:
	* m_graph:
    *   unordered_map where the keys are node IDs and the values are agjacency lists
    *   *The first entry in each adjacency list is the weight of the key node
    * start_node & end_node:
    *   The id of the start and end node respectively 
	*/
public:

	Solution(int start_node, int end_node, unordered_map<int, vector<int>> in_graph);
	vector<int> outputPath();
	vector<int> m_output_path;
    unordered_map<int, vector<int>> m_graph;
    int m_start_node;
    int m_end_node;

};






Solution::Solution(int start_node, int m_end_node, unordered_map<int, vector<int>> in_graph) :
	m_graph(in_graph), m_start_node(start_node), m_end_node(m_end_node)
{/* Nothing needs to be added here.*/}


vector<int> Solution::outputPath() {
    int size=m_graph.size();
	int set[size];
    int f[size]={};
    
	for(int i=0;i<size;i++){
		set[i]=-1;
	}


	auto cmp2 = [&](int left, int right) {
		int a=set[left];
		int b=set[right];
		return (a ^ 1) > (b ^ 1);
	};
	std::priority_queue<int,vector<int>,decltype(cmp2)> pq(cmp2);

	//m_output_path.push_back(m_start_node);
    f[m_end_node]=-1;
	set[m_end_node]=0;
	int father=m_end_node;

	while(1){
		vector<int> cur=m_graph[father];
		//cout<<tmp<<" "<<cur[0];
		int cur_size=cur.size();
		for(int i=1;i<cur_size;i++){
			int son=cur[i];
			int weight=m_graph[son][0];

			if(set[son]==-1||set[father]+weight<set[son]) {
                f[son]=father;
				set[son]=set[father]+weight;
                pq.push(son);
			}
		}
		 if(pq.empty())
            return vector<int>();
		father=pq.top();
		if(father==m_start_node) {
            while(father!=-1){
                m_output_path.push_back(father);
                father=f[father];
            }
////		  reverse the vector
//            vector<int>::reverse_iterator riter;
//            for(riter=aa->rbegin();riter!=aa->rend();riter++){
//                m_output_path.push_back(*riter);
//            }
            return m_output_path;
		}
       
		pq.pop();

	}

}
