#include<cstdio>
#include<cstring>
using namespace std;

typedef int State[9];
const int maxstate = 1000000;
State st[maxstate], goal;
int dist[maxstate];

const int dx[] = {-1, 1, 0,  0};
const int dy[] = { 0, 0, 1, -1};

int vis[362880], factorial[9];
void init_look_up_table(){
	factorial[0] = 1;
	for(int i = 1; i < 9; i++) factorial[i] = factorial[i-1] * i;
}

int try_to_insert(int s){
	int code = 0;
	for(int i = 0; i < 9; i++){
		int cnt = 0;
		for(int j = i + 1; j < 9; j++){
			if(st[s][j] < st[s][i]) cnt++;
		}
		code += factorial[8-i] * cnt;
	}
	if(vis[code]) return 0;
	return vis[code] = 1;
}

int bfs(){
	init_look_up_table();
	int front = 1, rear = 2;
	dist[1] = 0;
	while(front < rear){
		State& s = st[front];
		if(memcmp(goal, s, sizeof(s)) == 0) return front;
		int z;
		for(int i = 0; i < 9; i++) if(!s[i]) {z = i; break;}
		int x = z/3, y = z%3;
		for(int i = 0; i < 4; i++){
			int newx = x + dx[i];
			int newy = y + dy[i];
			int newz = newx * 3 + newy;
			if(newx >=0 && newx <3 && newy >= 0&& newy < 3){
				State& t = st[rear];
				memcpy(t, s, sizeof(s));
				t[newz] = s[z];
				t[z] = s[newz];
				dist[rear] = dist[front] + 1;
				if(try_to_insert(rear)) rear++;
			}
		}
		front++;
	}
	return 0;
}

int main(){
#ifdef LOCAL
	freopen("7.5.in", "r", stdin);
	freopen("7.5.out", "w", stdout);
#endif
	for(int i = 0; i < 9; i++) scanf("%d", &st[1][i]);
	for(int i = 0; i < 9; i++) scanf("%d", &goal[i]);
	int ans = bfs();
	if(ans > 0) printf("%d\n", dist[ans]);
	else printf("-1\n");
	return 0;
}

