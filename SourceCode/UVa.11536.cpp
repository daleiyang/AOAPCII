//http://blog.csdn.net/keshuai19940722/article/details/18883357
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1000000 + 5;
const int maxm = 1000 + 1;
int a[maxn],vis[maxm], N, M, K;

void init(){
	memset(a, 0, sizeof(a));
	memset(vis, 0, sizeof(vis));
	scanf("%d%d%d", &N, &M, &K);
	a[1] = 1, a[2] = 2, a[3] = 3;
	for(int i = 4; i <= N; i++) a[i] = (a[i-1]+a[i-2]+a[i-3])%M+1;
}

bool solve(){
	int L = 1, R = 1, c = 0;
	int ans = N+1;
	while(R <= N){
		int t = a[R++];
		vis[t]++;
		if(t <= K && vis[t] == 1) c++;
		while(c == K && L < R){
			ans = min(ans, R-L);
			t = a[L++];
			vis[t]--;
			if(t <= K && !vis[t]) c--;
		}
	}
	if(ans < N+1){
		printf("%d\n", ans);
		return true;
	}
	return false;
}

int main(){
#ifdef LOCAL
		freopen("UVa.11536.in", "r", stdin);
		freopen("UVa.11536.out", "w", stdout);
#endif
	int T;
	scanf("%d",  &T);
	for(int i = 1; i<= T; i++){
		printf("Case %d: ", i);
		init();
		if(!solve()) printf("sequence nai\n");
	}
	return 0;
}

