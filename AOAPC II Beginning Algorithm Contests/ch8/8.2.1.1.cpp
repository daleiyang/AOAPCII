#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 12;

int A[maxn] = {-2, 3, 5, 65, 100, 32, -70, 74, 0, 1, 8, 12}, T[maxn];

void merge_sort(int * A, int x, int y, int * T){
	if(y-x > 1){
		int m = x+(y-x)/2;
		merge_sort(A, x, m, T);
		merge_sort(A, m, y, T);
		int p = x, i = x, q = m;
		while(p < m || q < y){
			if(q >= y || (p < m && A[p] <= A[q])) T[i++] = A[p++];
			else T[i++] = A[q++];
		}
		for(int i = x; i < y; i++) A[i] = T[i];
	}
}

int main(){
	merge_sort(A, 0, 12, T);
	return 0;
}

