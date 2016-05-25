#include<stdio.h>
int sum(int * start, int * end){
	int n=end-start;
	int ans=0;
	for(int i=0; i<n; i++){
		ans += start[i];
	}
	return ans;
}
int sum2(int * start, int * end){
	int * p;
	int ans=0;
	for(p=start; p!=end; p++){
		ans +=*p;
	}
	return ans;
}
int main(){
	int a[]={1,2,3,4};
	printf("%d\n", sum(a, a+4));
	printf("%d\n", sum2(a, a+4));
	return 0;
}

