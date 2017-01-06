#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

const int maxn = 100000 + 5;
const int maxlog = 20;

struct RMQ{
    int d[maxn][maxlog];
    void init(const vector<int>& A){
        int n = A.size();
        for(int i = 0; i < n; i++) d[i][0] = A[i];
        for(int j = 1; (1<<j) <= n; j++)
            for(int i = 0; i + (1<<j) -1 < n; i++)
                d[i][j] = max(d[i][j-1], d[i+(1<<(j-1))][j-1]);
    }
    int query(int L, int R){
        int  k = 0;
        while((1<<(k+1)) <= R-L+1) k++;
        return max(d[L][k], d[R-(1<<k)+1][k]);
    }
};

int a[maxn], num[maxn], left[maxn], right[maxn];
RMQ rmq;

int main(){
#ifdef LOCAL
		freopen("UVa.11235.in", "r", stdin);
		freopen("UVa.11235.out", "w", stdout);
#endif
    int n, q;
    while(scanf("%d%d", &n, &q) == 2){
        for(int i = 0; i < n; i++) scanf("%d", &a[i]);
        a[n] = a[n-1] + 1;
        int start = -1;
        vector<int> count;
        for(int i = 0; i <= n; i++){
            if(i == 0 || a[i] > a[i-1]){
                if(i > 0){
                    count.push_back(i-start);
                    for(int j = start; j < i; j++){
                        num[j] = count.size()-1;
                        left[j] = start;
                        right[j] = i-1;
                    }
                }
                start = i;
            }
        }
        rmq.init(count);
        while(q--){
            int L, R, ans;
            scanf("%d%d", &L, &R); L--; R--;
            if(num[L] == num[R]) ans = R-L+1;
            else{
                ans = max(R-left[R]+1, right[L]-L+1);
                if(num[L]+1 < num[R]) ans = max(ans, rmq.query(num[L]+1, num[R]-1));
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
