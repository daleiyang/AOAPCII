#include<stdio.h>
int main(){
	int n = 0;
	char c;
	while((c = getchar()) != EOF)
		if(c == '1') n++;
	printf("%d\n", n);
	return 0;
}

