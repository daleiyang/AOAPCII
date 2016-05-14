#include<stdio.h>
int main()
{
	int i, j, t, k, m;
	while(scanf("%d%d", &i, &j) == 2){
		k = i; m = j;
		if(i > j) {t = i; i = j; j = t;}
		int max = 0;
		for(int x = i; x <= j; x++){
			int count = 1;
			long long n = x;
			while(n > 1){
				if(n % 2 == 1)
					n = n * 3 + 1;
				else
					n = n / 2;
				count++;
			}
			if(count > max)
				max = count;
		}
		printf("%d %d %d\n", k, m, max);
	}
	return 0;
}

