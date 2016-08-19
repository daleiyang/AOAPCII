#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<ctime>
using namespace std;

const int dif = 105;
const int maxn = 20;

int n, s[maxn+5], G[210+5][210+5], vis[210+5][210+5], cnt, sum[maxn];
int dx[4] = { 1,  0,  0, -1};
int dy[4] = { 0,  1, -1,  0};
int cd[4][2] = {{1, 2}, {0, 3}, {0, 3}, {1, 2}};
char di[4] = {'e', 'n', 's', 'w'};

void dfs(int cur, int x, int y, int d){
	if((abs(x - dif) + abs(y - dif)) > (sum[n] - sum[cur])) return; //prune
	if((abs(x-dif) > sum[n]/2) || (abs(y-dif) > sum[n]/2)) return; //prune
	if(x == dif && y == dif && cur < n) return; //prune
	if(cur == n &&(x != dif || y != dif)) return;
	if(cur == n && x == dif && y == dif) {
		for(int i = 0; i < n; i++){printf("%c", di[s[i]]);}
		printf("\n"); cnt++;
		return;
	}
	for(int i = 0; i < 2; i++){
		int newd = cd[d][i];
		bool f = true;
		for(int j = 1; j <= cur + 1; j++){
			if(G[x + dx[newd] * j][y + dy[newd] * j]){
				f = false;
				break;
			}
		}
		if(f && !vis[x+dx[newd]*(cur+1)][y+dy[newd]*(cur+1)]) {
			s[cur] = newd;
			vis[x+dx[newd]*(cur+1)][y+dy[newd]*(cur+1)] = 1;
			dfs(cur+1, x+dx[newd]*(cur+1), y+dy[newd]*(cur+1), newd);
			vis[x+dx[newd]*(cur+1)][y+dy[newd]*(cur+1)] = 0;
		}
	}
}

void cal_sum(){
	sum[0] = 0;
	for(int i = 1; i <= maxn; i++){
		sum[i] = sum[i-1] + i;
	}
}

int main(){
#ifdef LOCAL
		freopen("UVa.225.in", "r", stdin);
		freopen("UVa.225.out", "w", stdout);
#endif
	int T, k, x, y;
	scanf("%d", &T);
	cal_sum();
	while(T--){
		scanf("%d%d", &n, &k);
		memset(G, 0, sizeof(G));
		memset(vis, 0, sizeof(vis));
		cnt = 0;
		while(k--){
			scanf("%d%d", &x, &y);
			G[x+dif][y+dif] = 1;
		}
		for(int i = 0; i < 4; i++){
			s[0] = i;
			if(G[dif+dx[i]][dif+dy[i]]) continue;
			vis[dif+dx[i]][dif+dy[i]] = 1;
			dfs(1, dif+dx[i], dif+dy[i], i);
			vis[dif+dx[i]][dif+dy[i]] = 0;
		}
		printf("Found %d golygon(s).\n\n", cnt);
	}
	//printf("Time used = %.4f\n", (double)clock()/CLOCKS_PER_SEC);
	return 0;
}

