#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

int n, m, k, T;
const int maxn = 20+5;
int board[maxn][maxn], vis[maxn][maxn][maxn];
int dx[] = {0,  0, 1, -1};
int dy[] = {1, -1, 0,  0};

struct C{
	int x, y, step, layer;
	C(int x = 1, int y = 1, int step = 0, int layer = 0):x(x), y(y), step(step), layer(layer){}
};

int ans(){
	queue<C> q;
	memset(vis, 0, sizeof(vis));
	q.push(C(1, 1, 0, 0));
	vis[1][1][0] = 1;
	while(!q.empty()){
		C tc = q.front(); q.pop();
		if(tc.x == n && tc.y == m) return tc.step;
		for(int i = 0; i < 4; i++){
			int x = tc.x + dx[i];
			int y = tc.y + dy[i];
			int layer = tc.layer;
			if(board[x][y]) layer++; else layer = 0;
			if(!vis[x][y][layer] && layer <= k && x > 0 && x <= n && y > 0 && y <= m){
				vis[x][y][layer] = 1;
				q.push(C(x, y, tc.step+1, layer));
			}
		}
	}
	return -1;
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
		printf("%d\n", ans());
	}
	return 0;
}

