#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 20;
int tree[1 << maxn];

int main(){
#ifdef LOCAL
	freopen("UVa.679.in", "r", stdin);
	freopen("UVa.679.out", "w", stdout);
#endif
	int T, D, I, k, n;
	scanf("%d", &T);
	while(T--){
		memset(tree, 0 , sizeof(tree));
		scanf("%d%d", &D, &I);
		k = (1<<D) - 1;
		for(int i = 1; i <= I; i++){
			n = 1;
			for(;;){
				tree[n] = !tree[n];
				n = tree[n]? 2*n : 2*n+1;
				if(n > k) break;
			}
		}
		printf("%d\n", n/2);
	}
	return 0;
}

