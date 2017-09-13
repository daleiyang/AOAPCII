#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;

//Yes, following code got AC, but I need mathematical proof.

const int maxv = 1000 + 1;
int v, e, t, vis[maxv][maxv], visnode[maxv], degree[maxv], kase = 0, block, odd[maxv];
vector<int> GV[maxv];

void dfs(int u){
	for(unsigned int i = 0; i < GV[u].size(); i++){
		if(!vis[u][GV[u][i]]){
			vis[u][GV[u][i]] = vis[GV[u][i]][u] = 1;
			degree[u]++; degree[GV[u][i]]++;
			dfs(GV[u][i]);
		}
	}
	visnode[u] = 1;
}

void solve(){
	block = 0;
	for(int i = 1; i <= v; i++){
		if(!visnode[i] && GV[i].size()){
			memset(degree, 0, sizeof(degree));
			dfs(i);
			int cnt = 0;
			for(int j = 1; j <= v; j++){
				if(degree[j] % 2 == 1){
					cnt++;
				}
			}
			odd[block++] = cnt;
		}
	}
	if(block > 1) {e += block -1;}
	for(int i = 0; i < block; i++){
		if(odd[i] > 2) e += odd[i]/2 -1;
	}
	printf("Case %d: %d\n", ++kase, e*t);
	
}

int main(){
#ifdef LOCAL
	freopen("UVa.12118.in", "r", stdin);
	freopen("UVa.12118.out", "w", stdout);
#endif
	while(scanf("%d%d%d", &v, &e, &t) == 3 && v){
		memset(vis, 0, sizeof(vis));
		memset(visnode, 0 , sizeof(visnode));
		for(int i = 1; i <= v; i++){
			GV[i].clear();
		}
		int x, y, te = e;
		while(te--){
			scanf("%d%d", &x, &y);
			GV[x].push_back(y);
			GV[y].push_back(x);
		}
		solve();
	}
	return 0;
}

