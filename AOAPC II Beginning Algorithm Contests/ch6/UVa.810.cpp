#include<cstdio>
#include<cstring>
using namespace std;

int opposite[7] = {0, 6, 5, 4, 3, 2, 1}; // 1->6; 6->1; 2->5; 5->2; 3->4; 4->3;

int rotate[7][4] = {0 ,0 ,0, 0,
					2, 4, 5, 3, //take 1 as axis, facing 1, clockwise sequence for other sides. 2, 4, 5, 3
					3, 6, 4, 1, //facing 2
					1, 5, 6, 2, //facing 3
					1, 2, 6, 5, //facing 4
					1, 4, 6, 3, //facing 5
					2, 3, 5, 4};//facing 6

int num2idx[7][7] = { 0,  0,  0,  0,  0,  0,  0,
					 -1, -1,  0,  3,  1,  2, -1, //num2idx[1][2] = 0; [1][3] = 3; [1][4]=1; [1][5]=2, the value is index number in rotate[1]. A helper to find out index number in rotate[1] for number 2, 4, 5, 3
					 -1,  3, -1,  0,  2, -1,  1, //facing 2, idx in roate[2]
					 -1,  0,  3, -1, -1,  1,  2, //facing 3, idx in roate[3]
					 -1,  0,  1, -1, -1,  3,  2, //facing 4, idx in roate[4]
					 -1,  0, -1,  3,  1, -1,  2, //facing 5, idx in roate[5]
					 -1, -1,  0,  1,  3,  2, -1};//facing 6, idx in roate[6]
char name[21];
int r, c, sr, sc, top, face, vidx;
int G[11][11], vis[11][11][7][7];//row, column, top, face
int dx[4] = {  0,  0, -1,  1};
int dy[4] = { -1,  1,  0,  0};

struct state{
	int x, y, top, face, pre;
	state(int x = 0, int y =0, int top = 0, int face = 0, int pre = 0):x(x), y(y), top(top), face(face), pre(pre){}
} v[1000];
int q[1000], front, rear;

void print(int u){
	int trace[1000], idx = 0;
	for(;;){
		trace[idx++] = u;
		u = v[u].pre;
		if (u == -1){break;}
	}
	int cnt = 0;
	for(int i = idx-1; i >= 0; i--){
		if(!cnt) {printf("\n  (%d,%d)", v[trace[i]].y, v[trace[i]].x);}
		else if((cnt)%9 == 0) printf(",\n  (%d,%d)", v[trace[i]].y, v[trace[i]].x);
		else{printf(",(%d,%d)", v[trace[i]].y, v[trace[i]].x);}
		cnt++;
	}
	printf("\n");
}

void bfs(){
	//vis[sc][sr][top][face] = 1; //must remove this lline to get AC. because it could possible go back to initial position with the same top, face of the initial state.
	vidx = 0;
	v[vidx++] = state(sc, sr, top, face, -1);
	q[0] = 0;
	front = 0; rear = 0;
	bool f = false;
	while(front <= rear){
		int t = q[front]; front++;
		if(v[t].x == sc && v[t].y == sr && f){
			print(t);
			return;
		}
		if(v[t].x == sc && v[t].y == sr && !f) f = true;
		for(int i = 0; i < 4; i++){
			int x = v[t].x + dx[i];
			int y = v[t].y + dy[i];
			if(x >= 1 && x <= c && y >=1 && y <= r && G[x][y]){ //in the valid square
				if(v[t].top == G[x][y] || G[x][y] == -1){ //could move to new square
					int ntop, nface;
					if(i == 0){ //up
						ntop = v[t].face;
						nface = opposite[v[t].top];
					}else if(i == 1){ //down
						ntop = opposite[v[t].face];
						nface = v[t].top;
					}
					else{
						int idx = num2idx[v[t].face][v[t].top];
						if(i == 2){//left 
							ntop = rotate[v[t].face][(idx+1)%4];
						}else if(i == 3){//right
							ntop = rotate[v[t].face][(idx+3)%4];							
						}
						nface = v[t].face;
					}
					if(!vis[x][y][ntop][nface]){
						vis[x][y][ntop][nface] = 1;
						v[vidx++] = state(x, y, ntop, nface, t);
						q[++rear] = vidx - 1;
					}
				}
			}
		}
	}
	printf("\n  No Solution Possible\n");
}

int main(){
#ifdef LOCAL
	freopen("UVa.810.in", "r", stdin);
	freopen("UVa.810.out", "w", stdout);
#endif
	while(scanf("%s", name) == 1 && strcmp(name, "END")){
		memset(vis, 0, sizeof(vis));
		scanf("%d%d%d%d%d%d", &r, &c, &sr, &sc, &top, &face);
		for(int i = 1; i <= r; i++){
			for(int j = 1; j <= c; j++){
				scanf("%d", &G[j][i]);
			}
		}	
		printf("%s", name);
		bfs();
	}
	return 0;
}

