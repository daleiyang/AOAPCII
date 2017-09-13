#include<cstdio>
#include<cctype>
#include<ctime>
using namespace std;

int main(){
#ifdef LOCAL
	freopen("5.1.3.in", "r", stdin);
	freopen("5.1.3.out", "w", stdout);
#endif
	int c, sum=0, num=0;
	while((c=getchar()) != EOF){
		if(c == '\r') continue;
		if(c == '\n') {sum += num; num=0; printf("%d\n", sum); sum=0;}
		if(c == ' ') {sum += num; num=0;}
		if(isdigit(c)){num = num*10 + c - '0';}
	}
	sum += num;
	printf("%d\n", sum);
	printf("Time used = %.5f\n", (double)clock()/CLOCKS_PER_SEC);
	return 0;
}

