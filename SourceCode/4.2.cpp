#include<stdio.h>
long long c(int n, int m){
	if(m<n-m) m = n-m;
	long long ans = 1;
	for(int i=m+1; i<=n; i++) ans *=i;
	for(int i= n-m; i>=1; i--) ans /=i;
	return ans;
}

int main(){
#ifdef LOCAL
	freopen("4.1.in", "r", stdin);
	freopen("4.1.out", "w", stdout);
#endif
	int n, m;
	scanf("%d%d", &n, &m);
	printf("%lld", c(n, m));
	return 0;
}

