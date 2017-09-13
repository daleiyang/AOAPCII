#include<stdio.h>
#include<string.h>
const int max = 1010;
int main(){
#ifdef LOCAL
	freopen("UVA.340.in", "r", stdin);
	freopen("UVA.340.out", "w", stdout);
#endif
	int n, c = 0;
	while(scanf("%d", &n) == 1 && n){
		int code[max], guess[max], a[10], b[10];
		memset(a, 0, sizeof(a));
		for(int i = 0; i < n; i++){
			scanf("%d", &code[i]);
			a[code[i]]++;
		}
		printf("Game %d:\n", ++c);
		for(;;){
			int f = 1, s = 0,w = 0;
			memset(b, 0, sizeof(b));
			for(int i = 0; i < n; i++){
				scanf("%d", &guess[i]);
				if(guess[i] != 0 ) f = 0;
				if(code[i] == guess[i]) s++;
				b[guess[i]]++;
			}
			if(f) break;
			for(int i = 1; i <=9; i++)
				w += a[i] < b[i] ? a[i]:b[i];
			printf("    (%d,%d)\n", s, w - s);
		}
	}
	return 0;
}

