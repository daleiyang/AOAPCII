#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 1000 + 5;
int G[maxn][maxn], c[maxn], topo[maxn], n, m, t;

bool dfs(int u){
	c[u] = -1;
	for(int v = 1; v <= n; v++){
		if(G[u][v]){
			if(c[v] < 0) return false;
			else if(!c[v] && !dfs(v)) return false;
		}
	}
	c[u] = 1;
	topo[--t] = u;
	return true;
}

bool toposort(){
	t = n;
	for(int u = 1; u <= n; u++){
		if(!c[u]){if(!dfs(u)) return false;}
	}
	return true;
}

int main(){
#ifdef LOCAL
		freopen("UVa.10305.in", "r", stdin);
		freopen("UVa.10305.out", "w", stdout);
#endif
	while(scanf("%d%d", &n, &m) == 2 && n  /* && m*/) {   
		memset(G, 0, sizeof(G));	
		memset(c, 0 ,sizeof(c));
		int u, v;
		while(m--){
			scanf("%d%d", &u, &v);
			G[u][v] = 1;
		}
		if(toposort()){
			for(int i = 0; i < n; i++){
				if(!i) printf("%d", topo[i]);
				else printf(" %d", topo[i]);
			}
			printf("\n");
		}
		else{printf("No\n");}
	}
	return 0;
}

