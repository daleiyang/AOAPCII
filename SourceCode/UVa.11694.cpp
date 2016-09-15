#include<cstdio>
#include<cstring>
#include<vector>
#include<utility>
using namespace std;

typedef pair<int, int> PII;

#define REP(h, b, n) for(int h = b; h < n; h++)
#define rep(h, n) for(int h = 0; h < n; h++)

const int M = 10;

int cnt[M][M], ans[M][M], n, m, R, C;
char num[M][M];
vector<PII> G[M][M];

bool loop(int r, int c, int pr, int pc){
	for(vector<PII>::iterator it = G[r][c].begin(); it != G[r][c].end(); it++){
		if(!(it->first == pr && it->second == pc)){
			if(it->first == R && it->second == C) return true;
			else if(loop(it->first, it->second, r, c)) return true;
		}
	}
	return false;
}

bool check(int r, int c, int type){
	if(r < m-1 && c < m-1){
		if(num[r][c] 		!= '.' && cnt[r][c] 	!= num[r][c] - '0') 	return false;
		if(num[r][c+1] 		!= '.' && cnt[r][c+1] 	>  num[r][c+1] - '0') 	return false;
		if(num[r+1][c] 		!= '.' && cnt[r+1][c] 	>  num[r+1][c] - '0') 	return false;
		if(num[r+1][c+1] 	!= '.' && cnt[r+1][c+1] >  num[r+1][c+1] - '0') return false;
	}
	if(r < m-1 && c == m-1){
		if(num[r][c] 		!= '.' && cnt[r][c] 	!= num[r][c] - '0') 	return false;
		if(num[r][c+1] 		!= '.' && cnt[r][c+1] 	!= num[r][c+1] - '0') 	return false;
		if(num[r+1][c] 		!= '.' && cnt[r+1][c] 	>  num[r+1][c] - '0') 	return false;
		if(num[r+1][c+1] 	!= '.' && cnt[r+1][c+1] >  num[r+1][c+1] - '0') return false;
	}
	if(r == m-1 && c < m-1){
		if(num[r][c] 		!= '.' && cnt[r][c] 	!= num[r][c] - '0') 	return false;
		if(num[r][c+1] 		!= '.' && cnt[r][c+1] 	>  num[r][c+1] - '0') 	return false;
		if(num[r+1][c] 		!= '.' && cnt[r+1][c] 	!= num[r+1][c] - '0') 	return false;
		if(num[r+1][c+1] 	!= '.' && cnt[r+1][c+1] >  num[r+1][c+1] - '0') return false;
	}
	if(r == m-1 && c == m-1){
		if(num[r][c] 		!= '.' && cnt[r][c] 	!= num[r][c] - '0') 	return false;
		if(num[r][c+1] 		!= '.' && cnt[r][c+1] 	!= num[r][c+1] - '0') 	return false;
		if(num[r+1][c] 		!= '.' && cnt[r+1][c] 	!= num[r+1][c] - '0') 	return false;
		if(num[r+1][c+1] 	!= '.' && cnt[r+1][c+1] != num[r+1][c+1] - '0') return false;
	}
	if(type == 1) {
		R = r; C = c;
		if(loop(R, C, -1, -1)) return false;
	}
	if(type == 2) {
		R = r; C = c+1;
		if(loop(R, C, -1, -1)) return false;
	}
	return true;
}

bool dfs(int d){
	if(d == m*m+1) return true;
	int r = d/m, c = d%m;
	
	//try "\"
	cnt[r+1][c+1]++; cnt[r][c]++; ans[r][c] = 1;
	G[r][c].push_back(PII(r+1, c+1));
	G[r+1][c+1].push_back(PII(r, c));
	if(check(r, c, 1)) if(dfs(d+1)) return true;
	G[r+1][c+1].pop_back();
	G[r][c].pop_back();
	cnt[r+1][c+1]--; cnt[r][c]--; ans[r][c] = 0;

	//try "/"
	cnt[r][c+1]++; cnt[r+1][c]++; ans[r][c] = 2;
	G[r][c+1].push_back(PII(r+1, c));
	G[r+1][c].push_back(PII(r, c+1));
	if(check(r, c, 2)) if(dfs(d+1)) return true;
	G[r+1][c].pop_back();
	G[r][c+1].pop_back();
	cnt[r][c+1]--; cnt[r+1][c]--; ans[r][c] = 0;

	return false;
}

int main(){
#ifdef LOCAL
		freopen("UVa.11694.in", "r", stdin);
		freopen("UVa.11694.out", "w", stdout);
#endif
	scanf("%d", &n);
	while(n--){
		scanf("%d", &m);
		rep(i, m+1) rep(j, m+1) G[i][j].clear();
		rep(i, m+1) rep(j, m+1) scanf(" %c ", &num[i][j]);
		memset(cnt, 0, sizeof(cnt));
		memset(ans, 0, sizeof(ans));
		if(dfs(0)){
			rep(i, m) {
				rep(j, m){
					if(ans[i][j] == 1) printf("\\");
					else if(ans[i][j] == 2) printf("/");
				}
				printf("\n");
			}
		}
	}
	return 0;
}

