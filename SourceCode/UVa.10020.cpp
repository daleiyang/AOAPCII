#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 5;

int path[maxn];

struct range{
	int x, y, dx, dy;
	bool operator < (const range & rhs) const{
		return (dx < rhs.dx) || (dx == rhs.dx && dy > rhs.dy);
	}
}r[maxn];

int main(){
#ifdef LOCAL
	freopen("UVa.10020.in", "r", stdin);
	freopen("UVa.10020.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	while(T--){
		int m;
		scanf("%d", &m);
		int n = 0, x, y;
		while(scanf("%d%d", &x, &y) == 2 && (x || y)){
			if(x > y){
				int temp = x;
				x = y;
				y = temp;
			}
			if(x > m || y < 0) continue;
			r[n].x = x;
			r[n].y = y;
			if(x > 0) r[n].dx = x; else r[n].dx = 0;
			if(y < m) r[n].dy = y; else r[n].dy = m;
			n++;
		}
		sort(r, r+n);
		int maxx = 0, sum = 0, pos = 0;
		while(1){
			if(pos == m) break;
			maxx = 0;
			for(int i = 0; i < n; i++){
				if(r[i].dx <= pos &&r[i].dy >= pos){
					if(maxx <= r[i].dy){
						maxx = r[i].dy;
						path[sum] = i;
					}
				}
			}
			if(maxx == 0){
				sum = 0;
				break;
			}
			pos = maxx;
			sum++;
		}
		printf("%d\n", sum);
		for(int i = 0; i < sum; i++) printf("%d %d\n", r[path[i]].x, r[path[i]].y);
		if(T) printf("\n");
	}
	return 0;
}

