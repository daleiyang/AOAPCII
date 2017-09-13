#include<cstdio>
#include<cstring>
#include<queue>
#include<utility>
using namespace std;

struct C{
	int x, y, cnt;
	C(int x = 0, int y = 0, int cnt = 0):x(x), y(y), cnt(cnt){}
};
C tc;
int vis[8][8];
char st[3], en[3];
int dx[] = {2, 2, 1, -1, -2, -2,  1, -1};
int dy[] = {1,-1, 2,  2,  1, -1, -2, -2};
int sx, sy, ex, ey;

int main(){
#ifdef LOCAL
	freopen("UVa.439.in", "r", stdin);
	freopen("UVa.439.out", "w", stdout);
#endif
	while(scanf("%s%s", st, en) == 2){
		memset(vis, 0, sizeof(vis));
		sx = st[0]-'a'; sy = st[1]-'0'-1;
		ex = en[0]-'a'; ey = en[1]-'0'-1;
		queue<C> q;
		vis[sx][sy] = 1;
		q.push(C(sx, sy, 0));
		while(!q.empty()){
			tc = q.front(); q.pop();
			if(tc.x == ex && tc.y == ey) break;
			for(int i = 0; i < 8; i++){
				int x = tc.x + dx[i];
				int y = tc.y + dy[i];
				if(x >= 0 && x <= 7 && y >= 0 && y <= 7 && !vis[x][y]){
					vis[x][y] = 1;
					q.push(C(x, y, tc.cnt+1));
				}
			}
		}
		printf("To get from %s to %s takes %d knight moves.\n", st, en, tc.cnt);
	}
	return 0;
}

