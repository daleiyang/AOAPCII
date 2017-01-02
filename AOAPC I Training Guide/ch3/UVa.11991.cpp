#include<cstdio>
#include<hash_map>
#include<vector>
using namespace std;
using namespace __gnu_cxx;

hash_map<int, vector<int> > mp;
int n, m, a, b, ans;

int main(){
#ifdef LOCAL
	freopen("UVA.11991.in", "r", stdin);
	freopen("UVA.11991.out", "w", stdout);
#endif
    while(scanf("%d%d", &n, &m) == 2){
        mp.clear();
        for(int i = 0; i < n; i++){
            scanf("%d", &a);
            if(!mp.count(a)) mp[a] = vector<int>();
            mp[a].push_back(i+1);
        }
        while(m--){
            scanf("%d%d", &a, &b);
            ans = 0;
            if(mp.count(b) && (int)mp[b].size() >= a) ans = mp[b][a-1];
            printf("%d\n", ans);
        }
    }
    return 0;
}
