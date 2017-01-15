#include<cstdio>
#include<cstring>
#include<queue>

using namespace std;

const int sigma_size = 26;
const int maxnode = 10000+10;

void process_match(int pos, int v);

struct AhoCorasickAutomata{
    int ch[maxnode][sigma_size];
    int f[maxnode];
    int val[maxnode];
    int last[maxnode];
    int sz;

    void init(){sz = 1; memset(ch[0], 0, sizeof(ch[0]));}

    int idx(char c) { return c-'a'; }

    void insert(char *s, int v){
        int u = 0, n = strlen(s);
        for(int i = 0; i < n; i++){
            int c = idx(s[i]);
            if(!ch[u][c]){
                memset(ch[sz], 0, sizeof(ch[sz]));
                val[sz] = 0;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        val[u] = v;
    }

    void report(int pos, int j){
        if(j){
            process_match(pos, val[j]);
            report(pos, last[j]);
        }
    }

    void find(char *T){
        int n = strlen(T);
        int j = 0;
        for(int i = 0; i < n; i++){
            int c = idx(T[i]);
            while(j && !ch[j][c]) j = f[j];
            j = ch[j][c];
            if(val[j]) report(i, j);
            else if(last[j]) report(i, last[j]);
        }
    }

    void getFail(){
        queue<int> q;
        f[0] = 0;
        for(int c = 0; c < sigma_size; c++){
            int u = ch[0][c];
            if(u) {f[u] = 0; q.push(u); last[u] = 0;}
        }
        while(!q.empty()){
            int r = q.front(); q.pop();
            for(int c = 0; c < sigma_size; c++){
                int u = ch[r][c];
                if(!u) continue;
                q.push(u);
                int v = f[r];
                while(v && !ch[v][c]) v = f[v];
                f[u] = ch[v][c];
                last[u] = val[f[u]] ? f[u] : last[f[u]];
            }
        }
    }
};

AhoCorasickAutomata ac;

const int maxn = 1000 + 10;
const int maxm = 1000 + 10;
const int maxx = 100 + 10;
const int maxy = 100 + 10;
char text[maxn][maxm], P[maxx][maxy];
int repr[maxx], nx[maxx], len[maxx];
int tr, cnt[maxn][maxm];

void process_match(int pos, int v){
    int pr = repr[v-1];
    int c = pos-len[pr]+1;
    while(pr >= 0){
        if(tr >= pr)
            cnt[tr-pr][c]++;
        pr = nx[pr];
    }
}

int main(){
#ifdef LOCAL
	freopen("UVa.11019.in", "r", stdin);
	freopen("UVa.11019.out", "w", stdout);
#endif
    int T, n, m, x, y;
    scanf("%d", &T);
    while(T--){
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; i++)
            scanf("%s", text[i]);

        scanf("%d%d", &x, &y);
        ac.init();
        for(int i = 0; i < x; i++){
            scanf("%s", P[i]);
            len[i]= strlen(P[i]);
            repr[i] = i;
            nx[i] = -1;
            for(int j = 0; j < i; j++)
                if(strcmp(P[i], P[j]) == 0){
                    repr[i] = j;
                    nx[i] = nx[j];
                    nx[j] = i;
                    break;
                }
            if(repr[i] == i) ac.insert(P[i], i+1);
        }
        ac.getFail();

        memset(cnt, 0, sizeof(cnt));
        for(tr = 0; tr < n; tr++)
            ac.find(text[tr]);

        int ans = 0;
        for(int i = 0; i < n-x+1; i++)
            for(int j = 0; j < m-y+1; j++)
                if(cnt[i][j] == x) ans++;
        printf("%d\n", ans);
    }
    return 0;
}
