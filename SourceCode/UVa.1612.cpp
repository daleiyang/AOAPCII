#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

const int maxn = 16384 + 5;
const int cnt = 3;
const int maxm = 1 << cnt;

int p[maxn][maxm+1], t[cnt], rk[maxn];

int main(){
#ifdef LOCAL
		freopen("UVa.1612.in", "r", stdin);
		freopen("UVa.1612.out", "w", stdout);
#endif
	int n, kase = 0;
	while(scanf("%d", &n) == 1 && n){
		//generate 8 possible sum score for each person
		for(int i = 1; i <= n; i++){
			double ff;
			for(int j = 0; j < cnt; j++){
				scanf("%lf", &ff);
				t[j] = (int)round(ff*100); //must round here if you want to * 100 to avoid precision issue
			}
			for(int j = 0; j < maxm; j ++){
				int sum = 0;
				for(int k = 0; k < cnt; k++){
					if((1<<k)&j) sum += t[k];
				}
				p[i][j] = sum;
			}
			sort(p[i], p[i]+maxm);	
		}

		for(int i = 0; i < n; i++) scanf("%d", &rk[i]);
		
		printf("Case %d: ", ++kase);
		int pre = rk[0];
		int ans = p[rk[0]][maxm-1]; //the max sum score for rank 1 person.
		
		bool f = true; int r;
		for(int i = 1; i <= n-1; i++){
			r = rk[i];
			//lower_bound
			int x = 0, y = maxm;
			while(x<y){
				int m = x+(y-x)/2;
				if(p[r][m] >= ans) y = m;
				else x = m+1;
			}
			if(r > pre){
				if(x == maxm){
					ans = p[r][maxm-1];
					pre = r;
					continue;
				}
				else if(p[r][x] == ans){
					ans = p[r][x];
					pre = r;
					continue;
				}		
				else if(p[r][x] > ans && x > 0){
					ans = p[r][x-1];
					pre = r;
					continue;
				}
				else if(p[r][x] > ans && x == 0){
					f = false;
					break;
				}
			}
			else if(r < pre){
				if(x == maxm){
					ans = p[r][maxm-1];
					pre = r;
					continue;
				}
				else if(p[r][x] == ans && x == 0){
					f = false;
					break;
				}
				else if(p[r][x] == ans && x > 0){
					ans = p[r][x-1];
					pre = r;
					continue;
				}
				else if(p[r][x] > ans && x > 0){
					ans = p[r][x-1];
					pre = r;
					continue;
				}
				else if(p[r][x] > ans && x == 0){
					f = false;
					break;
				}
			}
		}
		if(f) printf("%.2f\n", (double)ans/100);
		else printf("No solution\n");
	}
	return 0;
}
