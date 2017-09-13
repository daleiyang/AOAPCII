#include<stdio.h>
#include<cstdlib>
#include<string.h>
char s[128][10];
char v[105][15];
char k[105][100];
int n=0;
void dic(){
	unsigned char x[2];
	while(scanf("%s", x) == 1 && x[0] != '*'){
		scanf("%s", s[x[0]]);
	}
}
void map(){
	int i=0;
	while(scanf("%s", v[i]) == 1){
		if(v[i][0] == '*') {n=i; return;}
		int idx=0;
		for(unsigned int j=0; j<strlen(v[i]); j++){
			for(unsigned int z=0; z<strlen(s[(unsigned int)v[i][j]]); z++){
				k[i][idx++]=s[(unsigned int)v[i][j]][z];
			}
		}
		k[i][idx]='\0';
		i++;
	}
}
void find(){
	char x[100];
	int f[105];
	for(;;){
		scanf("%s", x);
		if(x[0]=='*') return;
		memset(f, 1, sizeof(f));
		for(unsigned int i=0; i<strlen(x); i++){
			for(int j=0; j<n; j++){
				if(strlen(k[j])<=i || f[j]==0) continue;
				if(x[i] != k[j][i]) {f[j]=0;}
			}
		}
		int d[105];
		for(int j=0; j<n; j++){
			if(f[j]==0) d[j] = -1;
			else d[j] = abs(strlen(x) - strlen(k[j]));
		}
		int c=0, flag=0;
		for(int j=0; j<n; j++){
			if(d[j]==0){
				c++;
				if(!flag) {printf("%s", v[j]); flag=1;}
			}
		}
		if(c>1) printf("!\n");
		else if(flag==1)printf("\n");
		if(flag) continue;
		int min=1000, idx;
		for(int j=0; j<n; j++){
			if(d[j]>0 && d[j]<min){
				min=d[j];
				idx=j;
			}
		}
		printf("%s?\n", v[idx]);
	}
}
int main(){
#ifdef LOCAL
	freopen("UVA.508.in", "r", stdin);
	freopen("UVA.508.out", "w", stdout);
#endif
	dic();
	map();
	find();
	return 0;
}

