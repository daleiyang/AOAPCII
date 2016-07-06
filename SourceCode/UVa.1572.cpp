#include<cstdio>
#include<cstring>

const int maxn = 52;

int G[maxn][maxn];
int c[maxn];
char s[9];

int ID(char a1, char a2){
	return (a1-'A')*2+ (a2 == '+' ? 0:1);
}

void connect(char a1, char a2, char b1, char b2){
	if(a1 == '0' || b1 == '0') return;
	int u = ID(a1, a2)^1, v = ID(b1, b2);
	G[u][v] = 1;
}

bool dfs(int u){
	c[u] = -1;
	for(int v = 0; v < maxn; v++){
		if(G[u][v]){
			if(c[v] < 0) return true;
			else if(!c[v] && dfs(v)) return true;
		}
	}
	c[u] = 1;
	return false;
}

bool find_cycle(){
	memset(c, 0, sizeof(c));
	for(int i = 0; i < maxn; i++){
		if(!c[i] && dfs(i)) return true;
	}
    return false;
}

int main(){
#ifdef LOCAL
		freopen("UVA.1572.in", "r", stdin);
		freopen("UVA.1572.out", "w", stdout);
#endif
	int n;
	while(scanf("%d", &n) == 1){
		memset(G, 0, sizeof(G));
		while(n--){
			scanf("%s", s);
			for(int i = 0; i < 4; i++){
				for(int j = 0; j < 4; j++){
					if(i != j){
						connect(s[i*2], s[i*2+1], s[j*2], s[j*2+1]);
					}
				}
			}
		}
		if(find_cycle()) printf("unbounded\n");
		else printf("bounded\n");
	}
	return 0;
}

