#include<stdio.h>
#include<string.h>
const int maxn = 1048576;
int po[maxn];
int main(){
#ifdef LOCAL
	freopen("UVA.1591.in", "r", stdin);
	freopen("UVA.1591.out", "w", stdout);
#endif
	long long N, SP, SQ, K, A, B, t;
	while(scanf("%lld%lld%lld", &N, &SP, &SQ) != EOF){
		K=N*SQ<<10;A=34;B=34;
		for(int i=0; i<34; i++){
			for(int j=0; j<34; j++){
				t=(((N-1)*SP+((N-1)*SP<<i))>>j) + SQ;
				if((t<N*SQ)||(t>K)) continue;
				for(int k=0; k<N; k++){
					po[k]=(k*SP+((k*SP)<<i))>>j;
				}
				int f=1;
				for(int k=1; k<N; k++){
					if((po[k]-po[k-1])<SQ) f=0; 
					break;
				}
				if(!f) continue;
				if(t<K){K=t;A=i;B=j;}
				if(t==K && i<A){A=i; B=j;}
				if(t==K && i==A && j<B){B=j;}
			}
		}
		printf("%lld %lld %lld\n", K, A, B);
	}
	return 0;
}

