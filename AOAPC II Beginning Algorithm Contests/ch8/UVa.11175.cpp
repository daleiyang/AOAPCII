//http://www.cnblogs.com/137033036-wjl/p/4945084.html
//https://github.com/morris821028/UVa/blob/master/volume111/11175%20-%20From%20D%20to%20E%20and%20Back.cpp
#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 300+5;

int g[maxn][maxn], gt[maxn];
int invg[maxn][maxn], invgt[maxn], to[maxn];

bool solve(int m){
	for(int i = 0; i < m; i++){
		memset(to, 0, sizeof(to));
		for(int j = 0; j < invgt[i]; j++){
			for(int k = 0; k < gt[invg[i][j]]; k++){
				to[g[invg[i][j]][k]]++;
			}
		}
		for(int j = 0; j < m; j++){
			if(to[j] != 0 && to[j] != invgt[i])
				return false;
		}
	}
	return true;
}

int main(){
#ifdef LOCAL
		freopen("UVa.11175.in", "r", stdin);
		freopen("UVa.11175.out", "w", stdout);
#endif
	int T, kase = 0, a, b, m, k;
	scanf("%d", &T);
	while(T--){
		memset(gt, 0, sizeof(gt));
		memset(invgt, 0, sizeof(invgt));
		scanf("%d%d", &m, &k);
		while(k--){
			scanf("%d%d", &a, &b);
			g[a][gt[a]++] = b;
			invg[b][invgt[b]++] = a;
		}
		printf("Case #%d: %s\n", ++kase, solve(m) ? "Yes":"No");
	}
	return 0;
}

