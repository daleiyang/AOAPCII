#include<stdio.h>
int main(){
#ifdef LOCAL
		freopen("2.e.5.4.in", "r", stdin);
		freopen("2.e.5.4.out", "w", stdout);
#endif
	int a, b, c, t, i, tmp, kase = 0;
	int s[110];
	while(scanf("%d%d%d", &a, &b, &c) == 3 && !((a == 0) && (b == 0) && (c == 0))){
		t = a / b;
		a = a % b * 10;
		for(i = 1; i < c; i++){
			s[i] = a / b;
			a = a % b * 10;
		}
		tmp = a % b * 10 / b;
		if(tmp < 5)
			s[i] = a / b;
		else
			s[i] = a / b +1;
/*
		for(int j = 1; j<= c; j++){
			printf("%d\n", s[j]);
		}
*/
		while(i > 1){
			if(s[i] == 10){
				s[i] -= 10;
				s[i-1] += 1;
			}
			i--;
		}
		if(s[1] == 10){
			s[1] -= 10;
			t += 1;
		}
		printf("Case %d: %d.", ++kase, t);
		for(i = 1; i <= c; i++){
			printf("%d", s[i]);
		}
		printf("\n");
	}
	return 0;
}

