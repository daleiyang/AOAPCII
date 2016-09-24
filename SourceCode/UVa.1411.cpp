#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;

const int maxn = 100+10;

int n, ans[maxn*2];

struct Point{
	int x, y;
	void read(){
		scanf("%d%d", &x, &y);
	}
	double angle(const Point & p) const{
		return atan2(y - p.y, x - p.x);
	}
	bool operator < (const Point & p) const{
		return y < p.y || (y == p.y && x < p.x);
	}
};

struct Node{
	Point p;
	int id;
	double ang;
	bool operator < (const Node & rhs) const{
		return ang < rhs.ang;
	}
	void getangle(const Point & p0){
		ang = p.angle(p0);
	}
	int type(){
		return id <= n ? 1: -1;
	}
}p[maxn*2];

void solve(int L, int R){
	if(L > R) return;
	int pos = L;
	for(int i = L+1; i<=R; i++){
		if(p[i].p < p[pos].p) pos =i;
	}
	swap(p[pos], p[L]);
	int cnt = p[L].type();
	for(int i = L+1; i<=R; i++){
		p[i].getangle(p[L].p);
	}
	sort(p+L+1, p+R+1);
	for(int i = L+1; i <= R; i++){
		cnt += p[i].type();
		if(!cnt){
			ans[p[L].id] = p[i].id;
			ans[p[i].id] = p[L].id;
			solve(L+1, i-1);
			solve(i+1, R);
			return;
		}
	}
}

int main(){
#ifdef LOCAL
	freopen("UVa.1411.in", "r", stdin);
	freopen("UVa.1411.out", "w", stdout);
#endif
	while(scanf("%d", &n) == 1){
		for(int i = 1; i <= (n<<1); i++){
			p[i].p.read();
			p[i].id = i;
		}
		solve(1, n<<1);
		for(int i = 1; i <= n; i++){
			printf("%d\n", ans[i]-n);
		}
	}
	return 0;
}

