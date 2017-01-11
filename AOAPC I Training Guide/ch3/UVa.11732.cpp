#include<cstring>
using namespace std;

const int maxnode = 4000*1000+10;

struct Trie{
    int head[maxnode]; //left child node idx
    int next[maxnode]; //brother node idx
    char ch[maxnode]; //char in the node
    int tot[maxnode]; //how many word go through this node
    int sz; //total node number
    long long ans;

    void clear(){sz = 1; head[0] = next[0] = tot[0] = 0;}

    void insert(const char *s){
        int u = 0, v, n = strlen(s);
        tot[0]++;
        for(int i = 0; i <= n; i++){
            bool f = false;
            for(v = head[u]; v != 0; v = next[v]) //start from child of u and search all it's brother
                if(ch[v] == s[i]){
                    f = true;
                    break;
                }
            if(!f){
                v = sz++;
                tot[v] = 0;
                ch[v] = s[i];
                next[v] = head[u];
                head[u] = v;
                head[v] = 0;
            }
            u = v;
            tot[u]++;
        }
    }

    //too difficult...
    void dfs(int depth, int u){
         /*  try this case for leaf calculation logic
                4
                abc
                abc
                acd
                acd
            when head[u] == 0, which mean we hit '\0' node for abc & abc or acd & acd nodes
            the tot[u] is 2, so the total compare for abc & abc is 2 * 4 (depth:a,b,c,'\0') 
            if we have tot[u] > 2, it's not difficult to know the compare for each node should
            be tot[u] * (tot[u]-1)
        */
        if(head[u] == 0)
            ans += tot[u] * (tot[u]-1) * depth;
        else{
            /* Logic for non-leaf node:
               we need to detect comparison not match case here and calculate comparison count
               until this miss-match happens.
               So, if tot[u] == tot[v], which means no miss match happens, we go on. No miss match
               count needed. If tot[u] != tot[v], such as: abc & acd, the logic leverage the different 
               between tot[u] and tot[v] to find out miss match string comparison count (only inlucde
               miss match string hapeens in this node). Based on this logic, it's not hard to understand
               we calculate tot[v] * (tot[u] - tot[v]) for each nodes (such as 'c' abd 'b' in this case)
               After we get a sum count, we divided it by 2 to remove duplicate count.
               The miss match string comparsion count will based on this division result.
               It's not too diificult to know the matching part for these missing string's comparsion count
               should be same as this division result. But we need to *2 to inlcude s[i] == '\0' after each 
               match. for miss match comparsion, we need +1. So, we get a sum/2*(2*depth+1).

               One more thing is about depth number, just draw the tree, you will know the depth is exactly
               the number we need.  
            */
            int sum = 0;
            for(int v = head[u]; v != 0; v = next[v])
                sum += tot[v] * (tot[u] - tot[v]);
            ans += sum/2*(2*depth+1); 
            //go deeper for match part.
            for(int v = head[u]; v != 0; v = next[v])
                dfs(depth+1, v);
        }
    }

    long long count(){
        ans = 0;
        dfs(0, 0);
        return ans;
    }
};

#include<cstdio>

const int maxl = 1000 + 10;

int n;
char word[maxl];
Trie trie;

int main(){
#ifdef LOCAL
		freopen("UVa.11732.in", "r", stdin);
		freopen("UVa.11732.out", "w", stdout);
#endif
    int kase = 0;
    while(scanf("%d", &n) == 1 && n){
        trie.clear();
        for(int i  = 0; i < n; i++){
            scanf("%s", word);
            trie.insert(word);
        }
        printf("Case %d: %lld\n", ++kase, trie.count());
    }
    return 0;
}
