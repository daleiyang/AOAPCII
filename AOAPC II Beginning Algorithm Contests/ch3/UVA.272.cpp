#include<stdio.h>
int main(){
#ifdef LOCAL
freopen("UVA.272.in", "r", stdin);
freopen("UVA.272.out", "w",stdout);
#endif
	int c, f = 1;
	while((c = getchar()) != EOF){
		if (c == '"'){
			printf("%s", f ? "``" : "''");
			f =!f;
		}else printf("%c", c);
	}
	return 0;
}

