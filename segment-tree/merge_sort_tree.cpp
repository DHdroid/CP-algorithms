#include <bits/stdc++.h>
using namespace std;

struct Node {
	vector<int> values{};
};

struct MergeSortTree {
	Node nodes[800020];
	void merge(vector<int>& target, vector<int>& v1, vector<int>& v2) {
		int pt1 = 0, pt2 = 0;
		while(pt1<v1.size() || pt2<v2.size()) {
			if(pt2 >= v2.size() || (pt1 < v1.size() && v1[pt1] < v2[pt2])) {
				target.push_back(v1[pt1]);
				pt1++;
			}
			else {
				target.push_back(v2[pt2]);
				pt2++;
			}

		}
	}
	void build(int node, int l, int r, vector<int>& init) {
		if(l==r) {
			nodes[node].values.push_back(init[l]);
		}
		else {
			int mid = (l+r) >> 1;
			build(2*node, l, mid, init);
			build(2*node+1, mid+1, r, init);
			merge(nodes[node].values, nodes[2*node].values, nodes[2*node+1].values);
		}
	}
	int query(int node, int l, int r, int s, int e, int k) {
		if(e < l || s > r) {
			return 0;
		}
		else {
			if(s <= l && e >= r) {
				auto& v = nodes[node].values;
				return lower_bound(v.begin(), v.end(), k) - v.begin();
			}
			else {
				int mid = (l+r)>>1;
				return query(2*node, l, mid, s, e, k) + query(2*node+1, mid+1, r, s, e, k); 
			}
		}
	}
} mst;