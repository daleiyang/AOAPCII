#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;

const int maxn = 26;
int G[maxn][maxn], d[maxn], in[maxn], out[maxn], cnt;
char w[1000+5];

void dfs(int u){
	d[u] = 1;
	for(int v = 0; v < maxn; v++){
		if((G[u][v] == 1 ||G[v][u] == 1) && d[v] == 0){
			dfs(v);
		}
	}
}

int main(){
#ifdef LOCAL
		freopen("UVa.10129.in", "r", stdin);
		freopen("UVa.10129.out", "w", stdout);
#endif

	int n, m, u, v;
	scanf("%d", &n);
	while(n--){
		memset(G, 0, sizeof(G));
		memset(d, 0, sizeof(d));
		memset(in, 0, sizeof(in));
		memset(out, 0, sizeof(out));
		cnt = 0;
		scanf("%d", &m);
		while(m--){
			scanf("%s", w);
			u = w[0]-'a'; v = w[strlen(w)-1]-'a';
			in[u]++; out[v]++;
			G[u][v] = G[v][u] = 1;
		}
		for(int i = 0; i < maxn; i++){
			if((in[i] != 0 || out[i] != 0) && d[i] == 0){
				dfs(i);
				cnt++;
			}
		}
		if(cnt > 1) {
			printf("The door cannot be opened.\n");
			continue;
		}
		cnt = 0; bool f = true; int sum = 0;
		for(int i = 0; i < maxn; i++){
			if(in[i] != out[i]){
				if(abs(in[i]-out[i]) !=1){
					f = false; 
					break;
				}
				sum += in[i]-out[i];
				cnt++;
			}
		}
		if(!f || !(cnt ==0 || cnt == 2) || sum != 0){
			printf("The door cannot be opened.\n");
			continue;
		}
		printf("Ordering is possible.\n");
	}
	return 0;
}

