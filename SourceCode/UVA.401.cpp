#include<stdio.h>
#include<ctype.h>
#include<string.h>
const char * m = "A   3  HIL JM O   2TUVWXY51SE Z  8 ";
const char * o[] = {" -- is not a palindrome.", " -- is a regular palindrome.", 
					" -- is a mirrored string.", " -- is a mirrored palindrome."};
char r(char i){
	if(isdigit(i)) return m[i-'0'+25];
	else return m[i - 'A'];
}

int main(){
#ifdef LOCAL
freopen("UVA.401.in", "r", stdin);
freopen("UVA.401.out", "w", stdout);
#endif
	char b[30];
	while(scanf("%s", b) == 1){
		int len = strlen(b);
		int sp = 1, sm = 1;
		for(int i = 0; i < (len + 1)/ 2; i++){
			if(b[i] != b[len - 1 - i]) sp = 0;
			if(r(b[i]) != b[len - 1 - i]) sm = 0;
		}
		printf("%s%s\n\n", b, o[sp + sm * 2]);
	}
	return 0;
}

