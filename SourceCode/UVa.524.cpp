#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 16;
int isp[maxn*2];
int A[maxn];

int is_prime(int x){
	for(int i = 2; i*i <= x; i++){
		if(x % i == 0) return 0;
	}
	return 1;
}

int main(){
#ifdef LOCAL
	freopen("UVa.524.in", "r", stdin);
	freopen("UVa.524.out", "w", stdout);
#endif
	for(int i = 2; i < maxn*2; i++){
		isp[i] = is_prime(i);
	}
	int n, kase = 0;
	while(scanf("%d", &n) == 1){
		printf("Case %d:\n", ++kase);
		for(int i = 0; i < n; i++){
			A[i] = i+1;
		}
		do{
			int ok = 1;
			for(int i = 0; i < n; i++){
				if(!isp[A[i]+A[(i+1)%n]]){
					ok = 0; break;
				}
			}
			if(ok){
				for(int i = 0; i < n; i++){
					printf("%d ", A[i]);
				}
				printf("\n");
			}

		}while(next_permutation(A+1, A+n));
		printf("\n");
	}
	return 0;
}

