#include<stdio.h>
#include<string.h>
#include<stdlib.h>
const int maxn = 30;
int a[maxn], b[maxn];
int myCompare(const void * elem1, const void * elem2){
	return *(int *)elem1 - *(int *)elem2;
}
int main(){
#ifdef LOCAL
	freopen("UVA.1339.in", "r", stdin);
	freopen("UVA.1339.out", "w", stdout);
#endif
	char x[105], y[105];
	while(scanf("%s%s", x, y) != EOF){
		memset(a, 0, sizeof(a));
		memset(b, 0, sizeof(b));
		int len=strlen(x);
		for(int i=0; i<len; i++) a[x[i]-'A']++;
		for(int i=0; i<len; i++) b[y[i]-'A']++;
		qsort(a, maxn, sizeof(int), myCompare);
		qsort(b, maxn, sizeof(int), myCompare);
		int j;
		for(j=0; j<maxn; j++){
			if(a[j]!=b[j]) break;
		}
		if(j==maxn) printf("YES\n");
		else printf("NO\n");
	};
	return 0;
}

