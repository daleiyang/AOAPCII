#include<cstdio>
using namespace std;

typedef long long LL;
int K;

LL c(int k){
	LL ans = 1;
	for(int i = 0; i < k; i++) ans *= 3;
	return ans;	
}

LL f(int k, int i){
	if(k == 0 && i == 1) return 1;
	else if(i < 1) return 0;
	else if(i <= (1 << (k-1))) return 2 * f(k-1, i);
	else if(i > (1 << (k-1))) return 2 * c(k-1) + f(k-1, i - (1 << (k-1)));
	return 0;
}

LL g(int k, int i){
	if(k == 0 && i == 1) return 1;
	else if(i > (1 << K)) return 0;
	else if(i <= (1 << (k-1))) return c(k-1) + 2* g(k-1, i);
	else if (i > (1 << (k-1))) return g(k-1, i - (1 << (k-1)));
	return 0;
}

LL solve(int k, int a, int b){	
	return f(k, b) - f(k, a-1);
	//return g(k, a) - g(k, b+1);
}

int main(){
#ifdef LOCAL
	freopen("UVa.12627.in", "r", stdin);
	freopen("UVa.12627.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	for(int i = 1; i <= T; i++){
		int A, B;
		scanf("%d%d%d", &K, &A, &B);
		printf("Case %d: %lld\n", i, solve(K, A, B));
	}
	return 0;
}

