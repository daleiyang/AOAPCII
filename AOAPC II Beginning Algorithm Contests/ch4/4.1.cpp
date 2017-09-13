#include<stdio.h>
long long factorial(int n){
	long long m=1;
	for(int i=1; i<=n; i++){
		m *=i;
	}
	return m;
}
long long c(int n, int m){
	long long x = factorial(n);
	long long y = factorial(m);
	long long z = factorial(n-m);
	return x/(y*z);
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

