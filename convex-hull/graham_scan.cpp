/*
	this code is a solution of 
	https://www.acmicpc.net/problem/1708
*/

#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int,int>;

struct Point {
	ll x,y;
};

vector<Point> points;
vector<Point> ans;

ll ccw(Point& p1, Point& p2, Point& p3) {
	return (p1.y-p2.y) * (p3.x-p2.x) - (p1.x-p2.x) * (p3.y-p2.y);
}

int main() {
	int N;
	scanf("%d",&N);
	for(int i=0,x,y; i<N; i++) {
		scanf("%d %d",&x,&y);
		points.push_back({x,y});
	}
	sort(points.begin(), points.end(), [](Point& p1, Point& p2) {
		return make_pair(p1.y, p1.x) < make_pair(p2.y, p2.x);
	});
	Point s = points[0];
	sort(points.begin()+1, points.end(), [&s](Point& p1, Point& p2) {
		ll tmp = ccw(p1, s, p2);
		if(tmp != 0)
			return tmp < 0;
		// if two points have same tangent, the closer one should be placed before another
		if(p1.y != p2.y) return p1.y < p2.y;
		return p1.x < p2.x;
	});
	ans.push_back(s);
	for(int i=1; i<N; i++) {
		if(ans.size() == 1) {
			ans.push_back(points[i]);
		}
		else {
			while(ans.size() > 1) {
				if(ccw(points[i], ans[ans.size()-1], ans[ans.size()-2]) >= 0) {
					ans.pop_back();
				}
				else {
					ans.push_back(points[i]);
					break;
				}
			}
			if(ans.size() == 1)
				ans.push_back(points[i]);
		}
	}
	printf("%d",ans.size());
}