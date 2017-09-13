#include<stdio.h>
#include<string.h>
const int maxn=65*100;
char m[7][maxn];
int d, s, b, kase=0;
unsigned int parity;
int read(){
	scanf("%d%d%d", &d, &s, &b);
	if(!d) return 0;
	memset(m, 0, sizeof(m));
	char p[2];
	scanf("%s", p);
	parity = p[0]=='O';
	for(int i=0; i<d; i++) {
		scanf("%s", m[i]);
	}
	return 1;
}
int verify(){
	for(int i=0; i<s*b; i++){
			unsigned int num=parity;
			int n=0, xj=0;
			for(int j=0; j<d; j++){
				if(m[j][i] == 'x'){
					n++; xj=j;
					if(n>1) {return 0;}
					continue;
				}
				num ^= (m[j][i]-'0');
			}
			if(n==0 && num==1) return 0;
			if(n==1) m[xj][i]= num==0?'0':'1';
	}
	return 1;
}
void parse(){
	 int num=0, c=0, df[7];
	 df[0]=0;
	 for(int i=1; i<d; i++) df[i]=df[i-1]+d+1;
	 for(int i=0; i<b*d; i++){
		if(df[i%d]==i){
			df[i%d] += d*d; 
			continue;
		}
		for(int j=0; j<s; j++){
			num = num*2 + (m[i%d][(i/d)*s+j]-'0');
			c++;
			if(c==4){
				printf("%X", num);
				c=0; num=0;
			}
		}
	 }
	 if(c>0){
		for(int i=0; i<4-c; i++) num = num*2;
		printf("%X", num);
	 }
	 printf("\n");
	 return ;
}
int main(){
#ifdef LOCAL
	freopen("UVA.509.in", "r", stdin);
	freopen("UVA.509.out", "w", stdout);
#endif
	int kase=0;
	while(read()){
		if(!verify()){
			printf("Disk set %d is invalid.\n", ++kase);
			continue;
		}
		printf("Disk set %d is valid, contents are: ", ++kase);
		parse();
	}
	return 0;
}

