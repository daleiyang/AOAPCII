#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 25;
int isp[maxn*2], A[maxn], vis[maxn], n;

int is_prime(int x){
	for(int i = 2; i*i <= x; i++){
		if(x % i == 0) return 0;
	}
	return 1;
}

void dfs(int cur){
	if(cur == n && isp[A[n-1]+A[0]]){
		for(int i = 0; i < n; i++) {
			if(i == 0) printf("%d", A[i]);
			else printf(" %d", A[i]);
		}
		printf("\n");
	}else{
		for(int i = 2; i <= n; i++){
			if(!vis[i] && isp[A[cur-1]+i]){
				A[cur] = i;
				vis[i] = 1;
				dfs(cur+1);
				vis[i] = 0;
			}
		}
	}
}

int main(){
#ifdef LOCAL
	freopen("UVa.524.in", "r", stdin);
	freopen("UVa.524.out", "w", stdout);
#endif
	for(int i = 2; i < maxn*2; i++){
		isp[i] = is_prime(i);
	}
	int kase = 0;
	while(scanf("%d", &n) == 1){
		if(kase) printf("\n");
		memset(vis, 0, sizeof(vis));
		printf("Case %d:\n", ++kase);
		A[0] = 1;
		dfs(1);
	}
	return 0;
}

