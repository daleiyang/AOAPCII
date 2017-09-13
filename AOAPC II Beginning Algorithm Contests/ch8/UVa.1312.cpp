//http://blog.csdn.net/keshuai19940722/article/details/19174879
#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 100 + 5;

struct point{
	int x, y;
	point(int x = 0, int y = 0):x(x), y(y){}
	bool operator < (const point & rhs) const {
		return (x < rhs.x || (x == rhs.x && y < rhs.y));
	}
} p[maxn];

int n, w, h, dy[maxn];

void input(){
	scanf("%d%d%d", &n, &w, &h);
	for(int i = 0; i < n; i++){
		scanf("%d%d", &p[i].x, &p[i].y);
		dy[i] = p[i].y;
	}
	dy[n] = 0; dy[n+1] = h;
	sort(dy, dy+n+2);
	sort(p, p+n);
}

void solve(){
	int ansx, ansy, ans = 0;
	int m = unique(dy, dy+n+2) - dy;
	for(int i = 0; i < m; i++){
		for(int j = i+1; j < m; j++){
			int maxy = dy[j], miny = dy[i];
			int hh = maxy - miny, ww = 0, tmp = 0;
			for(int k = 0; k < n; k++){
				if(p[k].y <= miny || p[k].y >= maxy) continue;
				ww = p[k].x - tmp;
				if(ans < min(hh, ww)){
					ans = min(hh, ww);
					ansx = tmp;
					ansy = miny;
				}
				tmp = p[k].x;
			}

		 	ww = w - tmp;
			if(ans < min(hh, ww)){
					ans = min(hh, ww);
					ansx = tmp;
					ansy = miny;
			}
		}
	}
	printf("%d %d %d\n", ansx, ansy, ans);
}

int main(){
#ifdef LOCAL
		freopen("UVa.1312.in", "r", stdin);
		freopen("UVa.1312.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	while(T--){
		input();
		solve();
		if(T) printf("\n");
	}
	return 0;
}

