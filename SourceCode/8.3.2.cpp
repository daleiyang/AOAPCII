#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 64;

int G[maxn][maxn], k;

void print(){
	int n = 1<<k;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++) printf("%3d", G[i][j]);
		printf("\n");
	}
	printf("\n");
}

void dfs(int d){
	if(d > k) return;
	int len = 1<<(d-1);
	for(int i = 0; i < len; i++)
		for(int j = 0; j < len; j++){
			G[i+len][j] = G[i][j]+len; //left bottom
			G[i][j+len] = G[i][j]+len; //rigth top
			G[i+len][j+len] = G[i][j]; //right bottom
		}
	dfs(d+1);
}

int main(){
#ifdef LOCAL
	freopen("8.3.2.in", "r", stdin);
	freopen("8.3.2.out", "w", stdout);
#endif
	while(scanf("%d", &k) == 1 && k){
		memset(G, 0, sizeof(G));
		G[0][0] = 1;
		print();
		dfs(1);
		print();
	}
	return 0;
}

