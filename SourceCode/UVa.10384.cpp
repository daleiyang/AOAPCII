#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<ctime>
using namespace std;

const int maxn = 100000;

typedef long long LL;

struct node{
	int r, c, idx, pidx, di;
	node(int r = 0, int c = 0, int idx = 0, int pidx = 0, int di = 0):r(r), c(c), idx(idx), pidx(pidx), di(di){};
}n[maxn];

//hash
struct E{
	int next;
	LL w;
}e[maxn];

int head[maxn], tot;

void init(){
	memset(head, -1, sizeof(head));
	tot = 0;
}

int find(long long n){
	int h = n % maxn;
	int u = head[h];
	
	while(u >= 0){
		if(e[u].w == n) return u;
		u = e[u].next;
	}
	e[tot].w = n;
	e[tot].next = head[h];
	head[h] = tot++;
	return tot - 1;
}

int vis[maxn];

int north(int r, int c){return (6+7)*r+c;}
int south(int r, int c){return (6+7)*(r+1)+c;}
int west(int r, int c){return (6+7)*r+6+c;}
int east(int r, int c){return (6+7)*r+6+c+1;}

bool subcheck(int idx, LL st){
	return ((st>>idx)&1) == 0;
}

int check(int r, int c, LL st){
	int idx;
	if(r == 0) {
		idx = north(r, c); 
		if(subcheck(idx, st)) return 0;
	}
	if(c == 0) {
		idx = west(r, c);  
		if(subcheck(idx, st)) return 2;
	}
	if(c == 5) {
		idx = east(r, c);  
		if(subcheck(idx, st)) return 3;
	}
	if(r == 3) {
		idx = south(r, c); 
		if(subcheck(idx, st)) return 1;
	}
	return -1;
}

char D[4] = {'N', 'S', 'W', 'E'};

void print(int idx, int f){
	vector<int> v;
	v.push_back(f);
	int u = idx;
	while(n[u].pidx != -1) {
		v.push_back(n[u].di);
		u = n[u].pidx;
	}
	for(int i = v.size()-1; i >= 0;  i--){
		printf("%c", D[v[i]]);
	}
	printf("\n");
}

int dc[4] = { 0, 0, -1, 1};
int dr[4] = {-1, 1,  0, 0};

void solve(int r, int c, LL st){
	queue<int> q;
	memset(vis, 0, sizeof(vis));
	int idx = find(st);
	vis[idx] = 1;
	n[idx] = node(r, c, idx, -1, -1);
	q.push(idx);
	while(!q.empty()){
		node temp = n[q.front()]; q.pop();
		int f = check(temp.r, temp.c, e[temp.idx].w);
		if(f != -1) {
			print(temp.idx, f);
			return;
		}
		for(int i = 0; i < 4; i++){
			int nr = temp.r + dr[i];
			int nc = temp.c + dc[i];
			if(nr >= 0 && nr < 4 && nc >= 0 && nc < 6){
				int idx, idxn;
				if(i == 0){
					idx = north(temp.r, temp.c);
					idxn = north(nr, nc);
				}
				else if(i == 1){
					idx = south(temp.r, temp.c);
					idxn = south(nr, nc);
				}
				else if(i == 2){
					idx = west(temp.r, temp.c);
					idxn = west(nr, nc);
				}
				else if(i == 3){
					idx = east(temp.r, temp.c);
					idxn = east(nr, nc);
				}
				if(((e[temp.idx].w>>idx)&1) == 0){
						LL stn = (((LL)1<<58)-1)&e[temp.idx].w; //clean r, c 
						stn |= (LL)nc << 58; 		 //setup new r
						stn |= (LL)nr << 61;		 //setup new c
						int nidx = find(stn);
						if(!vis[nidx]){
							vis[nidx] = 1;
							n[nidx] = node(nr, nc, nidx, temp.idx, i);
							q.push(nidx);
						}
				}else if(((e[temp.idx].w>>idx)&1) == 1 && ((e[temp.idx].w>>idxn)&1) == 0){
						LL stn = e[temp.idx].w;
						stn ^= (LL)1<<idx;  //push wall
						stn ^= (LL)1<<idxn; //push wall
						
						stn = (((LL)1<<58)-1)&stn; //clean r, c 
						stn |= (LL)nc << 58; 	  //setup new r
						stn |= (LL)nr << 61;      //setup new c
						int nidx = find(stn);
						if(!vis[nidx]){
							vis[nidx] = 1;
							n[nidx] = node(nr, nc, nidx, temp.idx, i);
							q.push(nidx);
						}
				}
			}
		}
	}
}

int main(){
#ifdef LOCAL
	freopen("UVa.10384.in", "r", stdin);
	freopen("UVa.10384.out", "w", stdout);
#endif
	int r, c;
	while(scanf("%d%d", &c, &r) == 2 && c){
		init();
		LL st = 0; 
		r--; c--;
		int temp;
		for(int i = 0; i < 4; i++) //set bits from 0 to 57 representing wall
			for(int j = 0; j < 6; j++){
				scanf("%d", &temp);
				if(2 & temp) st |= (LL)1 << north(i, j);
				if(8 & temp) st |= (LL)1 << south(i, j);
				if(1 & temp) st |= (LL)1 << west(i, j);
				if(4 & temp) st |= (LL)1 << east(i, j);
			}
		st |= (LL)c << 58;  //set bit 58, 59, 60 which represent start columns
		st |= (LL)r << 61;  //set bit 61, 62 which represent start rows
		solve(r, c, st);
	}
	//printf("Time used:%.4f", (double)clock()/CLOCKS_PER_SEC);
	return 0;
}

