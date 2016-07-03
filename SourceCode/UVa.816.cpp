#include<cstdio>
#include<queue>
#include<vector>
#include<cstring>
using namespace std;

const char * dirs = "NESW";
const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0 , 1, 0, -1};
const char * turns = "FLR";
const int maxn = 10;

int d[maxn][maxn][4];			// minimum length for each node
int has_edge[maxn][maxn][4][3];	// acceptable turn for each direction, x and y
char name[20+1], op[4+1], sdir[2], maze[99]; 
int r, c, r0, c0, r1, c1, r2, c2;

struct Node{
	int r, c, dir;
	Node(int r = 0, int c = 0, int dir = 0):r(r), c(c), dir(dir){}
};
Node p[maxn][maxn][4];	//parent node for each direction, x and y

int dir_id(char c){return strchr(dirs, c) - dirs;}
int turn_id(char c){return strchr(turns, c) - turns;}

Node walk(const Node & u, int turn){
	int dir = u.dir;
	if(turn == 1) dir = (dir+3)%4;
	if(turn == 2) dir = (dir+1)%4;
	return Node(u.r + dx[dir], u.c + dy[dir], dir);
}

void print(){
	for(int i = 1 ; i < maxn; i++)
		for(int j = 1; j < maxn; j++)
			for(int d = 0 ; d < 4; d++)
				for(int t = 0; t < 3; t++)
					printf("R:%d C:%d D:%d T:%d Value:%d\n", i, j, d, t, has_edge[i][j][d][t]);
}

void print_ans(Node u){
	vector<Node> nodes;
	for(;;){
		nodes.push_back(u);
		if(d[u.r][u.c][u.dir] == 0) break;
		u = p[u.r][u.c][u.dir];
	}
	nodes.push_back(Node(r0, c0, dir_id(sdir[0])));

	int cnt = 0;
	for(int i = nodes.size()-1; i>=0 ; i--){
		if(cnt%10 == 0) printf(" ");
		printf(" (%d,%d)", nodes[i].r, nodes[i].c);
		if(++cnt%10 == 0) printf("\n");
	}
	if(nodes.size()%10 != 0) printf("\n");
}

bool inside(int r, int c){
	return (r > 0) && (r < maxn) && (c > 0) && (c < maxn); 
}

void solve(){
	queue<Node> q;
	int dir = dir_id(sdir[0]);
	r1 = r0 + dx[dir];
	c1 = c0 + dy[dir];
	Node u(r1, c1, dir);
	d[u.r][u.c][u.dir] = 0;
	q.push(u);
	while(!q.empty()){
		Node u = q.front(); q.pop();
		if((u.r == r2) && (u.c == c2)) {print_ans(u); return;}
		for(int i = 0; i < 3; i++){
			Node v = walk(u, i);
			if(has_edge[u.r][u.c][u.dir][i] && inside(v.r, v.c) 
				&& d[v.r][v.c][v.dir] < 0){
				d[v.r][v.c][v.dir] = d[u.r][u.c][u.dir] + 1;
				p[v.r][v.c][v.dir] = u;
				q.push(v);
			}
		}
	}
	printf("  No Solution Possible\n");
}

int main(){
#ifdef LOCAL
		freopen("UVa.816.in", "r", stdin);
		freopen("UVa.816.out", "w", stdout);
#endif
	while(scanf("%s", maze) && strcmp(maze, "END") != 0){
		printf("%s\n", maze);
		memset(d, -1, sizeof(d));
		memset(p, 0, sizeof(p));
		memset(has_edge, 0 , sizeof(has_edge));
		scanf("%d%d%s%d%d", &r0, &c0, sdir, &r2, &c2);
		while(scanf("%d", &r) == 1 && r){
			scanf("%d", &c);
			while(scanf("%s", op) == 1 && strcmp(op, "*") != 0){
				for(unsigned int i = 1; i < strlen(op); i++){
					has_edge[r][c][dir_id(op[0])][turn_id(op[i])] = 1;
				}
			}
		}
		//print();
		solve();
	}
	return 0;
}

