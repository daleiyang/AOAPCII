#include<stdio.h>
char s[] = "`1234567890-=QWERTYUIOP[]\\ASDFGHJKL;\'ZXCVBNM,./";
int main(){
#ifdef LOCAL
	freopen("UVA.10082.in", "r", stdin);
	freopen("UVA.10082.out", "w", stdout);
#endif
	int i, c;
	while((c = getchar()) != EOF){
		for(i = 1; s[i] && s[i] != c; i++);
		if(s[i]) putchar(s[i-1]);
		else putchar(c);
	}
	return 0;
}

