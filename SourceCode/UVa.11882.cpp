#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
using namespace std;

const int maxn = 15+5, maxm = 30+5;

int r, c, cnt, x[maxm], y[maxm], dig[maxm], G[maxm][maxm], num[maxm], id[maxn][maxn], vis[maxm], vis2[maxm];
int A[maxm], B[maxm], idxB, q[maxm];
int dx[4] = {0,  0, 1, -1};
int dy[4] = {1, -1, 0,  0};

char maze[maxn][maxn];

bool prune(int curr){
	memcpy(vis2, vis, sizeof(vis2));
	int len = 0;
	for(int i = 0; i < cnt; i++){
		if(!vis2[i]){
			int nn = 0;
			vis2[i] = 1;
			int front = 0, rear = 1;
			q[front] = i;
			while(front < rear){
				int now = q[front];
				nn++;
				for(int j = 0; j < dig[now]; j++){
					if(!vis2[G[now][j]]){
						vis2[G[now][j]] = 1;
						q[rear++] = G[now][j];
					}
				}
				front++;
			}
			len = max(len, nn); //leverage bfs to find the max number in remaining non-visited space.
		}
	}
	bool ans = false;
	if(len + curr < idxB) {
		ans = true;
	}
	else if(len + curr == idxB){ //prune the candidate with same potential lenght. 
		for(int i = 0; i <= curr; i++){
			if(A[i] == B[i]) continue;
			if(A[i] > B[i])  break;
			if(A[i] < B[i])  {ans = true; break;}
		}
	}
	return ans;
}

void dfs(int d, int cnt){
	A[d] = num[cnt];
	if(prune(d)) return;
	bool f = false;
	for(int i = 0; i < dig[cnt]; i++){
		if(!vis[G[cnt][i]]){
			vis[G[cnt][i]] = 1;
			dfs(d+1, G[cnt][i]);
			vis[G[cnt][i]] = 0;
			f = true;
		}
	}
	if(!f){
		if(d > idxB){
			for(int i = 0; i <= d; i++){
				B[i] = A[i];
			}
			idxB = d;
		}
		if(d == idxB){
			int t = 0;
			while(A[t] == B[t]) t++;
			if(A[t] > B[t]){
				for(int i = t; i <= d; i++){
					B[i] = A[i];
				}
			}
		}
	}
}

int main(){
#ifdef LOCAL
	freopen("UVa.11882.in", "r", stdin);
	freopen("UVa.11882.out", "w", stdout);
#endif
	while(scanf("%d %d", &r, &c) == 2 && r){
		memset(id, -1, sizeof(id));
		memset(G, 0, sizeof(G));
		memset(vis, 0, sizeof(vis));
		idxB = 0; B[0] = 0;
		fgets(maze[0], maxn, stdin); // remove the new line char.
		for(int i = 0; i < r; i++){fgets(maze[i], maxn, stdin);}
		
		cnt = 0;
		for(int i = 0;  i < r; i++) for(int j = 0; j < c; j++){
			if(maze[i][j] != '#'){
				num[cnt] = maze[i][j] - '0';
				x[cnt] = i; y[cnt] = j;
				id[i][j] = cnt;
				cnt++;
			}
		}
		for(int i = 0; i < cnt; i++){
			int tx, ty;
			dig[i] = 0;
			for(int j = 0; j < 4; j++){
				tx = x[i] + dx[j];
				ty = y[i] + dy[j];
				if(tx >= 0 && tx < r && ty >= 0 && ty < c && maze[tx][ty] != '#'){
					G[i][dig[i]++] = id[tx][ty];
				}
			}
		}
		for(int i = 0; i < cnt; i++){
			vis[i] = 1;
			dfs(0, i);
			vis[i] = 0;
		}
		for(int i = 0; i <=idxB; i++){
			printf("%d", B[i]);
		}
		printf("\n");
	}
	//printf("Time used:%.2f", (double)clock()/CLOCKS_PER_SEC);
	return 0;
}

