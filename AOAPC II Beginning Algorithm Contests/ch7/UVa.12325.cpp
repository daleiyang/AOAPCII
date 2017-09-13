#include<cstdio>
#include<algorithm>
using namespace std;

typedef long long LL;

const int maxn = 65536;

int main(){
#ifdef LOCAL
	freopen("UVa.12325.in", "r", stdin);
	freopen("UVa.12325.out", "w", stdout);
#endif
	int T, kase = 0, N, s1, v1, s2, v2;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d%d%d%d", &N, &s1, &v1, &s2, &v2);
		if(s1 < s2) {swap(s1, s2); swap(v1, v2);}
		LL sum = 0;
		LL ss1 = N/s1;
		if(ss1 < maxn){
			for(LL i = 0; i <= ss1; i++) {
				sum = max(sum, i*v1 + (N-i*s1)/s2*v2);
			}
		}
		else{
			if(s2*v1 > s1*v2){
				for(LL i = 0; i < s1; i++){
					sum = max(sum, (N-i*s2)/s1*v1 + i*v2);
				}
			}else{
				for(LL i = 0; i < s2; i++){
					sum = max(sum, i*v1 + (N-i*s1)/s2*v2);
				}
			}
		}
		printf("Case #%d: %lld\n", ++kase, sum);
	}
	return 0;
}

