#include<cstdio>
#include<utility>
#include<algorithm>
using namespace std;

typedef pair<int, int> P;

const int maxn = 10000 + 5;
int a[maxn], cnt;
P ans[maxn*2];

void sw(int * a, int L, int R){
	if(L >= R) return;
	ans[cnt++] = P(L, R);
	for(int i = L, j = (R-L+1)/2+L; j <= R; i++, j++) swap(a[i], a[j]);
}

int main(){
#ifdef LOCAL
	freopen("UVa.1611.in", "r", stdin);
	freopen("UVa.1611.out", "w", stdout);
#endif
	int T, n;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &n);
		cnt = 0;
		for(int i = 1; i <= n; i++) scanf("%d", &a[i]);
		for(int i = 1; i < n; i++){
			int p;
			for(int j = i; j <= n; j++){
				if(a[j] == i){
					p = j;
					break;
				}
			}
			if(p == i) continue;
			if((p-i+1)%2 == 0){
				sw(a, i, p);
				sw(a, i, p-2);
			}
			else{
				sw(a, i+1, p);
				sw(a, i, p-1);
			}
		}
		printf("%d\n", cnt);
		for(int i = 0; i < cnt; i++) printf("%d %d\n", ans[i].first, ans[i].second);
	}
	return 0;
}

