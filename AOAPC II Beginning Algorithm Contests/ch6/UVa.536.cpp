#include<cstdio>
#include<cstring>
using namespace std;

char in_order[27], pre_order[27];

void build(int L1, int R1, int L2, int R2){
	if(L1 > R1) return;
	char root = pre_order[L1];
	int p = L2;
	while(in_order[p] != root) p++;
	int cnt = p-L2;
	build(L1+1, L1+cnt, L2, p-1);
	build(L1+cnt+1, R1, p+1, R2);
	printf("%c", in_order[p]);
}

int main(){
#ifdef LOCAL
		freopen("UVa.536.in", "r", stdin);
		freopen("UVa.536.out", "w", stdout);
#endif
	while(scanf("%s", pre_order) == 1){
		scanf("%s", in_order);
		int n = strlen(pre_order);
		build(0, n-1, 0, n-1);
		printf("\n");
	}
	return 0;
}

