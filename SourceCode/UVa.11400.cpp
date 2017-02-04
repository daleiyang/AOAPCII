#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 1000+5;

struct lamp{
    int v, k, c, l;
    bool operator < (const lamp& rhs) const{
        return v < rhs.v;
    }
} lamps[maxn];

int n, s[maxn], d[maxn];

int main(){
#ifdef LOCAL
		freopen("UVa.11400.in", "r", stdin);
		freopen("UVa.11400.out", "w", stdout);
#endif
    while(scanf("%d", &n) == 1 && n){
        for(int i = 1; i <= n; i++)
            scanf("%d%d%d%d", &lamps[i].v, &lamps[i].k, &lamps[i].c, &lamps[i].l);
        sort(lamps+1, lamps+n+1);
        s[0] = 0;
        for(int i = 1; i <= n; i++) s[i] = s[i-1] + lamps[i].l;
        d[0] = 0;
        for(int i = 1; i <= n; i++){
            d[i] = s[i]*lamps[i].c + lamps[i].k;
            for(int j = 1; j < i; j++){
                d[i] = min(d[i], d[j]+(s[i]-s[j])*lamps[i].c+lamps[i].k);
            }
        }
        printf("%d\n", d[n]);
    }
    return 0;
}
