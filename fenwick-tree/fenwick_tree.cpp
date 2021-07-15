#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;

// use 1-base index
struct FenwickTree {
	vector<ll> tree;
	int size;
	FenwickTree(int size) {
		this->size = size;
		tree.resize(size+20, 0);
	}
	void init(vector<ll>& v) {
		vector<ll> sums(v.size()+1, 0);
		for(int i=0; i<v.size(); i++) {
			sums[i+1] = sums[i] + v[i];
		}
		for(int i=1; i<=size; i++) {
			tree[i] = sums[i] - sums[i-(i&(~i+1))];
		}
	}
	void update(int i, ll v) {
		while(i <= size) {
			tree[i] += v;
			i += i&(~i+1);
		}
	};
	ll query(int i) {
		ll ret = 0;
		while(i>0) {
			ret += tree[i];
			i -= i&(~i+1);
		}
		return ret;
	}
};