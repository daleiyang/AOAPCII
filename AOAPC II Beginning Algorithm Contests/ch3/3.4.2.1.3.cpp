#include<stdio.h>
#include<stdlib.h>
const int maxn = 100;
int a[maxn];
int main(){
	int n = 0;
	while(scanf("%d", &a[n++]) == 1);
	int x, y, c, t;
	if(n > 1) {c = abs(a[1] - a[0]); x = a[0]; y = a[1];}
	else c = 0;
	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			t = abs(a[i] - a[j]);
			if(c > t) {c = t; x = a[i]; y = a[j];}
		}
	}
	printf("%d %d\n", x, y);
	return 0;
}

