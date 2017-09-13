#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 21;

int G[maxn][maxn], s[maxn], vis[maxn], target, x, y, n, cnt;

bool dfs(int v){
	if(v == target) return true;
	for(int i = 2; i <= n; i++){
		if(!vis[i] && G[v][i]){
			vis[i] = 1;
			if(dfs(i)) return true;
		}
	}
	return false;
}

void print_permutation(int * A, int cur){
	if(A[cur-1] ==  target){
		for(int i = 0; i < cur; i++){
			if(i == 0) printf("%d", A[i]);
			else printf(" %d", A[i]);
		}
		printf("\n"); cnt++;
	}
	else{
		for(int i = 2; i <= n; i++){
			if(G[A[cur-1]][i]){
				int k = 1;
				for(int j = 0; j < cur; j++){
					if(A[j] == i) {k = 0; break;}
				}
				if(k){
					A[cur] = i;
					print_permutation(A, cur+1);
				}
			}
		}
	}
}

int main(){
#ifdef LOCAL
	freopen("UVa.208.in", "r", stdin);
	freopen("UVa.208.out", "w", stdout);
#endif
	int kase = 0;
	while(scanf("%d", &target) == 1){
		printf("CASE %d:\n", ++kase);

		//input.
		memset(G, 0, sizeof(G));
		n = 0; cnt = 0;
		while(scanf("%d%d", &x, &y) == 2 && x){
			G[x][y] = G[y][x] = 1;
			n = max(max(x, y), n);
		}

		//dfs to check the connectivit.
		memset(vis, 0, sizeof(vis));
		if(!dfs(1)) {
			printf("There are 0 routes from the firestation to streetcorner %d.\n", target);
			continue;
		}
		s[0] = 1;
		print_permutation(s, 1);
		printf("There are %d routes from the firestation to streetcorner %d.\n", cnt, target);
	}
	return 0;
}

