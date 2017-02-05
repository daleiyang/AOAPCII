#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 50+5;

int n, t, v, d[2][maxn*180+678];

int main(){
#ifdef LOCAL
		freopen("UVa.12563.in", "r", stdin);
		freopen("UVa.12563.out", "w", stdout);
#endif
    int T;
    scanf("%d", &T);
    for(int kase = 1; kase <= T; kase++){
        scanf("%d%d", &n, &t);
        for(int i = 0; i < t; i++) d[0][i] = -1;
        d[0][0] = 0;
    
        int p = 1, ans = 0;
        for(int i = 1; i <= n; i++){
            scanf("%d", &v);
            for(int j = 0; j < t; j++){
                d[p][j] = d[p^1][j];
                if(j >= v && d[p^1][j-v] >=0)
                    d[p][j] = max(d[p][j], d[p^1][j-v]+1);
                ans = max(ans, d[p][j]); 
            }
            p = p^1;
        }
        for(int i = t-1; i >= 0; i--)
            if(d[p^1][i] == ans){
                printf("Case %d: %d %d\n", kase, ans+1, i+678);
                break;
            }
    }
    return 0;
}
