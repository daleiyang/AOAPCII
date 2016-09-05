#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 15+5, maxm = 30+5;

int r, c, cnt, x[maxm], y[maxm], dig[maxm], G[maxm][maxm], num[maxm], id[maxn][maxn], vis[maxm];
int A[maxm], B[maxm], idxB;
int dx[4] = {0,  0, 1, -1};
int dy[4] = {1, -1, 0,  0};

char maze[maxn][maxn];

bool check(){
	
}

void dfs(int d, int cnt){
	vis[cnt] = 1;
	A[d] = num[cnt];
	bool f = false;
	for(int i = 0; i < dig[cnt]; i++){
		if(!vis[G[cnt][i]]){
			if(check()){
				dfs(d+1, G[cnt][i]);
				f = true;
			}
		}
	}
	if(!f){
		if(d > idxB){
			for(int i = 0; i <= d; i++){
				B[i] = A[i];
			}
			idxB = d;
		}
		if(d == idxB){
			int t = 0;
			while(A[t] == B[t]) t++;
			if(A[t] > B[t]){
				for(int i = t; i <= d; i++){
					B[i] = A[i];
				}
			}
		}
	}
	vis[cnt] = 0;
}

int main(){
#ifdef LOCAL
	freopen("UVa.11882.in", "r", stdin);
	freopen("UVa.11882.out", "w", stdout);
#endif
	while(scanf("%d %d", &r, &c) == 2 && r){
		memset(id, -1, sizeof(id));
		memset(G, 0, sizeof(G));
		memset(vis, 0, sizeof(vis));
		idxB = 0; B[0] = 0;
		fgets(maze[0], maxn, stdin); // remove the new line char.
		for(int i = 0; i < r; i++){fgets(maze[i], maxn, stdin);}
		
		
		cnt = 0;
		for(int i = 0;  i < r; i++) for(int j = 0; j < c; j++){
			if(maze[i][j] != '#'){
				num[cnt] = maze[i][j] - '0';
				x[cnt] = i; y[cnt] = j;
				id[i][j] = cnt;
				cnt++;
			}
		}
		for(int i = 0; i < cnt; i++){
			int tx, ty;
			dig[i] = 0;
			for(int j = 0; j < 4; j++){
				tx = x[i] + dx[j];
				ty = y[i] + dy[j];
				if(tx >= 0 && tx < r && ty >= 0 && ty < c && maze[tx][ty] != '#'){
					G[i][dig[i]++] = id[tx][ty];
				}
			}
		}
		for(int i = 0; i < cnt; i++){
			dfs(0, i);
		}
		for(int i = 0; i <=idxB; i++){
			printf("%d", B[i]);
		}
		printf("\n");
	}
	return 0;
}

