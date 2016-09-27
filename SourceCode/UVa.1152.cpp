#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 4000 + 5;
int A[maxn], B[maxn], C[maxn], D[maxn], sum[maxn*maxn];

int main(){
#ifdef LOCAL
	freopen("UVa.1152.in", "r", stdin);
	freopen("UVa.1152.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	while(T--){
		int n;
		scanf("%d", &n);
		for(int i = 0; i < n; i++){
			scanf("%d%d%d%d", &A[i], &B[i], &C[i], &D[i]);
		}
		int idx = 0;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++)
				sum[idx++] = A[i]+B[j];
		sort(sum, sum+idx);
		int cnt = 0, t;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < n; j++){
				t = -C[i]-D[j];
				cnt += upper_bound(sum, sum+idx, t) - lower_bound(sum, sum+idx, t);
			}
		printf("%d\n", cnt);
		if(T) printf("\n");
	}
	return 0;
}

