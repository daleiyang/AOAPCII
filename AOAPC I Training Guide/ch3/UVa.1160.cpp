#include<cstdio>
using namespace std;

const int maxn = 100000 + 5;
int pa[maxn];

int findset(int x) {return pa[x] == x ? x : pa[x] = findset(pa[x]);}

int main(){
#ifdef LOCAL
		freopen("UVa.1160.in", "r", stdin);
		freopen("UVa.1160.out", "w", stdout);
#endif
    int x, y;
    while(scanf("%d", &x) == 1){
        for(int i = 0; i < maxn; i++) pa[i] = i;
        int ans = 0;
        while(x != -1){
            scanf("%d", &y);
            int u = findset(x), v = findset(y);
            if(u == v) ans++;
            else pa[u] = v;
            scanf("%d", &x);
        }
        printf("%d\n", ans);
    }
    return 0;
}
