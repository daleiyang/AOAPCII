#include<cstdio>
#include<algorithm>
using namespace std;

const int maxm = 10+5;
const int maxn = 100+5;
const int INF = 1000000000;

int a[maxm][maxn], d[maxm][maxn], nx[maxm][maxn], m, n;

int main(){
#ifdef LOCAL
		freopen("UVa.116.in", "r", stdin);
		freopen("UVa.116.out", "w", stdout);
#endif
    while(scanf("%d%d", &m, &n) == 2){
        for(int i = 0; i < m; i++) 
            for(int j = 0; j < n; j++)  
                scanf("%d", &a[i][j]);
        
        int ans = INF, first = 0;
        for(int j = n-1; j >=0; j--){
            for(int i = 0; i < m; i++){
                if(j == n-1) d[i][j] = a[i][j];
                else{
                    int rows[3] = {i, i-1, i+1};
                    if(i == 0) rows[1] = m-1;
                    if(i == m-1) rows[2] = 0;
                    sort(rows, rows+3);
                    d[i][j] = INF;
                    for(int k = 0; k < 3; k++){
                        int v = d[rows[k]][j+1]+a[i][j];
                        if(v < d[i][j]){d[i][j] = v; nx[i][j] = rows[k];}
                    }
                }
                if(j == 0 && d[i][j] < ans) {ans = d[i][j]; first = i;}
            }
        }
        printf("%d", first+1);
        for(int i = nx[first][0], j = 1; j < n; i = nx[i][j], j++)
            printf(" %d", i+1);
        printf("\n%d\n", ans);
    }
    return 0;
}
