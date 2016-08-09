#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 13+1;

int ans[1000 + 1], a[maxn], n;

bool dfs(int d, int maxd){
	if(d == maxd && a[d] == n) return true;	
	if(d == maxd && a[d] != n) return false;

	int maxv = a[0];
	for(int i = 1; i <= d; i++){
		maxv = max(maxv, a[i]);
	}
	if(maxv << (maxd - d) < n) return false;

	for(int i = d; i >= 0; i--){
		a[d+1] = a[d]+a[i];
		if(dfs(d+1, maxd)) return true;
		a[d+1] = a[d]-a[i];
		if(dfs(d+1, maxd)) return true;
	}
	return false;
}

int solve(){
	for(int maxd = 1; maxd <= maxn; maxd++){
		if(dfs(0, maxd)) return maxd;
	}
	return maxn;
}

int main(){
#ifdef LOCAL
	freopen("UVa.1374.in", "r", stdin);
	freopen("UVa.1374.out", "w", stdout);
#endif
	a[0] = 1; ans[1] = 0;
	for(n = 2; n <= 1000; n++){
		ans[n] = solve();
	}
	int x;
	while(scanf("%d", &x) == 1 && x){
		printf("%d\n", ans[x]);
	}
	return 0;
}

