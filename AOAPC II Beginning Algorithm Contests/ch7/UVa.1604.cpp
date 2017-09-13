//http://blog.csdn.net/auto_ac/article/details/8790113
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;
/*
0 1 2
3 4 5
6 7 8
*/
const int maxn = 5000007;

struct node{
	int state, dep, pos;
	node(){};
	node(int state, int dep, int pos):state(state), dep(dep), pos(pos){};
}s;
queue<node> Q, q;

//hash
struct E{
	int next, w;
}e[maxn];
int head[maxn], tot;

void init(){
	memset(head, -1, sizeof(head));
	tot = 0;
}

int find(int n){
	int h = n % maxn;
	int u = head[h];
	
	while(u >= 0){
		if(e[u].w == n) return u;
		u = e[u].next;
	}
	e[tot].w = n;
	e[tot].next = head[h];
	head[h] = tot++;
	return tot-1;
}

bool vis[maxn], mark[maxn];

/*
states:          0   1   2   3   4   5    6 
up & down  : E  W  W  B  B   R   R
front & back:     R   B   R  W  W  B
*/
char ch[11];
int emp;

void dfs(int dep, int state){
	if(dep == 9){
		node w;
		q.push( w = node(state, 0, emp));
		int tp = find(state);
		mark[tp] = 1;
		return;
	}
	if(ch[dep] == 'E'){
		dfs(dep+1, state<<3);
		return;
	}
	int x, y;
	if(ch[dep] == 'W') {x = 1; y = 2;}
	else if(ch[dep] == 'B') {x = 3; y = 4;}
	else {x = 5; y = 6;}
	dfs(dep+1, (state<<3)|x);
	dfs(dep+1, (state<<3)|y);
}

int mp1[] = {0, 5, 4, 6, 2, 1, 3}; //up and down
int mp2[] = {0, 3, 6, 1, 5, 4, 2}; //left and right
int get(int a, int f){
	return  (((a>>(f*3+2))&1)<<2) |
			(((a>>(f*3+1))&1)<<1) |
			((a>>(f*3))&1);
}

void update(node & v, int op){
	int f;
	if(op == 0){ //down
		if(v.pos+3 < 9){
			f = v.pos+3;
			int tp = get(v.state, 8-f);
			v.state = (v.state ^ (tp<<((8-f)*3))) | (mp1[tp]<<((8-f+3)*3));
			v.dep++; v.pos = f;
		}
	}
	if(op == 1){ // up
		if(v.pos-3 >= 0){
			f = v.pos-3;
			int tp = get(v.state, 8-f);
			v.state = (v.state ^ (tp<<((8-f)*3))) | (mp1[tp]<<((8-f-3)*3));
			v.dep++; v.pos = f;
		}
	}
	if(op == 2){ //right
		if(v.pos != 2 && v.pos != 5 && v.pos != 8){
			f = v.pos+1;
			int tp = get(v.state, 8-f);
			v.state = (v.state ^ (tp<<((8-f)*3))) | (mp2[tp]<<((8-f+1)*3));
			v.dep++; v.pos = f;
		}
	}
	if(op == 3){ //left
		if(v.pos != 0 && v.pos != 3 && v.pos != 6){
			f = v.pos-1;
			int tp = get(v.state, 8-f);
			v.state = (v.state ^ (tp<<((8-f)*3))) | (mp2[tp]<<((8-f-1)*3));
			v.dep++; v.pos = f;
		}
	}
}

int bfs(){
	int i, t, k, j = 0;
	for(i = 0; i <= 20; i++){
		node u;
		while(!Q.empty() && Q.front().dep == i){
			u = Q.front(); Q.pop();
			for(k = 0; k < 4; k++){
				node v = u; update(v, k);
				t = find(v.state);
				if(!vis[t]){
					vis[t] = 1;
					if(mark[t]) return i+j+1;
					Q.push(v);
				}
			}
		}
		while(!q.empty() && q.front().dep == j && j < 9){
			u = q.front(); q.pop();
			for(k = 0; k < 4; k++){
				node v = u; update(v, k);
				t = find(v.state);
				if(!mark[t]){
					mark[t] = 1;
					if(vis[t]) return i+j+2;
					q.push(v);
				}
			}
		}
		if(j < 9) j++;
	}
	return -1;
}

int main(){
#ifdef LOCAL
	freopen("UVa.1604.in", "r", stdin);
	freopen("UVa.1604.out", "w", stdout);
#endif
	int i, j, c, r;
	while(scanf("%d%d", &c, &r) == 2 && c){
		while(!Q.empty()) Q.pop();
		while(!q.empty()) q.pop();
		init();
		memset(vis, 0, sizeof(vis));
		memset(mark, 0, sizeof(mark));
		s.state = 0; s.dep = 0; s.pos = (r-1)*3+c-1;
		for(i = 1; i <= 3; i++) for(j = 1; j <= 3; j++){
			s.state <<= 3;
			if(i == r && j == c) continue;
			s.state |= 1;
		}
		Q.push(s);
		int tp = find(s.state);
		vis[tp] = 1;
		char c[11];
		for(i = 0; i < 3; i++) for(j = 0; j < 3; j++){
			scanf("%s", c);
			ch[i*3+j] = c[0];
			if(c[0] == 'E') emp = i*3+j;
		}
		// for 0 step case
		for(i = 0; i < 9; i++){
			if(i != s.pos && ch[i] == 'W') continue;
			else if(i == s.pos && ch[i] == 'E') continue;
			else break;
		}
		if(i == 9) {printf("0\n"); continue;}
		dfs(0, 0);
		printf("%d\n", bfs());
	}
	return 0;
}

