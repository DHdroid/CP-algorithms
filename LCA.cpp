#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;

vector<int> lis[100020];
int visited[100020];
int depth[100020];
int parent[100020][18]; // sparse_table
void dfs(int node, int par) {
	visited[node] = 1;
	depth[node] = depth[par]+1;
	parent[node][0] = par;
	for(int i=1; (1<<i)<depth[node]; i++) {
		parent[node][i] = parent[parent[node][i-1]][i-1];
	}
	for(auto i: lis[node]) {
		if(!visited[i]) {
			dfs(i, node);
		}
	}
}
int LCA(int a, int b) {
	if(depth[a] < depth[b])
		return LCA(b, a);
	int diff = depth[a] - depth[b];
	while(diff > 0) {
		for(int i=17; i>=0; i--) {
			if((1<<i) <= diff) {
				diff -= (1<<i);
				a = parent[a][i];
				break;
			}
		}
	}
	while(a!=b) {
		for(int i=17; i>=0; i--) {
			if(i==0) {
				a = parent[a][0];
				b = parent[b][0];
			}
			else {
				if(parent[a][i]!=parent[b][i]) {
					a = parent[a][i];
					b = parent[b][i];
					break;
				}
			}
		}
	}
	return a;
}

int main() {
	int n, m;
	cin >> n;
	for(int i=0; i<n-1; i++) {
		int t1, t2;
		cin >> t1 >> t2;
		lis[t1].push_back(t2);
		lis[t2].push_back(t1);
	}
	dfs(1, 0);
	cin >> m;
	while(m--) {
		int q1, q2;
		cin >> q1 >> q2;
		cout << LCA(q1, q2) << endl;
	}
}