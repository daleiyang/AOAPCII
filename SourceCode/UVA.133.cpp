#include<stdio.h>
#include<string.h>
int main(){
#ifdef LOCAL
	freopen("UVA.133.in", "r", stdin);
	freopen("UVA.133.out", "w", stdout);
#endif
	int n, k, m, left, a[25], p1, p2, c;
	while(scanf("%d%d%d", &n, &k, &m) == 3 && !(n==0 && k==0 && m==0)){
		memset(a, 0, sizeof(a));
		left = n; p1 = 1; p2 = n;
		while(left){
			c=0;
			while(1){
				if(a[p1]==0 && (++c==k)) break;
				p1= p1==n?1:p1+1;
			}
			c=0;
			while(1){
				if(a[p2]==0 && (++c==m)) break;
				p2= p2==1?n:(p2-1);
			}
			a[p1]=a[p2]=1;
			if(p1!=p2){
				left -=2;
				printf("%3d%3d", p1, p2);
			}
			else{
				left -=1;
				printf("%3d", p1);
			}
			if(left) printf(",");
		}
		printf("\n");
	}
	return 0;
}

