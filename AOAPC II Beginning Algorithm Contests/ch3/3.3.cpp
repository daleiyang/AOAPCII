#include<stdio.h>
#include<string.h>
const int max = 20;
int a[max][max];

int main(){
	memset(a, 0, sizeof(a));
	int n, x, y, i;
	scanf("%d", &n);
	i = a[x = 0][y = n - 1] = 1;
	while(i < n * n){
		while((x+1) < n && !a[x+1][y]) a[++x][y] = ++i;
		while((y-1) >= 0 && !a[x][y-1]) a[x][--y] = ++i;
		while((x-1) >= 0 && !a[x-1][y]) a[--x][y] = ++i;
		while((y+1) < n && !a[x][y+1]) a[x][++y] = ++i;
	}

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++)
			printf("%-3d", a[i][j]);
		printf("\n");
	}
	return 0;
}

