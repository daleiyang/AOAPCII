#include<cstdio>
#include<cstring>
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

int best, best_sum;

int build(int L1, int R1, int L2, int R2, int sum){
	if(L1 > R1) {return 0;}
	int root = postorder[R2];
	sum += root;
	int p = L1;
	while(inorder[p] != root) p++;
	int cnt = p - L1;
	l[root] = build(L1, p-1, L2, L2+cnt-1, sum);
	r[root] = build(p+1, R1, L2+cnt, R2-1, sum);
	if(!l[root] && !r[root]){
		if(sum < best_sum || (sum == best_sum && L1 < best)){
			best = inorder[L1];
			best_sum = sum;
		}
	}
	return root;
}

int main(){
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("UVA.548.in", "r", stdin);
	freopen("UVA.548.out", "w", stdout);
#endif
	while(read_line(inorder)){
		read_line(postorder);
		best_sum = 100000000;
		build(0, n-1, 0 , n-1, 0);
		cout << best << endl;
	}
	return 0;
}

