#include<cstring>
#include<vector>
using namespace std;

const int maxnode = 4000 * 100 + 10;
const int sigma_size = 26;

struct Trie{
    int ch[maxnode][sigma_size];
    int val[maxnode];
    int sz;
    void clear() {sz = 1; memset(ch[0], 0, sizeof(ch[0]));} 
    int idx(char c) { return c-'a';}

    void insert(const char* s, int v){
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

    void find_prefixes(const char* s, int len, vector<int>& ans){
        int u = 0;
        for(int i = 0; i < len; i++){
            //if(s[i] == '\0') break;
            int c = idx(s[i]);
            if(!ch[u][c]) break;
            u = ch[u][c];
            if(val[u] != 0) ans.push_back(val[u]);
        }
    }
};

#include<cstdio>
const int maxl = 300000+10;
const int maxw = 4000+10;
const int maxwl = 100+10;
const int MOD = 20071027;

int d[maxl], len[maxw], S;
char text[maxl], word[maxwl];
Trie trie;

int main(){
#ifdef LOCAL
		freopen("UVa.1401.in", "r", stdin);
		freopen("UVa.1401.out", "w", stdout);
#endif
    int kase = 0;
    while(scanf("%s%d", text, &S) == 2){
        trie.clear();
        for(int i = 1; i <= S; i++){ //val == 0 means not a word;
            scanf("%s", word);
            len[i] = strlen(word);
            trie.insert(word, i);  
        }
        memset(d, 0, sizeof(d));
        int L = strlen(text);
        d[L] = 1; //guard
        for(int i = L-1; i >= 0; i--){
            vector<int> p;
            trie.find_prefixes(text+i, L-i, p);
            for(int j = 0; j < (int)p.size(); j++)
                d[i] = (d[i] + d[i+len[p[j]]]) % MOD; //great logic here
        }
        printf("Case %d: %d\n", ++kase, d[0]);
    }
    return 0;
}
