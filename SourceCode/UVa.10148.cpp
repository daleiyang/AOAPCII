#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1000 + 5;

struct path{
	int x, y;
	bool operator < (const path & rhs) const{
		return (y < rhs.y) || (y == rhs.y && x > rhs.x);
	}
}p[maxn];

int vis[20005], k, n;

int main(){
#ifdef LOCAL
	freopen("UVa.10148.in", "r", stdin);
	freopen("UVa.10148.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	while(T--){
		int m = 0;
		scanf("%d%d", &k, &n);
		for(int i = 0; i < n; i++){
			scanf("%d%d", &p[i].x, &p[i].y);
			if(p[i].x > p[i].y){
				int temp = p[i].x;
				p[i].x = p[i].y;
				p[i].y = temp;
			}
			p[i].x += 10000;
			p[i].y += 10000;
			if(p[i].y > m) m = p[i].y;
		}
		sort(p, p+n);
		memset(vis, 0, sizeof(vis));
		int sum = 0;
		for(int i = 0; i < n; i++){
			int c = 0;
			for(int j = p[i].x; j <= p[i].y; j++){
				if(vis[j]) c++;
			}
			if(c < k){
				for(int j = p[i].y; j >= p[i].x && c < k; j--){
					if(!vis[j]){
						vis[j] = 1;
						c++;
						sum++;
					}
				}
			}
		}
		printf("%d\n", sum);
		for(int i = 0; i <= m; i++){
			if(vis[i]) printf("%d\n", i-10000);
		}
		if(T) printf("\n");
	}
	return 0;
}

