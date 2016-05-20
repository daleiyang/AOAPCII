#include<stdio.h>
#include<string.h>
char a[30];
int main(){
#ifdef LOCAL
	freopen("UVA.227.in", "r", stdin);
	freopen("UVA.227.out", "w", stdout);
#endif
	char c;
	int kase = 0;
	while(1){
		memset(a, 0, sizeof(a));
		int n = 1, index;
		do{
			c = getchar();
		}while(c == '\r' || c == '\n');
		if(c == 'Z') break;
		a[n++] = c;
		while(n <= 25){
			c = getchar();
			if(c == '\r' || c == '\n') continue;
			a[n++] = c;
		}
		for(int i = 1; i <=25; i++){
			if(a[i] == ' ') index = i;
		}
		if(kase) printf("\n");
		printf("Puzzle #%d:\n", ++kase);
		int f = 1;
		while((c = getchar()) != '0'){
			switch(c){
				case('A'):{
					if(index < 6) {f = 0; break;}
					else {a[index] = a[index - 5]; index -= 5; a[index] = ' '; break;}
				}
				case('B'):{
					if(index > 20) {f = 0; break;}
					else {a[index] = a[index + 5]; index += 5; a[index] = ' '; break;}
				}
				case('L'):{
					if((index - 1) % 5 == 0) {f = 0; break;}
					else {a[index] = a[index - 1]; index -= 1; a[index] = ' '; break;}
				}
				case('R'):{
					if(index % 5 == 0) {f = 0; break;}
					else {a[index] = a[index + 1]; index += 1; a[index] = ' '; break;}
				}	
				case('\r'):{break;}
				case('\n'):{break;}
				default:{
					f = 0; break;
				}
			}
		}
		if(f == 1){
			for(int i = 1; i <=25; i++){
				if((i-1)%5 == 0) printf("%c ", a[i]);
				else if(i%5 !=0) printf("%c ", a[i]);
				else if(i%5 == 0)printf("%c\n", a[i]);
			}
		}else 
			printf("This puzzle has no final configuration.\n");
	}
	return 0;
}

