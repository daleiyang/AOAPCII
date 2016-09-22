#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 10;

int A[maxn] = {3, 6, 2, 1, 6, 6, 44, 33, 32, 11};

int lower_bound(int * A, int x, int y, int v){
	int m;
	while(x < y){
		m = x + (y-x)/2;
		if(A[m] >= v) y = m;
		else x = m+1;
	}
	return x;
}

int upper_bound(int * A, int x, int y, int v){
	int m;
	while(x < y){
		m = x + (y-x)/2;
		if(A[m] <= v) x = m+1;
		else y = m;
	}
	return x;
}

int main(){
	sort(A, A+10);
	for(int i = 0; i < 10; i++) printf("%d ", A[i]);
	printf("\n");
	
	int t = lower_bound(A, 0, 10, 5);
	printf("%d %d\n", 5, t);
	t = lower_bound(A, 0, 10, 6);
	printf("%d %d\n", 6, t);
	t = lower_bound(A, 0, 10, 1000);
	printf("%d %d\n", 1000, t);

	t = upper_bound(A, 0, 10, 5);
	printf("%d %d\n", 5, t);
	t = upper_bound(A, 0, 10, 6);
	printf("%d %d\n", 6, t);
	t = upper_bound(A, 0, 10, 1000);
	printf("%d %d\n", 1000, t);
	return 0;
}

