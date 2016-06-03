#include<stdio.h>
#include<stdlib.h>
const int maxn=30*30+1;
int a[maxn];
int compare(const void * elem1,const void * elem2){
	return *(int *)elem1 - *(int *)elem2;
}
int main(){
#ifdef LOCAL
	freopen("UVA.815.in", "r", stdin);
	freopen("UVA.815.out", "w", stdout);
#endif
	int kase=0, x, y, n, v;
	double len, level;
	while(scanf("%d%d", &x, &y) == 2 && x){
		n=x*y;
		for(int i=1; i<=n; i++){scanf("%d", &a[i]);}
		qsort(a+1, n, sizeof(int), compare);
		scanf("%d", &v);
		len=v/(10*10*1.00);
		printf("Region %d\n", ++kase);
		int pre=0, idx=1, t;
		for(;;){
			if(idx==1 && idx==n){
				level=len+a[idx];
				break;
			}
			if(idx==1){
				idx++;
				continue;
			}
			t=(a[idx]-a[idx-1])*(idx-1);
			if(idx>n || (t+pre)>len){
				level=(len-pre)/(idx-1)+a[idx-1];
				idx--;
				break;
			}
			if((t+pre)<len){
				pre += t; 
				idx++; 
				continue;
			}
			if((t+pre)==len){
				level=a[idx]*1.00;
				idx--;
				break;
			}
		}
		printf("Water level is %.2lf meters.\n", level); 
		printf("%.2lf percent of the region is under water.\n\n", (idx*1.00/n)*100);
	}
	return 0;
}

