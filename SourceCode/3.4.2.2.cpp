#include<stdio.h>
#include<string.h>
#define maxn 10000000 + 10
int main(){
	char s[maxn];
	scanf("%s", s);
	int tot = 0;
	for(unsigned int i = 0; i < strlen(s); i++)
		if(s[i] == 1) tot++;
	printf("%d\n", tot);
}

