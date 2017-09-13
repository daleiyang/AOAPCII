#include<cstdio>
using namespace std;

void print(int n){
	double ans = 1;
	long long f = 1;
	for(int i = 1; i < n; i++){
		f *= i;
		ans += 1.0/f;
	}
	printf("%d\n", n);
	printf("%.30f\n", ans);
}

int main(){
	for(int i = 2; i < 30; i++){
		print(i);
	}
	return 0;
}

