#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 12;

int A[maxn] = {-1, 2, 34, -6, 4, 3, 1, 6, 98, 100, -4, 99};
//int A[maxn] = {1,2,3};
int cnt, T[maxn];

void merge_sort(int * A, int x, int y, int * T){
	if(y-x > 1){
		int m = x+(y-x)/2;
		merge_sort(A, x, m, T);
		merge_sort(A, m, y, T);
		int p = x, q = m, i = x;
		while(p < m || q < y){
			if(q >= y || (p < m && A[p] < A[q])) T[i++] = A[p++];
			else{
				T[i++] = A[q++];
				cnt += m-p;
			}
		}
		for(int i = x; i < y; i++) A[i] = T[i];
	}
}

int main(){
	cnt = 0;
	merge_sort(A, 0, maxn, T);
	printf("%d", cnt);
	return 0;
}

