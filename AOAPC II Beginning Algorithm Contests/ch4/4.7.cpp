#include<stdio.h>
int sum(int a[]){
	int ans=0;
	for(unsigned int i=0; i<sizeof(a); i++){
		ans += a[i];
	}
	return ans;
}

int main(){
	int a[]={1,2,3,4};
	printf("%d\n", sum(a));
	return 0;
}

