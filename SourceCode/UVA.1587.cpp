#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct side{
	int x;
	int y;
};
typedef struct side side;
side a[6];
int myCompare(const void * elemt1, const void * elemt2){
	side * p1, * p2;
	p1 = (side *)elemt1;
	p2 = (side *)elemt2;
	if(p1->x == p2->x) 
		return p1->y - p2->y;
	else
		return p1->x - p2->x;
}

int main(){
#ifdef LOCAL
	freopen("UVA.1587.in", "r", stdin);
	freopen("UVA.1587.out", "w", stdout);
#endif
	int w, h, t;
	while(scanf("%d", &w) != EOF){
		memset(a, 0, sizeof(side));
		scanf("%d", &h);
		if(w>h) {t=w; w=h; h=t;}
		a[0].x=w; a[0].y=h;
		for(int i=1; i<6; i++){
			scanf("%d%d", &w, &h);
			if(w>h) {t=w; w=h; h=t;}
			a[i].x=w; a[i].y=h;
		}
		qsort(a, 6, sizeof(side), myCompare);
		if(a[0].x == a[1].x && a[0].x  == a[2].x && a[0].x == a[3].x
			&& a[0].y == a[1].y && a[0].y == a[4].x && a[0].y == a[5].x
			&& a[2].y == a[3].y && a[2].y == (a[4].y) && a[2].y == (a[5].y))
			printf("POSSIBLE\n");
		else
			printf("IMPOSSIBLE\n");
	}
}

