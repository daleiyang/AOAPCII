#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 35;

int N, k, D;
int cnt, x[maxn], y[maxn], num[maxn];
char maze[maxn][maxn], ch[maxn], G[maxn][maxn];

int dr[4] = { 0, 0, -1,  1};
int dc[4] = {-1, 1,  0,  0};

void print(){
	for(int i = 0; i < N; i++){
		for(int j = 0; j < N; j++){printf("%c", G[i][j]);}
		printf("\n");
	}
}

bool prune(int idx){
	for(int p = 0; p < N; p++)
		for(int q = 0; q < N; q++){
			if(G[p][q] == '2'){
				bool f = false;
				for(int z = 0; z < 4; z++){
					int nr = p + dr[z];
					int nc = q + dc[z];
					if(nr >= 0 && nr < N && nc >= 0 && nc < N){
						if(G[nr][nc] == '2' || (G[nr][nc]!= '2' && ((G[nr][nc]-'A') > idx))) {
							f = true;
						}
					}
				}
				if(!f) {
					return true; //prune when there is a empty cell is surrounded by not empty cell;
				}
			}
		}
	return false;
}

bool dfs(int idx, int r, int c){
	if(idx == cnt) {
		print();
		return true;
	}

	//possible range
	int r1 = r-num[idx]+1;  //left of top-left point
	int c1 = c-num[idx]+1;  //top of top-left point
	
	int r2 = r+num[idx]-1;  //right of top-left point
	int c2 = c+num[idx]-1;  //bottom of top-left point

	//find a start point
	for(int i = r1; i <= r2; i++){
		if(i < 0 || i > N-1) continue;
		for(int j = c1; j <= c2; j++){
			if(j < 0 || j > N-1) continue;
			//find a end point
			for(int m = i; m <= r2; m++){
				if(m < 0 || m > N-1) continue;
				for(int n = j; n <= c2; n++){
					if(n < 0 || n > N-1) continue;
					int area = (abs(i-m)+1) * (abs(j-n)+1);
					if(area != num[idx]) continue; 
					if(r < i || r > m || c < j || c > n) continue;
					
					int cnt = 0;
					for(int p = i; p <= m; p++)
						for(int q = j; q <= n; q++){
							if(G[p][q] != '2') cnt++;
						}
					if(cnt > 1) continue; //not a valid area, some cell is taken by other num[idx];
					
					for(int p = i; p <= m; p++)
						for(int q = j; q <= n; q++){
							G[p][q] = ch[idx];
						}
					
					if(prune(idx)){
						//traceback
						for(int p = i; p <= m; p++)
							for(int q = j; q <= n; q++){
								if(p == r && q == c) continue;
								else G[p][q] = '2';
							}
						continue;
					}
					
					if(dfs(idx+1, x[idx+1], y[idx+1])) return true;
					
					//traceback
					for(int p = i; p <= m; p++)
						for(int q = j; q <= n; q++){
							if(p == r && q == c) continue;
							else G[p][q] = '2';
						}
				}
			}
		}
	}
	return false;
}

int main(){
#ifdef LOCAL
	freopen("UVa.11846.in", "r", stdin);
	freopen("UVa.11846.out", "w", stdout);
#endif
	while(scanf("%d%d", &N, &k) == 2 && N){
		fgets(maze[0], maxn, stdin); //eat the fisrt line enter
		for(int i = 0; i < N; i++){
			fgets(maze[i], maxn, stdin);
		}

		memset(G, '2', sizeof(G));
		cnt = 0;
		for(int i = 0; i < N; i++)
			for(int j = 0; j < N; j++)
				if(maze[i][j] != '.'){
					x[cnt] = i; y[cnt] = j; 
					num[cnt] = maze[i][j] - '0';
					ch[cnt] = 'A' + cnt;
					G[i][j] = ch[cnt];
					cnt++;
				} 
		dfs(0, x[0], y[0]);
	}
	return 0;
}

