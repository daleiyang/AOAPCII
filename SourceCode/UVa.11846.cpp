#include<cstdio>
#include<cctype>
using namespace std;

#define REP(i, b, n) for(int i = b; i < n; i++)
#define rep(i, n) REP(i, 0, n)

const int M = 20;

char t[M][M], ans[M][M];
int n;

bool dfs(char c, int d){
	while(d != n*n && ans[d/n][d%n] != '.') d++;
	if(d == n*n) return true;
	int dx = d%n, dy = d/n;
	REP(h, dy, n) REP(w, dx, n){
		int area = (h-dy+1)*(w-dx+1);
		if(area > 9) break;
		if(ans[h][w] != '.') break;
		int now  = -1, out = false, cnt = 0;
		REP(y, dy, h+1){
			REP(x, dx, w+1){
				if(isdigit(t[y][x])){
					cnt++;
					now = t[y][x] - '0';
				}
				if(ans[y][x] != '.'){
					out = true;
					break;
				}
			}
			if(cnt > 1 || out || (now != -1 && now != area)) break;
		}
		if(cnt > 1 || out || (now != -1 && (area > now || now%(h-dy+1) != 0))) break;
		if(cnt == 0 || now > area) continue;
		REP(y, dy, h+1) REP(x, dx, w+1){
			ans[y][x] = c;
		}
		if(dfs(c+1, d+(w-dx+1))) return true;
		REP(y, dy, h+1) REP(x, dx, w+1){
			ans[y][x] = '.';
		}
	}
	return false;
}

int main(){
#ifdef LOCAL
	freopen("UVa.11846.in", "r", stdin);
	freopen("UVa.11846.out", "w", stdout);
#endif
	int temp;
	while(scanf("%d%d", &n, &temp) == 2 && n){
		rep(i, n) rep(j, n){
			scanf(" %c ", &t[i][j]); //interesting, with two black space, we could swallow the /r/n
			ans[i][j] = '.';
		}
		dfs('A', 0);
		rep(i, n){
			rep(j, n) printf("%c", ans[i][j]);
			printf("\n");
		}
	}
	return 0;
}

