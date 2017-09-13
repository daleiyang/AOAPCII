#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 200;

int n, t, s[maxn], ans, vis[maxn], mean;

bool cmp(int a, int b){return a > b;}

bool dfs(int cur, int sum, int d){
	if(d == n){
		ans = mean;
		return true;
	}
	for(int i = cur; i < n; i++){ //get subset
		if(vis[i]) continue;
		if(sum + s[i] == mean) {
			vis[i] = 1;
			if(dfs(0, 0, d+1)) return true;//start from index = 1 again to find match combination
			vis[i] = 0;
			
			//prune. if s[i] is the last one to form a stick and following search failed, We need to cancel this dfs call. which means with any s[i] or other elemnets whose
			//sum = s[i], there is no way to resolve remeaning element.
			//In this solution, if we comes there and if we just wan to replace s[i] with s[x] and s[y], x, y > i and s[x]+ s[y] = s[i]. We can say that we find a solution for 
			//current stick, but the question is the remaining elements set is the same as when we get the search failed, with one exception: we repleace s[x], s[y] with
			// s[i]. Think about it, the old set was failed to get the solution, the new set lost s[x] and s[y] and get a new s[i]. All s[i] can do, s[x] and s[y] can do also.
			// So, there couldn't have a workable solution.
			return false;
		}
		else if(sum + s[i] < mean){
			vis[i] = 1;
			if(dfs(i+1, sum+s[i], d+1)) return true;
			vis[i] = 0;
			
			//prune. We can think about it in this way:  we couldn't find a solution in a set, which means we coudn't find a solution in it's sub-set. Very similar with next prune.
			while(i+1 < n && s[i] == s[i+1]) i++;
			
			//prune. we are working on the first part of a new sticks, but this longest one failed to find a workable combination. So, we don't need to move any forward.
			//because, if we ignore this one and wokring on the next one, no matter how the following things hapens, this failed one must have a solition which has been
			// proved impossible.  We can think about it in this way:  we couldn't find a solution in a set, which means we coudn't find a solution in it's sub-set.
			if(sum == 0) return false;
		}
 	}
	return false;
} 

int main(){
#ifdef LOCAL
	freopen("UVa.307.in", "r", stdin);
	freopen("UVa.307.out", "w",stdout);
#endif
	while(scanf("%d", &n) == 1 && n){
		memset(vis, 0, sizeof(vis));
		int sum = 0;
		for(int i = 0; i < n; i++){
			scanf("%d", &s[i]);
			sum += s[i];
		}
		ans = sum;
		sort(s, s+n, cmp); 
		for(mean = s[0]; mean <= sum/2; mean++){
			t = sum % mean;
			if(t == 0) {
				if(dfs(0, 0, 0)) break;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

