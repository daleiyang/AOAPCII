#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 500+5;

int A[maxn*2], B[maxn*2];

int cal(int * A, int n){
	int cnt = 0, vis[maxn];
	memset(vis, 0, sizeof(vis));
	for(int i = 1; i <= n; i++){
		if(!vis[i]){
			cnt++;
			for(int j = i; !vis[j]; j = A[j])
				vis[j] = 1;
		}
	}
	return n-cnt;
}

int main(){
#ifdef LOCAL
		freopen("UVa.10570.in", "r", stdin);
		freopen("UVa.10570.out", "w", stdout);
#endif
	int n;
	while(scanf("%d", &n) == 1 && n){
		for(int i = 1; i <= n; i++){
			scanf("%d", &A[i]);
			B[n-i+1] = B[2*n-i+1] = A[i+n] = A[i];
		}
		int ans = 1<<30;
		for(int i = 0; i < n; i++)
			ans = min(ans, cal(A+i, n));
		for(int i = 0; i < n; i++)
			ans = min(ans, cal(B+i, n));
		printf("%d\n", ans);
	}
	return 0;
}

