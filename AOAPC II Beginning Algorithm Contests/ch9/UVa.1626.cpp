#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100 + 5;
char S[maxn];
int n, d[maxn][maxn];

int match(char a, char b){
    return (a == '(' && b == ')') || (a == '[' && b == ']');
}

int dp(int i, int j){
    int& ans = d[i][j];
    if(ans >= 0) return ans;
    if(i > j) return ans = 0;
    if(i == j) return ans = 1;
    ans = n;
    if(match(S[i], S[j])) ans = min(ans, dp(i+1, j-1));
    for(int k = i; k < j; k++)
        ans = min(ans, dp(i, k) + dp(k+1, j));
    return ans;
}

void print(int i, int j){
    if(i > j) return;
    if(i == j){
        if(S[i] == '(' || S[i] == ')') printf("()");
        else printf("[]");
        return;
    }
    int ans = d[i][j];
    if(match(S[i], S[j]) && ans == d[i+1][j-1]){
        printf("%c", S[i]); print(i+1, j-1); printf("%c", S[j]);
        return;
    }
    for(int k = i; k < j; k++)
        if(ans == d[i][k] + d[k+1][j]){
            print(i, k); print(k+1, j);
            return;
        }
}

void readline(char* S){
    fgets(S, maxn, stdin);
}

int main(){
#ifdef LOCAL
		freopen("UVa.1626.in", "r", stdin);
		freopen("UVa.1626.out", "w", stdout);
#endif
    int T;

    readline(S);
    sscanf(S, "%d", &T);
    readline(S);

    while(T--){
        readline(S);
        n = strlen(S) - 1;
        memset(d, -1, sizeof(d));
        dp(0, n-1);
        print(0, n-1);
        printf("\n");
        if(T) printf("\n");
        readline(S);
    }
    return 0;
}
