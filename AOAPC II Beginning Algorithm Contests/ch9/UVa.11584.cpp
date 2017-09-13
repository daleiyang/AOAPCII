#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1000+5;

int n, vis[maxn][maxn], p[maxn][maxn], d[maxn], kase;
char s[maxn];

int is_palindrome(int i, int j){
    if(i >= j) return 1;
    if(s[i] != s[j]) return 0;

    if(vis[i][j] == kase) return p[i][j];
    vis[i][j] = kase;

    return p[i][j] = is_palindrome(i+1, j-1);
}

int main(){
#ifdef LOCAL
	freopen("UVa.11584.in", "r", stdin);
	freopen("UVa.11584.out", "w", stdout);
#endif
    int T;
    scanf("%d", &T);
    memset(vis, 0, sizeof(vis));
    for(kase = 1; kase <= T; kase++){
        scanf("%s", s+1);
        n = strlen(s+1);
        d[0] = 0;
        for(int i = 1; i <= n; i++){
            d[i] = i;
            for(int j = 0; j < i; j++){
                if(is_palindrome(j+1, i)) d[i] = min(d[i], d[j]+1);
            }
        }
        printf("%d\n", d[n]);
    }
    return 0;
}
