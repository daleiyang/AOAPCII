#include<cstdio>
#include<cstring>
#include<string>
#include<queue>
#include<map>
using namespace std;

const int sigma_size = 26;
const int maxnode = 150 * 70 + 500;
const int maxs = 150 + 10;

map<string, int> ms;

struct AhoCorasickAutomata{
    int ch[maxnode][sigma_size];
    int f[maxnode]; //fail function
    int val[maxnode]; // indicate whether this node is end of a word. 
    int last[maxnode]; //suffix link
    int cnt[maxs];
    int sz;

    void init(){
        sz = 1;
        memset(ch[0], 0, sizeof(ch[0]));
        memset(cnt, 0, sizeof(cnt));
        ms.clear();
    }

    int idx(char c) { return c-'a'; }

    void insert(char * s, int v){
        int u = 0, n = strlen(s);
        for(int i= 0; i < n; i++){
            int c = idx(s[i]);
            if(!ch[u][c]){
                memset(ch[sz], 0, sizeof(ch[sz]));
                val[sz] = 0; 
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        val[u] = v;
        ms[string(s)] = v;
    }

    void print(int j){
        if(j){
            cnt[val[j]]++;
            print(last[j]);
        }
    }

    void find(char * T){
        int n = strlen(T);
        int j = 0;
        for(int i = 0; i < n; i++){
            int c = idx(T[i]);
            //while(j && !ch[j][c]) j = f[j];
            j = ch[j][c];
            if(val[j]) print(j);
            else if(last[j]) print(last[j]);
        }
    }

    void getFail(){
        queue<int> q;
        f[0] = 0;
        for(int c = 0; c < sigma_size; c++){
            int u = ch[0][c];
            if(u) { f[u] = 0; q.push(u); last[u] = 0;}
        }
        while(!q.empty()){
            int r = q.front(); q.pop();
            for(int c = 0; c < sigma_size; c++){
                int u = ch[r][c];
                if(!u) { ch[r][c] = ch[f[r]][c]; continue; }
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
char text[1000001], P[151][80];
int n, T;

int main(){
#ifdef LOCAL
		freopen("UVa.1449.in", "r", stdin);
		freopen("UVa.1449.out", "w", stdout);
#endif
    while(scanf("%d", &n) == 1 && n){
        ac.init();
        for(int i = 1; i <= n; i++){
            scanf("%s", P[i]);
            ac.insert(P[i], i);
        }
        ac.getFail();
        scanf("%s", text);
        ac.find(text);
        int best = -1;
        for(int i = 1; i <= n; i++)
            if(ac.cnt[i] > best) best = ac.cnt[i];
        printf("%d\n", best);
        for(int i = 1; i <= n; i++)
            if(ac.cnt[ms[string(P[i])]] == best) printf("%s\n", P[i]);
    }
    return 0;
}
