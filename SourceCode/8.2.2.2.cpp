#include<cstdio>
using namespace std;

const int maxn = 10;

int A[maxn] = {3, 6, 2, 1, 10, 98, 44, 33, 32, 11}, k = 8;

int oneRound(int * A, int x, int y){
	int t = A[x], i = x, j = y;
	while(i < j){
		while(i < j && t <= A[j]) j--;
		A[i] = A[j];
		while(i < j && t >= A[i]) i++;
		A[j] = A[i];
	}
	A[i] = t;
	return i;
}

void qsort(int * A, int x, int y){
	if(y-x > 1){
		int p = oneRound(A, x, y);
		if(p+1 >= k) qsort(A, x, p-1);
		else qsort(A, p+1, y);
	}
}

int main(){
	qsort(A, 0, maxn-1);
	printf("%d", A[k-1]);
	return 0;
}

