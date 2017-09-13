/* http://www.cnblogs.com/jerryRey/p/4719690.html
Algorithm:

The problem is ask for the largest value among all "sum[a[i], a[i+1], a[]j] * min(a[i], a[i+1] ... a[j])"

So, we will seach for a range for each element, in this range, we make sure this emelent is the smallest one and we try to enlarge 
this range as much as we can. We could proof, if we include another smaller value in the current set, the calculation result will be smaller 
than the value from original set.
*/
#include<cstdio>
using namespace std;

const int maxn = 1e5 + 5;

int a[maxn], L[maxn], R[maxn];
typedef long long ll;
ll sum[maxn];

int main(){
#ifdef LOCAL
		freopen("UVa.1619.in", "r", stdin);
		freopen("UVa.1619.out", "w", stdout);
#endif
	int n, kase = 0;
	sum[0] = 0;
	while(scanf("%d", &n) == 1){
		a[0] = -1, a[n+1] = -1;
		for(int i = 1; i <= n; i++) {
			scanf("%d", &a[i]);
			sum[i] = sum[i-1] + a[i]; 
			L[i] = R[i] = i;
		}
		for(int i = 1; i <=n; i++) 
			/*
			Test case, try this one, you will understand following magic logic.
			16
			1 2 1 1 1 1 1 1 1 1 1 1 1 1 1 1
			*/
			while (a[i] <= a[L[i]-1]) L[i] = L[L[i]-1]; //L[0] will not be touched becuase of a[0] = -1;
			
		for(int i = n; i >= 1; i--) 
			while (a[i] <= a[R[i]+1]) R[i] = R[R[i]+1]; //R[n+1] will not be touched because of a[n+1] = -1;
		
		ll MAX = (ll)a[1]*a[1]; 
		int Li = 1, Ri = 1;
		for(int i = 1; i <= n; i++){
			ll temp =(sum[R[i]] - sum[L[i]-1]) * a[i];
			if(temp > MAX){
				MAX = temp;
				Li = L[i];
				Ri = R[i];
			}
		}
		if(kase++) printf("\n");
		printf("%lld\n%d %d\n", MAX, Li, Ri);
	}
	return 0;
}

