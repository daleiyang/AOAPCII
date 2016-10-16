#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 100 + 5;
char a[maxn], b[maxn];

int main(){
#ifdef LOCAL
		freopen("UVa.12545.in", "r", stdin);
		freopen("UVa.12545.out", "w", stdout);
#endif
	int n, len;
	scanf("%d", &n);
	for(int t = 1; t <= n; t++){
		scanf("%s", a);
		scanf("%s", b);
		len = strlen(a);
		int a0n = 0, aqn = 0, b0n = 0;
		for(int i = 0; i < len; i++){
			if(a[i] == '0') a0n++;
			if(a[i] == '?') aqn++;
			if(b[i] == '0') b0n++;
		}
		if(a0n + aqn < b0n) {
			printf("Case %d: -1\n", t);
			continue;
		}
		int ans = 0;
		if(a0n < b0n){
			for(int i = 0; a0n < b0n && i < len; i++){
				if(a[i] == '?' && b[i] == '0') {
					a[i] = '0'; a0n++; ans++;
				}
			}
			for(int i = 0; a0n < b0n && i < len; i++){
				if(a[i] == '?') {
					a[i] = '0'; a0n++; ans++;
				}
			}
		}

		if(a0n > b0n){
			for(int i = 0; a0n > b0n && i < len; i++){
				if(a[i] == '0' && b[i] == '1') {
					a[i] = '1'; a0n--; ans++;
				}
			}
		}

		for(int i = 0; i < len; i++){
				if(a[i] == '?') {
					a[i] = '1'; ans++;
				}
		}

		int cnt = 0;
		for(int i = 0; i < len; i++){
			if(a[i] != b[i]) cnt++;
		}

		ans += cnt/2;
		printf("Case %d: %d\n", t, ans);
	}
	return 0;
}

