#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

int n, m, k, T, ans;
const int maxn = 20+5;
int board[maxn][maxn], vis[maxn][maxn][maxn];
int dx[] = {0,  0, 1, -1};
int dy[] = {1, -1, 0,  0};

void dfs(int x, int y, int step, int layer){
	if(x == n && y == m){
		ans = min(ans, step);
		return;
	}
	for(int i = 0; i < 4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		int nlayer = layer;
		if(board[nx][ny] == 1) nlayer++; else nlayer = 0;
		if((vis[nx][ny][nlayer] < 0 || vis[nx][ny][nlayer] > step+1)
			&& nlayer <= k && nx >= 1 && nx <= n && ny >= 1 && ny <= m){
			vis[nx][ny][nlayer] = step + 1;
			dfs(nx, ny, step+1, nlayer);
		}
	}
	return;
}

int main(){
#ifdef LOCAL
	freopen("UVa.1600.in", "r", stdin);
	freopen("UVa.1600.out", "w", stdout);
#endif
	scanf("%d", &T);
	while(T--){
		scanf("%d%d%d", &n, &m, &k);
		for(int i = 1; i <= n; i++){
			for(int j = 1; j <= m; j++){
				scanf("%d", &board[i][j]);
			}
		}
		memset(vis, -1 ,sizeof(vis));
		ans = 1 << 30;
		dfs(1, 1, 0, 0);
		if(ans == 1<<30) printf("-1\n");
		else printf("%d\n", ans);
	}
	return 0;
}

