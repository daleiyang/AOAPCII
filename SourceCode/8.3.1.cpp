#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 64;

int G[maxn][maxn], n, st;

void print(){
	for(int r = 0; r < n; r++){
		for(int c = 0; c < n; c++) printf("%3d", G[r][c]);
		printf("\n");
	}
	printf("\n");
}

void dfs(int r, int c, int w){
	if(w == 1) return;
	int i, j;
	bool f = false;
	for(i = r; i < r + w; i++){
		for(j = c; j < c + w; j++){
			if(G[i][j] != 0) {
				f = true;
				break;
			}
		}
		if(f) break;
	}
	int dr = r + w/2;
	int dc = c + w/2;
	if(i < dr){
		G[dr][dc] = G[dr][dc-1] = st;
		if(j < dc) G[dr-1][dc] = st;
		else G[dr-1][dc-1] = st;
	} else{
		G[dr-1][dc] = G[dr-1][dc-1] = st;
		if(j < dc) G[dr][dc] = st;
		else G[dr][dc-1] = st;
	}
	print();
	st++;
	int nw = w/2;
	dfs(r, c, nw);
	dfs(r, c+nw, nw);
	dfs(r+nw, c, nw);
	dfs(r+nw, c+nw, nw);
}

int main(){
#ifdef LOCAL
	freopen("8.3.1.in", "r", stdin);
	freopen("8.3.1.out", "w", stdout);
#endif
	int r, c, k;
	while(scanf("%d%d%d", &k, &r, &c) == 3 && k){
		n = 1<<k;
		memset(G, 0, sizeof(G));
		G[r][c] = -1;
		st = 1;
		print();
		dfs(0, 0, n);
		print();
	}
	return 0;
}

