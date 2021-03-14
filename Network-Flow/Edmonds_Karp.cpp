#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;

struct EdmondsKarp {
 	struct Edge {
		int start, end;
		int capacity, flow;
		Edge* duel;
		Edge(int start, int end, int capacity, int flow): start(start), end(end), capacity(capacity), flow(flow){
			duel = nullptr;
		}
	};
	vector<vector<Edge *>> lis; // source: 5000, sink: 5001
	vector<int> prev_node;
	vector<int> prev_edge;
	int n;
	int S, T;

	EdmondsKarp(int num_nodes) {
		n = num_nodes;
		lis = vector<vector<Edge *>>(n+3, vector<Edge *>());
		prev_node = vector<int>(n+3, 0);
		prev_edge = vector<int>(n+3, 0);
		S = n+1;
		T = n+2;
	}

	void ClearFlow() {
		for(int i=1; i<=T; i++) {
			for(auto& e: lis[i]) {
				e->flow = 0;
			}
		}
	}

	void AddEdge(int a, int b, int capacity) {
		Edge *e1 = new Edge(a, b, capacity, 0), *e2 = new Edge(b, a, 0, 0);
		e1->duel = e2;
		e2->duel = e1;
		lis[a].emplace_back(e1);
		lis[b].emplace_back(e2);
	}

	int BFS() {
		queue<int> q;
		fill(prev_node.begin(), prev_node.end(), 0);
		fill(prev_edge.begin(), prev_edge.end(), 0);
		q.push(S);
		while(!q.empty()) {
			int node = q.front();
			q.pop();
			if(node == T) {
				int min_flow = INT_MAX;
				for(int curr = T; curr!=S; curr=prev_node[curr]) {
					auto edge = lis[prev_node[curr]][prev_edge[curr]];
					min_flow = min(min_flow, edge->capacity - edge->flow); 
				}
				for(int curr = T; curr!=S; curr=prev_node[curr]) {
					auto edge = lis[prev_node[curr]][prev_edge[curr]];
					edge->flow += min_flow;
					edge->duel->flow -= min_flow;
				}
				return min_flow;
			}
			else {
			int length = lis[node].size();
				for(int i=0; i<length; i++) {
					auto edge = lis[node][i];
					if(edge->capacity > edge->flow) {
						if(prev_node[edge->end] == 0) {
							q.push(edge->end);
							prev_node[edge->end] = node;
							prev_edge[edge->end] = i;
						}
					}
				}
			}
		}
		return 0;
	}

	int MaxFlow() {
		int ans = 0;
		while(true) {
			int max_flow = BFS();
			if(!max_flow)
				return ans;
			ans+=max_flow;
		}
	}
};