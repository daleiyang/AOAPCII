#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 1000 + 5;
int a[maxn][maxn];

int main(){
#ifdef LOCAL
	freopen("UVA.10763.in", "r", stdin);
	freopen("UVA.10763.out", "w", stdout);
#endif
	int T, x, y;
	while(scanf("%d", &T) && T){
		memset(a, 0, sizeof(a));
		for(int i = 0; i < T; i++){
			scanf("%d%d", &x, &y);
			a[x][y]++;
			a[y][x]--;
		}
		bool r = true;
		for(int i = 0; i < maxn; i++){
			for(int j = 0; j < maxn; j++){
				if(a[i][j]) {r = false; break;}
			}
		}
		if(r) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}

