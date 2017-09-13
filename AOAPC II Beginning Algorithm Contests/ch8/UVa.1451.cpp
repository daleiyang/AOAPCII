#include<cstdio>
using namespace std;

const int maxn = 100000 + 5;

char s[maxn];
int sum[maxn], p[maxn];

int compare_avg(int x1, int x2, int x3, int x4){
	return (sum[x2]-sum[x1-1])*(x4-(x3-1)) - (sum[x4]-sum[x3-1])*(x2-(x1-1));
}

int main(){
#ifdef LOCAL
	freopen("UVa.1451.in", "r", stdin);
	freopen("UVa.1451.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	while(T--){
		int n, L;
		scanf("%d%d%s", &n, &L, s+1);
		
		sum[0] = 0;
		for(int i = 1; i <= n; i++) sum[i] = sum[i-1]+s[i]-'0';

		int ansL = 1, ansR = L;
		int i = 0, j = 0;
		for(int t = L; t <= n; t++){
			while(j-i > 1 && compare_avg(p[j-2], t-L, p[j-1], t-L) >= 0) j--;
			p[j++] = t-L+1;
			while(j-i > 1 && compare_avg(p[i], t, p[i+1], t) <= 0) i++;
				
			int c = compare_avg(p[i], t, ansL, ansR);
			if(c > 0 || (c == 0 && t-p[i] < ansR- ansL)){
				ansL = p[i];
				ansR = t;
			}
		}
		printf("%d %d\n", ansL, ansR);
	}
	return 0;
}

