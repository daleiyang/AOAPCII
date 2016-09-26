#include<cstdio>
using namespace std;

int main(){
#ifdef LOCAL
	freopen("UVa.1605.in", "r", stdin);
	freopen("UVa.1605.out", "w", stdout);
#endif
	int n;
	while(scanf("%d", &n) == 1){
		int h = 2, w = n, l = n;
		printf("%d %d %d\n", h, w, l);
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				if(i < 26) printf("%c", 'A'+i);
				else printf("%c", 'a'+i-26);
			}
			printf("\n");
		}
		printf("\n");
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				if(j < 26) printf("%c", 'A'+j);
				else printf("%c", 'a'+j-26);
			}
			printf("\n");
		}
	}
	return 0;
}

