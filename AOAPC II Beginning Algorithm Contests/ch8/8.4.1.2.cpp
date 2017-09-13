#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 10;

int w[maxn] = {1, 2,  3, 4,  5,  6,  7,  8, 9,  10};
int v[maxn] = {6, 4, 24, 4, 10, 18, 49, 64, 27, 100};

struct Node{
	int avg; int idx;
	bool operator < (const Node & rhs) const{
		return avg > rhs.avg;
	}
}N[maxn];

int main(){
	for(int i = 0; i < maxn; i++) printf("%3d ", w[i]); 
	printf("\n");
	for(int i = 0; i < maxn; i++) printf("%3d ", v[i]);
	printf("\n");

	for(int i = 0; i < maxn; i++) {
		N[i].avg = v[i]/w[i];
		N[i].idx = i;
	}
	sort(N, N+maxn);
	for(int i = 0; i < maxn; i++)
		printf("No.%d w:%d v:%d avg:%d\n", i, w[N[i].idx], v[N[i].idx], N[i].avg);
	int C, sum = 0;
	scanf("%d", &C);
	for(int i =0; i < maxn; i++){
		if(sum < C && sum+w[N[i].idx] > C){
			printf("w:%d v:%d take %d\n", w[N[i].idx], v[N[i].idx], C-sum);
			sum += C-sum;
		}
		else if(sum < C && sum+w[N[i].idx] <= C){
			printf("w:%d v:%d\n", w[N[i].idx], v[N[i].idx]);
			sum += w[N[i].idx];
		}
	}
	return 0;
}

