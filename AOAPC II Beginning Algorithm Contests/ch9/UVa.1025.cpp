#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 50+5;
const int maxt = 200+5;
const int INF = 1e9;

int t[maxn], has_train[maxt][maxn][2];
int dp[maxt][maxn];

int main(){
#ifdef LOCAL
	freopen("UVa.1025.in", "r", stdin);
	freopen("UVa.1025.out", "w", stdout);
#endif
	int kase = 0, n, T;
	while(scanf("%d%d", &n, &T) == 2 && n){
		int M1, M2, d;
		for(int i = 1; i <= n-1; i++) scanf("%d", &t[i]);

		memset(has_train, 0, sizeof(has_train));
		//at time d, in sation i, has train to right.
		scanf("%d", &M1);
		while(M1--){
			scanf("%d", &d);
			for(int i = 1; i <= n-1; i++){
				if(d <= T) has_train[d][i][0] = 1; //d could be T, and DP logic will take care of it
				d += t[i];
			}
		}
		//at time d, in sation i+1, has train to left.
		scanf("%d", &M2);
		while(M2--){
			scanf("%d", &d);
			for(int i = n-1; i >= 1; i--){
				if(d <= T) has_train[d][i+1][1] = 1; //d could be T, and DP logic will take care of it
				d += t[i];
			}
		}
		
		//DP state pattern 2:  the minimal path end with dp[T][n] == 0 
		for(int i = 1; i <= n-1; i++) dp[T][i] = INF; //INF means no answer
		dp[T][n] = 0;

		for(int i = T-1; i >= 0; i--)
			for(int j = 1; j <= n; j++){
				dp[i][j] = dp[i+1][j] + 1; //init dp[i][j]
				if(j < n && has_train[i][j][0] && i+t[j] <= T)
					dp[i][j] = min(dp[i][j], dp[i+t[j]][j+1]); //to right
				if(j > 1 && has_train[i][j][1] && i+t[j-1] <= T)
					dp[i][j] = min(dp[i][j], dp[i+t[j-1]][j-1]); //to left
		 	}

		printf("Case Number %d: ", ++kase);
		if(dp[0][1] >= INF) printf("impossible\n");
		else printf("%d\n", dp[0][1]);
	}
	return 0;
}

