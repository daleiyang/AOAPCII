#include<stdio.h>
#include<string.h>
#include<math.h>
double a[15][35];

int main(){
#ifdef LOCAL
	freopen("UVA.11809.in", "r", stdin);
	freopen("UVA.11809.out", "w", stdout);
#endif
	double m=1;
	for(int i=0; i <10; i++){
		m /=2;
		int e=2;
		for(int j=1; j<31; j++){
			a[i][j]=log10(2)*(e-1)+log10(1-m);
			e *=2;
		}
	}
	char b[256];
	while(scanf("%s", b) && strcmp(b, "0e0")){
		double x; int y;
		b[17]=' ';
		sscanf(b, "%lf%d", &x, &y);
		double z=log10(x) + y;
		for(int i=0; i<10; i++){
			for(int j=1; j<31; j++){
				if(fabs(a[i][j]-z)<1e-7){
					printf("%d %d\n", i, j);
					goto l;
				}
			}
		}
		l:;
	}
	return 0;
}

