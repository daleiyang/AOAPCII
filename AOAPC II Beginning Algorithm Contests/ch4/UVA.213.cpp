#include<stdio.h>
#include<string.h>
int codes[8][1<<8];
int readchar(){
	for(;;){
		int ch=getchar();
		if(ch!='\n' && ch!='\r') return ch;
	}
}
int readint(int len){
	int v=0;
	while(len--){
		v=v*2+readchar()-'0';
	}
	return v;
}
int readcodes(){
	memset(codes, 0 , sizeof(codes));
	codes[1][0]=readchar();
	for(int len=2; len<=7; len++){
		for(int i=0; i<((1<<len)-1); i++){
			int ch=getchar();
			if(ch==EOF) return 0;
			if(ch=='\n'||ch=='\r') return 1;
			codes[len][i]=ch;
		}
	}
	return 1;
}
void printcodes(){
	for(int len=1; len<=7; len++){
		for(int i=0; i<((1<<len)-1); i++){
			if(codes[len][i]==0) return;
			printf("codes[%d][%d] = %c\n", len, i, codes[len][i]);
		}
	}
}
int main(){
#ifdef LOCAL
	freopen("UVA.213.in", "r", stdin);
	freopen("UVA.213.out", "w", stdout);
#endif
	while(readcodes()){
		//printcodes();
		for(;;){
			int len=readint(3);
			if(len==0) break;
			//printf("len=%d\n", len);
			for(;;){
				int ch=readint(len);
				//printf("v=%d\n", ch);
				if(ch==((1<<len)-1)) break;
				putchar(codes[len][ch]);
			}
		}
		putchar("\n");
	}
	return 0;
}

