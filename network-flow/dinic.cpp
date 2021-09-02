#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;

struct Edge {
    int to, cap, rev;
};

int level[520];
int visited[520];
int work[520];
vector<Edge> lis[520];
vector<vector<int>> cows;


void clearvisit() {
    fill(visited, visited+500, 0);
}

void AddEdge(int a, int b, int cap) {
    int a_idx = lis[a].size(), b_idx = lis[b].size();
    lis[a].emplace_back(Edge({b, cap, b_idx}));
    lis[b].emplace_back(Edge({a, 0, a_idx}));
}

bool bfs(int s, int t) {
    queue<pii> q;
    visited[s] = 1;
    q.push({s, 0});
    while(!q.empty()) {
        pii curr = q.front();
        level[curr.first] = curr.second;
        q.pop();
        for(auto& e: lis[curr.first]) {
            if(!visited[e.to] && e.cap > 0) {
                visited[e.to] = 1;
                q.push({e.to, curr.second+1});
            }
        }
    }
    return visited[t];
}

int dfs(int curr, int flow, int t) {
    visited[curr] = 1;
    if(curr == t)
        return flow;
    for(int& i=work[curr]; i<lis[curr].size(); i++) {
        Edge& e = lis[curr][i];
        if(!visited[e.to] && e.cap > 0 && level[e.to] == level[curr]+1) {
            int final_flow = dfs(e.to, min(flow, e.cap), t);
            if(final_flow > 0) {
                e.cap -= final_flow;
                lis[e.to][e.rev].cap += final_flow;
                return final_flow;
            }
        }
    }
    return 0;
}

int get_maximum_flow(int s, int t) {
    int max_flow = 0;
    clearvisit();
    while(bfs(s, t)) {
        while(true) {
            clearvisit();
            int res = dfs(s, INT_MAX, t);
            if(res == 0)
                break;
            max_flow += res;
        }
        fill(work, work+500, 0);
        clearvisit();
    }
    return max_flow;
}

int main() {
    int N, M;
    cin >> N >> M;
    for(int i=0; i<N; i++) {
        int tmp;
        cin >> tmp;
        for(int j=0; j<tmp; j++) {
            int t;
            cin >> t;
            AddEdge(i+1, t+N, 1);
        }
    }
    for(int i=1; i<=N; i++) {
        AddEdge(0, i, 1);
    }
    for(int i=N+1; i<=N+M; i++) {
        AddEdge(i, N+M+1, 1);
    }
    cout << get_maximum_flow(0, N+M+1);
}