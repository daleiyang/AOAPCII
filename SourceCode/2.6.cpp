#include<stdio.h>
int main(){
	double sum = 0;
	for(int i = 0; ;i++){
		double step = 1.0 / (2 * i + 1);
		if(i % 2 == 0) sum += step;
		else sum -= step;
		if(step < 1e-6) break;
	}
	printf("%.6lf", sum);
	return 0;
}

