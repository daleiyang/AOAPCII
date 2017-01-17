#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 10;

struct SuffixArray{
    char s[maxn];
    int sa[maxn];
    int t[maxn], t2[maxn], c[maxn], n;

    void clear(){ n = 0; memset(sa, 0, sizeof(sa));}

    void build_sa(int m){
        int i, *x = t, *y = t2;

        for(i = 0; i < m; i++) c[i] = 0;
        for(i = 0; i < n; i++) c[x[i] = s[i]]++;
        for(i = 1; i < m; i++) c[i] += c[i-1];
        for(i = n-1; i >= 0; i--) sa[--c[x[i]]] = i;

        for(int k = 1; k <= n; k <<= 1){
            int p = 0;
            for(i = n-k; i < n; i++) y[p++] = i;
            for(i = 0; i < n; i++) if(sa[i] >= k) y[p++] = sa[i]-k;
            for(i = 0; i < m; i++) c[i] = 0;
            for(i = 0; i < n; i++) c[x[y[i]]]++;
            for(i = 0; i < m; i++) c[i] += c[i-1];
            for(i = n-1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];

            swap(x, y);
            p = 1; x[sa[0]] = 0;
            for(i = 1; i < n; i++)
                x[sa[i]] = y[sa[i-1]] == y[sa[i]] && y[sa[i-1]+k] == y[sa[i]+k] ? p-1 : p++;
            if(p >= n) break;
            m = p;
        }
    }

    int cmp_suffix(char* P, int p, int m){
        return strncmp(P, s+sa[p], m);
    }

    int find(char *P){
        int m = strlen(P);
        if(cmp_suffix(P, 0, m) < 0) return -1;
        if(cmp_suffix(P, n-1, m) > 0) return -1;
        int L = 0, R = n-1;
        while(R >= L){
            int M = L + (R-L)/2;
            int res = cmp_suffix(P, M, m);
            if(!res) return M;
            if(res < 0) R = M-1; else L = M+1;
        }
        return -1;
    }
};

SuffixArray sa;
char P[1000+5];

int main(){
#ifdef LOCAL
	freopen("UVa.10679.in", "r", stdin);
	freopen("UVa.10679.out", "w", stdout);
#endif
    int T, q;
    scanf("%d", &T);
    while(T--){
        sa.clear();
        scanf("%s", sa.s);
        sa.n = strlen(sa.s)+1;
        sa.build_sa('z'+1);
        scanf("%d", &q);
        while(q--){
            scanf("%s", P);
            if(sa.find(P) >= 0) printf("y\n"); else printf("n\n");
        }
    }
    return 0;
}       
