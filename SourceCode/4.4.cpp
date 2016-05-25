#include<stdio.h>
#include<math.h>
int is_prime(int n){
	if(n<=1) return 0;
	int m = floor(sqrt(n)+0.5);
	for(int i=2; i<=m; i++){
		if(n%i==0) return 0;	
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

