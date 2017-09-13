#include<cstdio>
using namespace std;

const int maxn = 100000 + 5;
char a[maxn];

int main(){
#ifdef LOCAL
		freopen("UVa.11491.in", "r", stdin);
		freopen("UVa.11491.out", "w", stdout);
#endif
	int d, n;
	while(scanf("%d %d", &n, &d) == 2 && n){
		getchar();
		int cnt = 0, t = n-d;
		for(int i = 0; i < n; i++){
			char c = getchar();
			while(cnt && cnt+n-i > t && a[cnt]<c) --cnt;
			if(cnt < t) a[++cnt] = c;
		}
		a[cnt+1] = '\0';
		puts(a+1);
	}
	return 0;
}

