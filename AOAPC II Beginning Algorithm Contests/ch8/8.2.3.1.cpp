#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 10;

int A[maxn] = {3, 6, 2, 1, 10, 98, 44, 33, 32, 11};

int bsearch(int * A, int x, int y, int v){
	int m;
	while(x < y){
		m = x + (y-x)/2;
		if(A[m] == v) return m;
		else if(A[m] > v) y = m;
		else x = m+1;
	}
	return -1;
}

int main(){
	sort(A, A+10);
	int t = bsearch(A, 0, 10, 98);
	printf("%d\n", A[t]);
	t = bsearch(A, 0, 10, 99);
	printf("%d", A[t]);
	return 0;
}

