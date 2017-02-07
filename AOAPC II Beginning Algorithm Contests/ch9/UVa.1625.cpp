#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 5000+5;
const int INF = 1000000000;

char p[maxn], q[maxn];
int sp[26], sq[26], ep[26], eq[26];
int d[2][maxn], c[2][maxn];

int main(){
#ifdef LOCAL
		freopen("UVa.1625.in", "r", stdin);
		freopen("UVa.1625.out", "w", stdout);
#endif
    int T;
    scanf("%d", &T);
    while(T--){
        scanf("%s%s", p+1, q+1);

        int n = strlen(p+1);
        int m = strlen(q+1);
        for(int i = 1; i <= n; i++) p[i] -= 'A';
        for(int i = 1; i <= m; i++) q[i] -= 'A';

        for(int i = 0; i < 26; i++) {sp[i] = sq[i] = INF; ep[i] = eq[i] = 0;}
        for(int i = 1; i <= n; i++){
            sp[p[i]] = min(sp[p[i]], i);
            ep[p[i]] = i;
        }
        for(int i = 1; i <= m; i++){
            sq[q[i]] = min(sq[q[i]], i);
            eq[q[i]] = i;
        }

        /*  
            d[i][j]: move 1~i from p and 1~j from q to mixed queue, the lowest L(c) for this queue.
            c[i][j]: how many incomplete colors in the mixed queue.
            d[i][j] = min(d[i-1][j]+c[i-1][j], d[i][j-1]+c[i][j-1]);
        */
        int t = 0;
        memset(d, 0, sizeof(d));
        memset(c, 0, sizeof(c));
        for(int i = 0; i <= n; i++){
            for(int j = 0; j <= m; j++){
                if(!i && !j) continue; //d[0][0] = c[0][0] = 0
                
                int v1 = INF, v2 = INF;
                if(i) v1 = d[t^1][j] + c[t^1][j]; //d[i][j-1]+c[i][j-1]
                if(j) v2 = d[t][j-1] + c[t][j-1]; //d[i-1][j]+c[i-1][j]
                d[t][j] = min(v1, v2);  //d[i][j] = min(d[i-1][j]+c[i-1][j], d[i][j-1]+c[i][j-1]);

                if(i){
                    c[t][j] = c[t^1][j];
                    //here we use sp[p[i]]. Reason is we start from i == 0, the else branch. we copy value from 
                    //c[t][j] = c[t^1][j], we need to find out whether p[i] could be affected by element from q.
                    if(sp[p[i]] == i && sq[p[i]] > j) c[t][j]++;
                    if(ep[p[i]] == i && eq[p[i]] <= j) c[t][j]--;
                }else if(j){ //just for i == 0, init c[0][0] = 0;
                    c[t][j] = c[t][j-1];
                    if(sq[q[j]] == j) c[t][j]++;
                    if(eq[q[j]] == j && ep[q[j]] == 0) c[t][j]--;
                }
            }
            t ^= 1;
        }
        printf("%d\n", d[t^1][m]);
    }
    return 0;
}
