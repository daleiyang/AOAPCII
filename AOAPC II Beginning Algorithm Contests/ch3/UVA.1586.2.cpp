#include<stdio.h>
#include<string.h>
#include<ctype.h>
const int maxn = 85;
double m[] = {0, 0, 12.01, 0, 0, 0, 0, 1.008, 0, 0, 0, 0, 0, 14.01, 16.00};
int main(){
#ifdef LOCAL
		freopen("UVA.1586.in", "r", stdin);
		freopen("UVA.1586.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	while(T--){
		char a[maxn];
		scanf("%s", a);
		int n = strlen(a);
		double sum = 0;
		for(int i = 0; i < n;){
			if(isalpha(a[i])){
				double q = m[a[i] - 'A'];
				int num = 0;
				for(i++; i < n && isdigit(a[i]); i++){
					num = num * 10 + a[i] - '0';
				}
				num = num == 0 ? 1 : num;
				sum += q * num;
			}else i++; //robustness
		}
		printf("%.3lf\n", sum);
	}
	return 0;
}

