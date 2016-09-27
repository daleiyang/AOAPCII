#include<cstdio>
#include<cstring>
#include<algorithm>
#include<ctime>
using namespace std;

const int maxn = 4000 + 5;
const int M = 10000007;
int A[maxn], B[maxn], C[maxn], D[maxn];

//hash
struct E{
	int next, w, cnt;
}e[M];
int head[M], tot;

void init(){
	memset(head, -1, sizeof(head));
	tot = 0;
}

void insert(int n){
	int h = abs(n)%M;
	int u = head[h];

	while(u >= 0){
		if(e[u].w == n) {
			e[u].cnt++;
			return;
		}
		u = e[u].next;
	}
	e[tot].w = n;
	e[tot].cnt = 1;
	e[tot].next = head[h];
	head[h] = tot++;
}

int find(int n){
	int h = abs(n)%M;
	int u = head[h];

	while(u >= 0){
		if(e[u].w == n) {
			return e[u].cnt;
		}
		u = e[u].next;
	}
	return 0;
}

bool vis[M];

int main(){
#ifdef LOCAL
	freopen("UVa.1152.in", "r", stdin);
	freopen("UVa.1152.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	while(T--){
		int n;
		scanf("%d", &n);
		for(int i = 0; i < n; i++){
			scanf("%d%d%d%d", &A[i], &B[i], &C[i], &D[i]);
		}
		init();
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				insert(A[i]+B[j]);
		int cnt = 0;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				cnt += find(-C[i]-D[j]);
		printf("%d\n", cnt);
		if(T) printf("\n");
	}
	//printf("Time usaged: %.4f", (double)clock()/CLOCKS_PER_SEC);
	return 0;
}

