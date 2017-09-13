#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 5;
int a[maxn];

int comp(int a, int b){
	return b < a;
}

int main(){
#ifdef LOCAL
		freopen("UVa.1149.in", "r", stdin);
		freopen("UVa.1149.out", "w", stdout);
#endif
	int T, n ,l;
	scanf("%d", &T);
	for(int kase = 0; kase < T; kase++){
		if(kase) printf("\n");
		scanf("%d%d", &n, &l);
		for(int i = 0; i < n; i++) scanf("%d", &a[i]);
		sort(a, a+n, comp);
		int ans = 0;
		for(int i = 0, j = n-1; i <= j;){
			if(i < j){
				if(a[i] + a[j] <= l){
					ans++; i++; j--;
				}
				else{
					ans++; i++;
				}
			}
			else if(i == j){
				ans++; break;
			}
		}
		printf("%d\n", ans);
	}	
	return 0;
}

