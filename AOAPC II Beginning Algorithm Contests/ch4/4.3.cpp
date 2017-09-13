#include<stdio.h>
//don't use whem n=1 or n is big
int is_prime(int n){
	for(int i=2; i*i<=n; i++){
		if(n%i == 0) return 0;
	}
	return 1;
}

int main(){
#ifdef LOCAL
	freopen("4.3.in", "r", stdin);
	freopen("4.3.out", "w", stdout);
#endif
	int n;
	scanf("%d", &n);
	printf("%d", is_prime(n));
	return 0;
}

