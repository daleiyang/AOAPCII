#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 1000 + 5;

char s[maxn][maxn];
int height[maxn], ans[maxn*2];

struct Rect{
	int c, h;
	Rect(int c = 0, int h = 0):c(c), h(h){}
} rect[maxn];

int main(){
#ifdef LOCAL
		freopen("UVA.12265.in", "r", stdin);
		freopen("UVA.12265.out", "w", stdout);
#endif
	int T, n, m;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &n, &m);
		for(int i = 0; i < n; i++) scanf("%s", s[i]);

		memset(height, 0, sizeof(height));
		memset(ans, 0, sizeof(ans));
		for(int i = 0; i < n; i++){
			int top  = - 1;
			for(int j = 0; j < m; j++){
				if(s[i][j] == '#'){
					height[j] = 0;
					top = - 1;
				}
				else{
					height[j]++;
					Rect r(j, height[j]);
					if(top < 0) rect[++top] = r;
					else{
						while(top >= 0 && r.h <= rect[top].h) r.c = rect[top--].c;
						if(top < 0 || r.h - r.c > rect[top].h - rect[top].c) rect[++top] = r;
					}
					ans[j-rect[top].c+1+rect[top].h]++;
				}
			}
		}
		for(int i = 0; i <= n+m; i++){
			if(ans[i]) printf("%d x %d\n", ans[i], i*2);
		}
	}
	return 0;
}

