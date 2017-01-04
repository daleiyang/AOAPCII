#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 20000 + 10;
int pa[maxn], d[maxn];

int findset(int x){
    if(pa[x] != x){
        int root = findset(pa[x]);
        d[x] += d[pa[x]];
        return pa[x] = root;
    }else return x;
}

int main(){
#ifdef LOCAL
		freopen("UVa.1329.in", "r", stdin);
		freopen("UVa.1329.out", "w", stdout);
#endif
    int T, n, u, v;
    scanf("%d", &T);
    while(T--){
        scanf("%d", &n);
        for(int i = 1;  i <= n ;i++) { pa[i] = i; d[i] = 0;}
        char op[2];
        while(scanf("%s", op) && op[0] != 'O'){
            if(op[0] == 'E'){
                scanf("%d", &u); findset(u); printf("%d\n", d[u]);
            }
            if(op[0] == 'I'){
                scanf("%d%d", &u, & v); pa[u] = v; d[u] = abs(u-v)%1000;
            }
        }
    }
    return 0;
}
