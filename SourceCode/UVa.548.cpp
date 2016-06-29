#include<cstdio>
#include<string>
#include<iostream>
#include<sstream>
#include<algorithm>
using namespace std;

const int maxn = 10000 + 10;
int inorder[maxn], postorder[maxn], l[maxn], r[maxn], n = 0;

bool read_line(int * order){
	string s;
	if(!getline(cin, s)){return false;};
	stringstream ss(s);
	n = 0;
	int x;
	while(ss >> x){order[n++] = x;}
	return n > 0;
}

int build(int L1, int R1, int L2, int R2){
	if(L1 > R1) return 0;
	int root = postorder[R2];
	int p = L1;
	while(inorder[p] != root) p++;
	int cnt = p - L1;
	l[root] = build(L1, p-1, L2, L2+cnt-1);
	r[root] = build(p+1, R1, L2+cnt, R2-1);
	return root;
}

int best, best_sum;

void dfs(int u, int sum){
	sum += u;
	if(!l[u] && !r[u]){
		if(sum < best_sum || (sum == best_sum && u < best)){
			best = u;
			best_sum = sum;
		}
	}
	if(l[u]) dfs(l[u], sum);
	if(r[u]) dfs(r[u], sum);
}

int main(){
#ifdef LOCAL
	freopen("UVA.548.in", "r", stdin);
	freopen("UVA.548.out", "w", stdout);
#endif
	string s;
	while(read_line(inorder)){
		read_line(postorder);
		build(0, n-1, 0 , n-1);
		best_sum = 100000000;
		dfs(postorder[n-1], 0);
		cout << best << endl;
	}
	return 0;
}

