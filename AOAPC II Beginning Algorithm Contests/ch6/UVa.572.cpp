#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 100 + 5;

int idx[maxn][maxn], n, m, cnt;
char oil[maxn][maxn], s[maxn];

void dfs(int r, int c, int & cnt){
	if(r < 0 || r > n-1 || c < 0 || c > m-1) return;
	if(oil[r][c]  == '*' || idx[r][c] != 0) return;
	idx[r][c] = cnt;
	for(int dx = -1; dx <= 1; dx++)
		for(int dy = -1; dy <= 1; dy++)
			if(!(dx==0 && dy == 0)) 
				dfs(r+dx, c+dy, cnt);
}

int main(){
#ifdef LOCAL
		freopen("UVa.572.in", "r", stdin);
		freopen("UVa.572.out", "w", stdout);
#endif
	while(scanf("%d%d", &n ,&m) == 2 && n && m){
		cnt = 0;
		memset(idx, 0, sizeof(idx));
		for(int i = 0; i < n; i++){scanf("%s", oil[i]);}
		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				if(oil[i][j] == '@' && idx[i][j] == 0) 
					dfs(i ,j, ++cnt);
		printf("%d\n", cnt);
	}
	return 0;
}

