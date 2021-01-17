#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;

vector<int> adj[10020];
vector<int> revadj[10020];
vector<vector<int>> scc;
stack<int> s;
int visited[10020];
void DFS(int node) {
	visited[node] = 1;
	for(auto N: adj[node]) {
		if(!visited[N]) {
			DFS(N);
		}
	}
	s.push(node);
}
void revDFS(int node, vector<int>& v) {
	visited[node] = 1;
	for(auto N: revadj[node]) {
		if(!visited[N]) {
			revDFS(N, v);
		}
	}
	v.push_back(node);
}
void findSCC() {
	fill(visited, visited+10002, 0);
	while(!s.empty()) {
		int tmp = s.top();
		s.pop();
		if(visited[tmp]) {
			continue;
		}
		vector<int> v;
		revDFS(tmp, v);
		sort(v.begin(), v.end());
		scc.push_back(v);
	}
}
int main() {
	int V, E;
	scanf("%d %d",&V,&E);
	for(int i=0; i<E; i++) {
		int t1, t2;
		scanf("%d %d",&t1,&t2);
		adj[t1].push_back(t2);
		revadj[t2].push_back(t1);
	}
	for(int i=1; i<=V; i++) {
		if(!visited[i])
			DFS(i);
	}
	findSCC();
	sort(scc.begin(), scc.end(), [](vector<int> &v1, vector<int> &v2) -> bool {return v1[0] < v2[0];});
	printf("%d\n",scc.size());
	for(auto v: scc) {
		for(auto node: v) {	
			printf("%d ",node);
		}
		printf("-1\n");
	}
}