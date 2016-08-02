#include<cstdio>
#include<cstring>
#include<cctype>
#include<queue>
using namespace std;

const int maxs = 20;
const int maxn = 150;

int dx[] = {0, 1, -1, 0, 0};
int dy[] = {0, 0, 0, 1, -1};
int s[3], t[3]; //starting , ending position for each ghost
int deg[maxn], G[maxn][5]; //target cell for each move, including "no move"

int ID(int a, int b, int c){
	return (a<<16)|(b<<8)|c;
}

bool conflict(int a, int a2, int b, int b2){
	return (a2 == b2) || (a == b2 && b == a2);
}

int d[maxn][maxn][maxn]; //distance from starting state
int d2[maxn][maxn][maxn]; 

int bfs(){
	queue<int> q, q2, next;
	q.push(ID(s[0], s[1], s[2]));
	q2.push(ID(t[0], t[1], t[2]));

	memset(d, -1 ,sizeof(d));
	memset(d2, -1 ,sizeof(d2));
	d[s[0]][s[1]][s[2]] = 0;
	d2[t[0]][t[1]][t[2]] = 0;

	while(!q.empty() || !q2.empty()){
		//for the first queue
		while(!q.empty()){
			int u = q.front(); q.pop();
			int a = (u>>16)&0xff, b = (u>>8)&0xff, c = u&0xff;
			if(a == t[0] && b == t[1] && c == t[2]) return d[a][b][c]; //q1 reach target, search finished.
			for(int i = 0; i < deg[a]; i++){
				int a2 = G[a][i];
				for(int j = 0; j < deg[b]; j++){
					int b2 = G[b][j];
					if(conflict(a, a2, b, b2)) continue;
					for(int k = 0; k < deg[c]; k++){
						int c2 = G[c][k];
						if(conflict(a, a2, c, c2)||conflict(b, b2, c, c2)||(d[a2][b2][c2] != -1)) continue;
						d[a2][b2][c2] = d[a][b][c] + 1;
						if(d2[a2][b2][c2] != -1) return d[a2][b2][c2] + d2[a2][b2][c2];  //has been visited by q2, search finished.
						//else if(d[a2][b2][c2] != -1) continue;     //been visited by q1, not q2, ignore this node.
						next.push(ID(a2, b2, c2));//not visited by q1 and q2, push into queue.
					}
				}
			}
		}
		while(!next.empty()){
			q.push(next.front());
			next.pop();
		}

		//for the second queue
		while(!q2.empty()){
			int u = q2.front(); q2.pop();
			int a = (u>>16)&0xff, b = (u>>8)&0xff, c = u&0xff;
			if(a == s[0] && b == s[1] && c == s[2]) return d2[a][b][c]; //q2 reach target, search finished.
			for(int i = 0; i < deg[a]; i++){
				int a2 = G[a][i];
				for(int j = 0; j < deg[b]; j++){
					int b2 = G[b][j];
					if(conflict(a, a2, b, b2)) continue;
					for(int k = 0; k < deg[c]; k++){
						int c2 = G[c][k];
						if(conflict(a, a2, c, c2)||conflict(b, b2, c, c2)||(d2[a2][b2][c2] != -1)) continue;
						d2[a2][b2][c2] = d2[a][b][c] + 1;
						if(d[a2][b2][c2] != -1) return d2[a2][b2][c2] + d[a2][b2][c2];  //has been visited by q, search finished.
						//else if continue;     //been visited by q2, not q1, ignore this node.
						next.push(ID(a2, b2, c2));	//not visited by q2 and q1, push into queue.
					}
				}
			}
		}
		while(!next.empty()){
			q2.push(next.front());
			next.pop();
		}
	}
	return -1;
}

int main(){
#ifdef LOCAL
	freopen("UVa.1601.in", "r", stdin);
	freopen("UVa.1601.out", "w", stdout);
#endif
	int w, h, n;
	while(scanf("%d%d%d\n", &w, &h, &n) == 3 && w){
		char maze[maxs][maxs];
		for(int i = 0; i < h; i++) fgets(maze[i], maxs, stdin);
		
		//extract empty cell
		int cnt = 0, x[maxn], y[maxn], id[maxs][maxs];
		for(int i = 0; i < h; i++) for(int j = 0; j < w; j++){
			if(maze[i][j] != '#'){
				x[cnt] = i; y[cnt] = j; id[i][j] = cnt;
				if(islower(maze[i][j])) s[maze[i][j] - 'a'] = cnt;
				else if(isupper(maze[i][j])) t[maze[i][j] - 'A'] = cnt;
				cnt++;
			}
		}

		//build a graph for empty cell
		for(int i = 0; i < cnt; i++){
			deg[i] = 0;
			for(int j = 0; j < 5; j++){
				int nx = x[i] + dx[j], ny = y[i] + dy[j];
				if(maze[nx][ny] != '#') G[i][deg[i]++] = id[nx][ny];
			}
		}

		if(n <= 2) {deg[cnt] = 1; G[cnt][0] = cnt; s[2] = t[2] = cnt++;}
		if(n <= 1) {deg[cnt] = 1; G[cnt][0] = cnt; s[1] = t[1] = cnt++;}

		printf("%d\n", bfs());
	}
	return 0;
}

