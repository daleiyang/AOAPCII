#include<stdio.h>
#include<string.h>
int main(){
	char s[20], b[99];
	scanf("%s", s);
	memset(b, 0, sizeof(b));
	int count = 0;
	for(int abc = 100; abc <= 999; abc++){
		for(int de = 10; de <=99; de++){
			int x = abc * (de % 10);
			int y = abc * (de / 10);
			int z = abc * de;
			sprintf(b, "%d%d%d%d%d", abc, de, x, y, z);
			unsigned int i;
			for(i = 0; i < strlen(b); i++)
				if(strchr(s, b[i]) == NULL) break;
			if(i == strlen(b)){
				printf("<%d>\n", ++count);
				printf("%5d\nX%4d\n\n%5d\n%4d\n\n%d\n", abc, de, x, y, z);
			}
		}
	}

	printf("The nmber of solution is = %d", count);
	return 0;
}

