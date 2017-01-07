#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 500000 + 10;
const int maxnode = 1000000 + 10;
typedef long long LL;
typedef pair<int, int> Interval;

LL prefix_sum[maxn];

LL sum(int L, int R){
    return prefix_sum[R] - prefix_sum[L-1];
}

LL sum(Interval p){
    return sum(p.first, p.second);
}

Interval better(Interval a, Interval b){
    if(sum(a) != sum(b)) return sum(a) > sum(b) ? a : b;
    return a < b ? a : b;
}

int ql, qr;

struct IntervalTree{
    int max_prefix[maxnode], max_suffix[maxnode];
    Interval max_sub[maxnode];

    void build(int o, int L, int R){
        if(L == R){
            max_prefix[o] = max_suffix[o] = L;
            max_sub[o] = make_pair(L, L);
        }else{
            int M = L + (R-L)/2;
            int lc = o*2, rc = o*2+1;
            build(lc, L, M);
            build(rc, M+1, R);

            LL v1 = sum(L, max_prefix[lc]);
            LL v2 = sum(L, max_prefix[rc]);
            if(v1 == v2) max_prefix[o] = min(max_prefix[lc], max_prefix[rc]);
            else max_prefix[o] = v1 > v2 ? max_prefix[lc] : max_prefix[rc];

            v1 = sum(max_suffix[lc], R);
            v2 = sum(max_suffix[rc], R);
            if(v1 == v2) max_suffix[o] = min(max_suffix[lc], max_suffix[rc]);
            else max_suffix[o] = v1 > v2 ? max_suffix[lc] : max_suffix[rc];

            max_sub[o] = better(max_sub[lc], max_sub[rc]);
            max_sub[o] = better(max_sub[o], make_pair(max_suffix[lc], max_prefix[rc]));
        }
    }

    Interval query_prefix(int o, int L, int R){
        if(max_prefix[o] <= qr) return make_pair(L, max_prefix[o]);
        int M = L + (R-L)/2;
        int lc = o*2, rc = o*2+1;
        if(qr <= M) return query_prefix(lc, L, M);
        Interval i = query_prefix(rc, M+1, R);
        i.first = L;
        return better(i, make_pair(L, max_prefix[lc]));
    }

    Interval query_suffix(int o, int L, int R){
        if(max_suffix[o] >= ql) return make_pair(max_suffix[o], R);
        int M = L + (R-L)/2;
        int lc = o*2, rc = o*2+1;
        if(ql > M) return query_suffix(rc, M+1, R);
        Interval i = query_suffix(lc, L, M);
        i.second = R;
        return better(i, make_pair(max_suffix[rc], R));
    }

    Interval query(int o, int L, int R){
        if(ql <= L && R <= qr) return max_sub[o];
        int M = L + (R-L)/2;
        int lc = o*2, rc = o*2+1;
        if(qr <= M) return query(lc, L, M);
        if(ql > M) return query(rc, M+1, R);
        Interval i1 = query_prefix(rc, M+1, R);
        Interval i2 = query_suffix(lc, L, M);
        Interval i3 = better(query(lc, L, M), query(rc, M+1, R));
        return better(make_pair(i2.first, i1.second), i3);
    }
};

IntervalTree tree;

int main(){
#ifdef LOCAL
		freopen("UVa.1400.in", "r", stdin);
		freopen("UVa.1400.out", "w", stdout);
#endif
    int kase = 0, n, a, Q;
    while(scanf("%d%d", &n, &Q) == 2){
        prefix_sum[0] = 0;
        for(int i = 0; i < n; i++){
            scanf("%d", &a);
            prefix_sum[i+1] = prefix_sum[i]+a;
        }
        tree.build(1, 1, n);
        printf("Case %d:\n", ++kase);
        while(Q--){
            scanf("%d%d", &ql, &qr);
            Interval ans = tree.query(1, 1, n);
            printf("%d %d\n", ans.first, ans.second);
        }
    }
    return 0;
}
