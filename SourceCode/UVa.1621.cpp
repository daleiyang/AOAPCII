//http://www.slideshare.net/elizarov/neerc-2012-problem-review
//http://www.cnblogs.com/byene/p/5709159.html
#include <cstdio>
#include<algorithm>

using namespace std;

const int maxn = 5005 * 3;

int a, b, c, ans[maxn], idx;

void add(int x){
	if(abs(x) == 1) a--;
	else if(abs(x) == 2) b--;
	else c--;
  	ans[idx] = ans[idx-1]+x;
	idx++;
}

int main(){
#ifdef LOCAL
		freopen("UVa.1621.in", "r", stdin);
		freopen("UVa.1621.out", "w", stdout);
#endif
	int T;
  	scanf("%d", &T);
	while (T--){
		idx = 0;
		scanf("%d%d%d", &a, &b, &c);
		int n = a + b + c + 1; 
		int x = c/3;
		ans[idx++] = 0;

		//process c
		if (c%3 == 0){
			for(int i = 0; i < x; i++) add(3);
		  	add(1);
		  	for(int i = 0; i < x; i++) add(-3);
		  	add(1);
			for(int i = 0; i < x; i++) add(3);
		}
		else if (c%3 == 1){
			for(int i = 0; i < x+1; i++) add(3);
		  	add(-2);
			for(int i = 0; i < x; i++) add(-3);
		  	add(1);
			for(int i = 0; i < x; i++) add(3);
		  	add(2);
		}
		else if (c%3 == 2){
			for(int i = 0; i < x+1; i++) add(3);
		  	add(-1);
			for(int i = 0; i < x; i++) add(-3);
		  	add(-1);
			for(int i = 0; i < x+1; i++) add(3);
		}

		//process a
		while (a > 1) add(1);

		//process b
		x = b/2;
		int f = b&1;
		while (b > x) add(2);
		if(f) add(-1); else add(1);
		for(int i = 0; i < x; i++) add(-2);

		//print
		for(int i = 0; i < n-1; i++) printf("%d ", ans[i]);
		printf("%d\n", ans[n-1]);
	}
 	return 0;
}

