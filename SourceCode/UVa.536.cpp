#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 26 + 5;
char s[maxn];
int in_order[maxn], pre_order[maxn], lch[maxn], rch[maxn];

int build(int L1, int R1, int L2, int R2){ //L1,R1 for pre_order; L2, R2 for in_order
	if(L1 > R1) return -1;
	int root = pre_order[L1];
	int p = L2;
	while(in_order[p] != root) p++;
	int cnt = p-L2;
	lch[root] = build(L1+1, L1+cnt, L2, p-1);
	rch[root] = build(L1+cnt+1, R1, p+1, R2);
	return root;
}

void post(int root){
	if(root == -1) return;
	post(lch[root]);
	post(rch[root]);
	printf("%c", root+'A');
}

int main(){
#ifdef LOCAL
		freopen("UVa.536.in", "r", stdin);
		freopen("UVa.536.out", "w", stdout);
#endif
	while(scanf("%s", s) == 1){
		int n = strlen(s);
		for(int i = 0; i < n; i++){
			pre_order[i] = s[i]-'A';
		}
		scanf("%s", s);
		for(int i = 0; i < n; i++){
			in_order[i] = s[i]-'A';
		}
		build(0, n-1, 0, n-1);
		post(pre_order[0]);
		printf("\n");
	}
	return 0;
}

