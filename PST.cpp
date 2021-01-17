/*
	Persistent Segment Tree C++ Implementation
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

const int MAX_NODE = 7000000;
const int MAX_NUM = 250000;

struct Node {
	int val, lnum, rnum;
};

struct PST {
	int curroot, num, nodecnt;
	int root[MAX_NUM+20];
	Node tree[MAX_NODE+20];
	void init(int n) {
		nodecnt = -1;
		num = n;
		curroot = 0;
		root[0] = 0;
		initialize(0, num-1); 
	}
	int initialize(int s, int e) {
		int mid = (s+e) >> 1, idx = nodecnt++;
		if(s==e) {
			tree[idx] = {0, -1, -1};
		}
		else {
			int l = initialize(s, mid), r = initialize(mid+1, e); 
			tree[idx] = {0, l, r};	
		}
		return idx;
	}
	void addNode(int idx, int val, bool newnode = true) {
		int preroot = root[curroot];
		if(newnode) 
			curroot++;
		root[curroot] = _addNode(idx, val, 0, num-1, preroot);
	}
	int _addNode(int idx, int val, int s, int e, int curr) {
		if(idx < s || idx > e) {
			return curr;
		}
		else {
			int insert_idx = nodecnt++, mid = (s+e)>>1;
			int left = tree[curr].lnum, right = tree[curr].rnum;
			int l = (s>=e)?-1:_addNode(idx, val, s, mid, left);
			int r = (s>=e)?-1:_addNode(idx, val, mid+1, e, right);
			tree[insert_idx] = {tree[curr].val+val, l, r};
			return insert_idx;
		}
	}
	int query(int l, int r, int rootnum) {
		return _query(l,r,0,num-1,root[rootnum]);
	}
	int _query(int l, int r, int s, int e, int curr) {
		if(r < s || l > e) {
			return 0;
		}
		else if(l <= s && r >= e) {
			return tree[curr].val;
		}
		else {
			int mid = (s+e) >> 1;
			return _query(l, r, s, mid, tree[curr].lnum) + _query(l, r, mid+1, e, tree[curr].rnum);
		}
	}
	int find_kth(int rootnum, int k) {
		if(tree[root[rootnum]].val < k) {
			return INT_MAX;
		}
		else {
			int curnode = root[rootnum];
			int sc=0, ec=num-1;
			while(true) {
				int left = tree[curnode].lnum, right = tree[curnode].rnum;
				int mid = (sc+ec) >> 1;
				if(sc == ec)  {
					return sc;
				}
				if(tree[left].val >= k) {
					curnode = left;
					ec = mid;
				}
				else {
					k -= tree[left].val;
					curnode = right;
					sc = mid+1;
				}
			}
		}
	}
};

PST pst = PST();
int main() {
	pst.init(MAX_NUM);
	// must be initialized
}
// author: DHdroid