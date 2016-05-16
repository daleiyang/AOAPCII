#include<stdio.h>
int main(){
	FILE * fin, * fout;
	fin = fopen("data.in", "rb");
	fout = fopen("data.out", "wb");

	int n, min = 0, max = 0, c = 0, sum = 0;
	fscanf(fin, "%d", &n);
	min = max = n;
	sum += n; c++;

	while(fscanf(fin, "%d", &n) == 1){
		if(min > n) min = n;
		if(max < n) max = n;
		sum += n;
		c++;
	}
	fprintf(fout, "%d %d %.3f", min, max, (double)sum / c);
	fclose(fin);
	fclose(fout);
	return 0;
}

