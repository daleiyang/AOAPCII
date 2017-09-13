//http://www.redblobgames.com/pathfinding/a-star/introduction.html
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cctype>
//#include<cmath>
#include<queue>
#include<vector>
#include<ctime>
using namespace std;

const int maxs = 20;
const int maxn = 150;

int dx[] = {0, 1, -1, 0, 0};
int dy[] = {0, 0, 0, 1, -1};
int s[3], t[3]; //starting , ending position for each ghost
int deg[maxn], G[maxn][5]; //target cell for each move, including "no move"
int x[maxn], y[maxn], id[maxs][maxs];

struct Node{
	int id;
	int priority;
	Node(int id, int priority):id(id), priority(priority){}
	bool operator < (const Node & b) const{
		return priority > b.priority;
	}
};

int ID(int a, int b, int c){
    return (a<<16)|(b<<8)|c;
}

bool conflict(int a, int a2, int b, int b2){
    return (a2 == b2) || (a == b2 && b == a2);
}

int d[maxn][maxn][maxn]; //distance from starting state
int heuristic[maxn][3]; //heuristic value for each empty cell to A,B,C position

/*
int heuristic(int a, int b){
	return abs(x[a] - x[b]) + abs(y[a] - y[b]);
}
*/

int bfs(){
    priority_queue<Node> pq;
    memset(d, -1 ,sizeof(d));
	
	d[s[0]][s[1]][s[2]] = 0;
    pq.push(Node(ID(s[0], s[1], s[2]), 0));

    while(!pq.empty()){
        Node n = pq.top(); pq.pop();
        int a = (n.id>>16)&0xff, b = (n.id>>8)&0xff, c = n.id&0xff;
        if(a == t[0] && b == t[1] && c == t[2]) return d[a][b][c];
        for(int i = 0; i < deg[a]; i++){
            int a2 = G[a][i];
            for(int j = 0; j < deg[b]; j++){
                int b2 = G[b][j];
                if(conflict(a, a2, b, b2)) continue;
                for(int k = 0; k < deg[c]; k++){
                    int c2 = G[c][k];
                    if(conflict(a, a2, c, c2)) continue;
                    if(conflict(b, b2, c, c2)) continue;
					int new_cost = d[a][b][c] + 1;
					if(d[a2][b2][c2] == -1 || new_cost < d[a2][b2][c2]){
						d[a2][b2][c2] = new_cost;
						int pri = new_cost + max(max(heuristic[a2][0], heuristic[b2][1]), heuristic[c2][2]);
						pq.push(Node(ID(a2, b2, c2), pri));
					}
                }
            }
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
        int cnt = 0;
        for(int i = 0; i < h; i++) for(int j = 0; j < w; j++){
            if(maze[i][j] != '#'){
                x[cnt] = i; y[cnt] = j; id[i][j] = cnt;
                if(islower(maze[i][j])) s[maze[i][j] - 'a'] = cnt;
                else if(isupper(maze[i][j])) t[maze[i][j] - 'A'] = cnt;
                cnt++;
            }
        }

		for(int i = 0; i < cnt; i++){
			for(int j = 0; j < 3; j++){
				heuristic[i][j] = abs(x[i] - x[t[j]]) + abs(y[i] - y[t[j]]);
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
	//printf("%.2f\n", (double)clock()/CLOCKS_PER_SEC);
    return 0;
}

