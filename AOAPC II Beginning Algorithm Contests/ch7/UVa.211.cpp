#include<cstdio>
#include<cstring>
using namespace std;

const int R=7, C=8;

int pips[R][C], t[R][R], ans[R][C], vis[30], cnt;
int dr[2] = {1, 0};
int dc[2] = {0, 1};

void init(){
	int c = 1;
	for(int i = 0; i < R; i++)
		for(int j = i; j < R; j++)
			t[i][j] = t[j][i] = c++;
}

bool input(){
	cnt = 0;
	for(int i = 0; i < R; i++)
		for(int j = 0; j < C; j++)
			if(scanf("%d", &pips[i][j]) != 1) return false;
	return true;
}

void dfs(int r, int c, int n){
	if(n == 28){
		printf("\n\n"); cnt++;
		for(int i = 0; i < R; i++){
			for(int j = 0; j < C; j++) {printf("%4d", ans[i][j]);}
			printf("\n");
		}
		return;
	}
	if(c == C) {r++; c=0;} if(r >= R) return;
	if(ans[r][c]) {dfs(r, c+1, n);}
	else{
		for(int i = 0; i < 2; i++){
			int nr = r+dr[i];
			int nc = c+dc[i];
			if(nr >= R || nc >= C || ans[nr][nc]) continue;
			int bones = t[pips[r][c]][pips[nr][nc]];
			if(!vis[bones]){
				vis[bones] = 1;
				ans[r][c] = ans[nr][nc] = bones;
				dfs(r, c+1, n+1);
				ans[r][c] = ans[nr][nc] = 0;
				vis[bones] = 0;
			}
		}
	}
}

int main(){
#ifdef LOCAL
	freopen("UVa.211.in", "r", stdin);
	freopen("UVa.211.out", "w", stdout);
#endif
	int kase = 0;
	memset(t, 0, sizeof(t));
	init();
	while(input()){
		if(kase)printf("\n\n\n\n\n");
		memset(vis, 0, sizeof(vis));
		memset(ans, 0, sizeof(ans));
		printf("Layout #%d:\n\n\n", ++kase);
		for(int i = 0; i < R; i++){
			for(int j = 0; j < C; j++) {printf("%4d", pips[i][j]);}
			printf("\n");
		}
		printf("\n");
		printf("Maps resulting from layout #%d are:\n", kase);
		dfs(0, 0, 0); //start from r=0 && c=0 && o number found.
		printf("\n\nThere are %d solution(s) for layout #%d.\n", cnt, kase);
	}
	return 0;
}

