#include<stdio.h>
#include<string.h>
int main(){
#ifdef LOCAL
	freopen("UVA.1585.in", "r", stdin);
	freopen("UVA.1585.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	while(T--){
		char s[85];
		scanf("%s", s);
		int n = strlen(s);
		int c = 0, sum = 0;
		for(int i = 0; i < n; i++){
			if(s[i] == 'O'){++c; sum += c;}
			else c = 0;
		}
		printf("%d\n", sum);
	}
	return 0;
}

