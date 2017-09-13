#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 10;

int A[maxn] = {70, 95, 60, 65, 50, 45, 80, 100, 90, 94};

int main(){
	for(int i = 0; i < maxn; i++) printf("%4d", A[i]);
	printf("\n");
	sort(A, A+maxn);
	for(int i = 0; i < maxn; i++) printf("%4d", A[i]);
	printf("\n");
	
	int C;
	scanf("%d", &C);

	int i = 0, j = maxn-1, cnt = 0;
	while(i < j){
		if(A[i] + A[j] <= C){
			i++; j--; cnt++; 
		}
		else {
			j--; cnt++;
		}
	}
	if(i == j) cnt++;
	printf("%d", cnt);
	return 0;
}

