#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int N = 5, M = 100;

int n, c, w[N], jump[M], ans;

bool judge(int * s, int k){
	for(int i = 0; i < N; i++){
		if((s[i]>>k)&w[i]) return false;
	}
	return true;
}

void init(){
	memset(w, 0 ,sizeof(w));
	char s[M];
	for(int i = 0; i < N; i++){
		scanf("%s", s);
		for(int j = 0; j < n; j++)
			if(s[j] == 'X') 
				w[i] |= (1<<j);
	}
	c = 0;
	for(int i = 0; i <= n; i++) 
		if(judge(w, i)) 
			jump[c++] = i;
	ans = n * 10;
}

void dfs(int * s, int d, int sum){
	if((sum + jump[0]*(10 - d)) > ans) return;
	if(d == 10){ans = min(ans, sum); return;}
	for(int i = 0; i < c; i++){
		if(judge(s, jump[i])){
			int p[N];
			for(int j = 0; j < N; j++)
				p[j] = (s[j]>>jump[i])^w[j];
			dfs(p, d + 1, sum + jump[i]);
		}
	}
}

int main(){
#ifdef LOCAL
		freopen("UVa.690.in", "r", stdin);
		freopen("UVa.690.out", "w", stdout);
#endif
	while(scanf("%d", &n) == 1 && n){
		init();
		dfs(w, 1, n);
		printf("%d\n", ans);
	}
	return 0;
}

