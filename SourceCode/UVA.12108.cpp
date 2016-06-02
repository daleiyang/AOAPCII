#include<stdio.h>
#include<string.h>
char a[11][200], h[5000][200];
int b[11], len[11], n;
int read(){
	scanf("%d", &n);
	if(n==0) return 0;
	int x, y, z;
	for(int i=0; i<n; i++){
		scanf("%d%d%d", &x, &y, &z);
		for(int j=0; j<x; j++) a[i][j]='W';
		for(int j=x; j<x+y; j++) a[i][j]='S';
		b[i]=z-1;
		len[i]=x+y;
	}
	return 1;
}
int repeat(int step){
	int idx=0;
	for(int i=0; i<n; i++)
		for(int k=0; k<len[i]; k++)
			h[step][idx++]=a[i][(b[i]+k)%len[i]];
	h[step][idx]='\0';
	for(int i=1; i<step; i++)
		if(strcmp(h[i], h[step])==0) return 1;
	return 0;
}
int main(){
#ifdef LOCAL
		freopen("UVA.12108.in", "r", stdin);
		freopen("UVA.12108.out", "w", stdout);
#endif
	int kase=0;
	while(read()){
		int step=1;
		for(;;){
			int w=0, s=0;
			for(int i=0; i<n; i++){if(a[i][b[i]]=='W') w++; else s++;}
			if(w==n) {printf("Case %d: %d\n", ++kase, step); break;}
			if(repeat(step)) {printf("Case %d: -1\n", ++kase); break;}
			for(int i=0; i<n; i++){
				if(a[i][b[i]]=='W' && a[i][(b[i]+1)%len[i]]=='S' && s<=w) b[i]=0;
				else b[i]=(b[i]+1)%len[i];
			}
			step++;
		}
	}
	return 0;
}

