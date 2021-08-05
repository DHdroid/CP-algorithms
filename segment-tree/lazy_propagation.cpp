#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;

struct SegTree {
	vector<ll> tree;
	vector<ll> lazy;
	SegTree(int n) {
		tree.resize(4*n, 0);
		lazy.resize(4*n, 0);
	}
	ll init(vector<ll>& v, int node, ll l, ll r) {
		if(l==r) 
			return tree[node] = v[l];
		else {
			ll mid = (l+r) >> 1;
			return tree[node] = init(v, 2*node, l, mid) + init(v, 2*node+1, mid+1, r); 
		}
	}
	void propagate(int node, ll l, ll r) {
		tree[node] += lazy[node] * (r-l+1LL);
		lazy[2*node] += lazy[node];
		lazy[2*node + 1] += lazy[node];
		lazy[node] = 0;
	}
	ll update(int node, ll l, ll r, ll s, ll e, ll v) {
		// add v in [s, e]
		if(s <= l && e >= r) {
			lazy[node] += v;
			return tree[node] + lazy[node] * (r-l+1LL);
		}
		else if(e < l || s > r) {
			return tree[node] + lazy[node] * (r-l+1LL);
		}
		else {
			// propagate 을 하지 않으면 subtree 만으로는 문제를 풀 수가 없다.
			propagate(node, l, r);
			ll mid = (l+r) >> 1;
			return tree[node] = update(2*node, l, mid, s, e, v) + update(2*node+1, mid+1, r, s, e, v); 
		}
	}
	ll query(int node, ll l, ll r, ll s, ll e) {
		if(s <= l && e >= r) {
			return tree[node] + lazy[node] * (r-l+1LL);
		}
		else if(e < l || s > r) {
			return 0;
		}
		else {
			propagate(node, l, r);
			ll mid = (l+r) >> 1;
			return query(2*node, l, mid, s, e) + query(2*node+1, mid+1, r, s, e); 
		}
	}
};