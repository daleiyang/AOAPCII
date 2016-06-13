#include<cstdio>
#include<algorithm>
using namespace std;

#define FOR(i, a, b) for(int i = a; i < b; i++)

const int maxn = 15 + 5;
int a[maxn];

int main(){
#ifdef LOCAL
	freopen("UVA.1594.in", "r", stdin);
	freopen("UVA.1594.out", "w", stdout);
#endif
	int T, n; bool f;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		FOR(i, 0, n) scanf("%d", a + i);
		FOR(i, 0, 1000){
			int c = a[0];
			FOR(j, 0, n){
				if(j == n - 1) a[n - 1] = abs(a[n - 1]-c);
				else a[j] = abs(a[j]-a[j + 1]);
			}
			f = true;
			FOR(j, 0, n) if(a[j]) {f = false; break;}
			if(f) break; 
		}
		if(f) printf("ZERO\n");
		else printf("LOOP\n");
	}
	return 0;
}

