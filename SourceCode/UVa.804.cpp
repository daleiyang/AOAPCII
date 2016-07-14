#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 100 + 5;
int p, t, np[maxn], k, limit, kase = 0;

struct petri{
	int in[maxn], out[maxn], i[maxn], o[maxn], ic, oc;
} pet[maxn];

int main(){
#ifdef LOCAL
		freopen("UVa.804.in", "r", stdin);
		freopen("UVa.804.out", "w", stdout);
#endif
	while(scanf("%d", &p) == 1 && p){
		memset(pet, 0 , sizeof(pet));
		for(int i = 1; i <= p; i++) {scanf("%d", &np[i]);}
		scanf("%d", &t);
		for(int i = 1; i <= t; i++){
			while(scanf("%d", &k) == 1 && k){
				if(k < 0){pet[i].in[-k]++;}
				else {pet[i].out[k]++;}
			}
			for(int j = 1; j <= p; j++){
				if(pet[i].in[j]){pet[i].i[++pet[i].ic] = j;}
				if(pet[i].out[j]){pet[i].o[++pet[i].oc] = j;}
			}
		}
		scanf("%d", &limit);
		int cnt = 0;
		for(int i = 1; i <= t; ++i){
			bool flag = true;
			petri &kt = pet[i];
			for(int j = 1; j <= kt.ic; j++){
				if(np[kt.i[j]] < kt.in[kt.i[j]]){
					flag = false; break;
				}
			}
			if(!flag) continue;
			for(int j = 1; j <= kt.ic; j++){
				np[kt.i[j]] -= kt.in[kt.i[j]];
			}
			for(int j = 1; j <= kt.oc; j++){
				np[kt.o[j]] += kt.out[kt.o[j]];
			}
			i = 0;
			if(++cnt >= limit) break;
		}
		if(cnt >= limit){
			printf("Case %d: still live after %d transitions\n", ++kase, limit);
		}
		else{
			printf("Case %d: dead after %d transitions\n", ++kase, cnt);
		}
		printf("Places with tokens:");
		for(int i = 1; i <= p; i++){
			if(np[i]) printf(" %d (%d)", i, np[i]);
		}
		printf("\n\n");
	}
	return 0;
}

