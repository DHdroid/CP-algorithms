/*
	Recursive Segment Tree C++ Implementation
*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

const int MAX_NODE = 6000020;
const int MAX_NUM = 1000020;

struct SEGTREE {
    ll tree[MAX_NODE];
    ll update(int i, int v, int l, int r, int node) {
        if(i < l || i > r) {
            return tree[node];
        }
        else {
            if(l==r) {
                return tree[node]=tree[node]+v;
            }
            int mid = (l+r)>>1;
            return tree[node] = update(i, v, l, mid, 2*node) + update(i, v, mid+1, r, 2*node+1);
        }
    }
    ll query(int s, int e, int l, int r, int node) {
        if(e<l || s>r) {
            return 0;
        }
        if(s<=l && e>=r) {
            return tree[node];
        }
        else {
            int mid = (l+r)>>1;
            return query(s, e, l, mid, 2*node) + query(s, e, mid+1, r, 2*node+1);
        }
    }
    ll find_kth(int k) {
        int curr = 1;
        int s = 0, e = MAX_NUM;
        while(true) {
            if(s==e) {
                return s;
            }
            if(tree[2*curr] >= k) {
                curr = 2*curr;
                e = (s+e)/2;
            }
            else {
                k -= tree[2*curr];
                curr = 2*curr+1;
                s = (s+e)/2 + 1;
            }
        }
    }
};

SEGTREE seg = SEGTREE();

// author: DHdroid