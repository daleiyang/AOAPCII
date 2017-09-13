#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 10 + 5;

int r, c, vis[4][20], maxd, vis2[maxn][maxn];
char mp[maxn][maxn];

bool dfs(int d){
	if(d == maxd){
		for(int i = 0; i < r; i++) for(int j = 0; j < c; j++){
			if(mp[i][j] == 'X' && !vis[0][i] && !vis[1][j] && !vis[2][i-j+10] && !vis[3][i+j]){
				return false;
			}
		}
		return true;
	}
	for(int i = 0; i < r; i++) for(int j = 0; j < c; j++){
		if(vis2[i][j]) continue;
		vis2[i][j] = 1;
		int t1 = vis[0][i], t2 = vis[1][j], t3 = vis[2][i-j+10], t4 = vis[3][i+j];
		vis[0][i] = vis[1][j] = vis[2][i-j+10] = vis[3][i+j] = 1;
		if(dfs(d+1)) return true;
		vis[0][i] = t1; vis[1][j] = t2; vis[2][i-j+10] = t3; vis[3][i+j] = t4;
		vis2[i][j] = 0;
	}
	return false;
}

int main(){
#ifdef LOCAL
	freopen("UVa.11214.in", "r", stdin);
	freopen("UVa.11214.out", "w", stdout);
#endif
	int kase = 0;
	while(scanf("%d", &r) == 1 && r){
		scanf("%d", &c);
		for(int i = 0; i < r; i++){scanf("%s", mp[i]);}
		for(maxd = 0; maxd < 10; maxd++){
			memset(vis, 0, sizeof(vis));
			memset(vis2, 0, sizeof(vis2));
			if(dfs(0)) break;
		}
		printf("Case %d: %d\n", ++kase, maxd);
	}
	return 0;
}

