#include<cstdio>
#include<cstring>
#include<vector>
#include<utility>
using namespace std;

const int maxn = 35;
typedef pair<int, int> PII;

int n, k, D;
int cnt, x[maxn], y[maxn], num[maxn];
char maze[maxn][maxn], ch[maxn], G[maxn][maxn];
vector<PII> h[maxn];

int dr[4] = { 0, 0, -1,  1};
int dc[4] = {-1, 1,  0,  0};

void print(){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){printf("%c", G[i][j]);}
		printf("\n");
	}
}

bool dfs(int idx, int r, int c, int d){
	if(num[idx]-1 == (int)h[idx].size()){
		if(idx + 1 < cnt){
			if(dfs(idx+1, x[idx+1], y[idx+1], 0)) return true;
			else {
				if(h[idx].size()){
					int t = h[idx].size() - 1;
					G[h[idx][t].first][h[idx][t].second] = '0';
					h[idx].pop_back();
				}
				return false;
			}
		}
		else if(idx+1 == cnt){
			print();
			return true;
		}
	}
	for(int i = 0; i < 4; i++){
		int nr = r + dr[i];
		int nc = c + dc[i];
		if(nr >= 0 && nr < n && nc >= 0 && nc < n && G[nr][nc] == '0'){
			G[nr][nc] = ch[idx]; 
			h[idx].push_back(PII(nr, nc));
			if(dfs(idx, nr, nc, d+1)) return true;	
		}
	}
	if(d == 0){
		for(vector<PII>::iterator it = h[idx].begin(); it != h[idx].end(); it++){
			G[it->first][it->second] = '0';
		}
		h[idx].clear();	
	}
	return false;
}

int main(){
#ifdef LOCAL
	freopen("UVa.11846.in", "r", stdin);
	freopen("UVa.11846.out", "w", stdout);
#endif
	while(scanf("%d%d", &n, &k) == 2 && n){
		fgets(maze[0], maxn, stdin); //eat the fisrt line enter
		for(int i = 0; i < n; i++){
			fgets(maze[i], maxn, stdin);
		}

		memset(G, '0', sizeof(G));
		cnt = 0;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				if(maze[i][j] != '.'){
					x[cnt] = i; y[cnt] = j; 
					num[cnt] = maze[i][j] - '0';
					ch[cnt] = 'A' + cnt;
					G[i][j] = ch[cnt];
					cnt++;
				}
		for(int i = 0 ; i < maxn; i++){h[i].clear();}
		dfs(0, x[0], y[0], 0);
	}
	return 0;
}

