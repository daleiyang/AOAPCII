#include<cstdio>
using namespace std;

const int maxn = 100000 + 5;
int a[maxn];
char x[maxn];

int main(){
#ifdef LOCAL
		freopen("UVa.11491.in", "r", stdin);
		freopen("UVa.11491.out", "w", stdout);
#endif
	int d, n;
	while(scanf("%d%d", &n, &d) == 2 && n){
		scanf("%s", x);
		for(int i = 0; i < n; i++) a[i] = x[i]-'0';
		
		int sidx = 0;
		for(int eidx = d; eidx < n; eidx++){
			int midx = 0, mn = -1;
			for(int i = sidx; i <= eidx; i++){
				if(a[i] > mn){
					midx = i;
					mn = a[i];
				}
			}
			printf("%d", a[midx]);
			sidx = midx+1;
		}
		printf("\n");
	}
	return 0;
}

