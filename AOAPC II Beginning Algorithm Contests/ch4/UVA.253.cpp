#include<stdio.h>
#define CM if(compare(xi, yi)) return 1
#define YI(a,b,c,d) yi[0]=a; yi[1]=b; yi[2]=c; yi[3]=d
#define XI(a,b,c,d) xi[0]=a; xi[1]=b; xi[2]=c; xi[3]=d
#define TE(a,b) x[n]==y[a] && x[m]==y[b]
char x[10], y[10];
int compare(int * xi, int * yi){
	for(int i=0; i<4; i++){
		int j;
		for(j=0; j<4; j++){
			if(x[xi[j]]!=y[yi[(i+j)%4]]) break;
		}
		if(j==4) return 1;
	}	
	return 0;
}
int find(int n, int m){
	int xi[4], yi[4];
	if(n==1 && m==6) {XI(2,3,5,4);}
	if(n==2 && m==5) {XI(3,1,4,6);}
	if(n==3 && m==4) {XI(1,2,6,5);}
	if(TE(1,6)) {YI(2,3,5,4); CM;}
	if(TE(6,1)) {YI(2,4,5,3); CM;}
	if(TE(2,5)) {YI(3,1,4,6); CM;}
	if(TE(5,2)) {YI(3,6,4,1); CM;}
	if(TE(3,4)) {YI(1,2,6,5); CM;}
	if(TE(4,3)) {YI(1,5,6,2); CM;}
	return 0;
}
int main(){
#ifdef LOCAL
	freopen("UVA.253.in", "r", stdin);
	freopen("UVA.253.out", "w", stdout);
#endif
	char a[15];
	while(scanf("%s", a) != EOF){
		for(int i = 0; i < 6; i++) {x[i+1]=a[i];}
		for(int i = 6, j = 1; i < 12; i++, j++) {y[j]=a[i];}
		if(find(1,6)||find(2,5)||find(3,4)) printf("TRUE\n");
		else printf("FALSE\n");
	}
	return 0;
}

