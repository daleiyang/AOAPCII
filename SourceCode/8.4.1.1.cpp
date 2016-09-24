#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 10;

int A[maxn] = {50, 1, 99, 40, 34, 87, 2, 2, 9, 10};

int main(){
	for(int i = 0; i < maxn; i++) printf("%d ", A[i]);
	printf("\n");
	sort(A, A+10);
	for(int i = 0; i < maxn; i++) printf("%d ", A[i]);
	printf("\n");
	int n;
	scanf("%d", &n);
	int sum = 0;
	for(int i = 0; i < maxn; i++){
		if(sum+A[i] < n) {
			sum += A[i];
			printf("%d ", A[i]);
		}
		else break;
	}
	return 0;
}

