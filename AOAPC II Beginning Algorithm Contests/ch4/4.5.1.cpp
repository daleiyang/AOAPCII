#include<stdio.h>
int * get_pointer(){
	int a=3;
	return &a;
}
int main(){
	get_pointer();
}

