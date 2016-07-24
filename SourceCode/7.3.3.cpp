#include<cstdio>
using namespace std;

int p[] = {4, 5, 3};

void print_subset(int n, int s){
	for(int i = 0; i < n; i++){
		if(s&(1<<i)) printf("%d ", p[i]);
	}
	printf("\n");
}

int main(){
	int n = 3;
	for(int i = 0; i < (1<<n); i++){
		print_subset(n, i);
	}
	return 0;
}

