#include<cstdio>
#include<algorithm>
using namespace std;

/* 
         00      01 
         02      03
04 05 06 07  08 09 10 
         11      12 
13 14 15 16 17 18 19 
         20      21 
         22      23 
 */

int line[8][7] = {
		{ 0,  2,  6, 11, 15, 20, 22},	//A
		{ 1,  3,  8, 12, 17, 21, 23},	//B
		{10,  9,  8,  7,  6,  5,  4}, 	//C
		{19, 18, 17, 16, 15, 14, 13}  	//D
};

int center[8] = {6, 7, 8, 11, 12, 15, 16, 17};
int rev[8] = {5, 4, 7, 6, 1, 0, 3, 2};

int a[24];
char ans[1024];

bool is_target(){
	for(int i = 1; i < 8; i++){
		if(a[center[i]] != a[center[0]]) return false;
	}
	return true;
}

int diff(int target){
	int cnt = 0;
	for(int i = 0; i < 8; i++){
		if(a[center[i]] != target) cnt++;
	}
	return cnt;
}

int h(){
	return min(min(diff(1), diff(2)), diff(3));
}

void move(int i){
	int temp = a[line[i][0]];
	for(int j = 0; j < 6; j++){
		a[line[i][j]] = a[line[i][j+1]];
	}
	a[line[i][6]] = temp;
}

bool dfs(int d, int maxd){
	if(is_target()){
		ans[d] = '\0';
		printf("%s\n", ans);
		return true;
	}
	if(d + h() > maxd) return false;
	for(int i = 0; i < 8; i++){
		ans[d] = 'A' + i;
		move(i);
		if(dfs(d+1, maxd)) return true;
		move(rev[i]);
	}
	return false;
}

int main(){
#ifdef LOCAL
		freopen("UVa.1343.in", "r", stdin);
		freopen("UVa.1343.out", "w", stdout);
#endif
	for(int i = 4; i <= 7; i++) for(int j = 0; j <= 6 ; j++){
		line[i][j] = line[rev[i]][6-j];
	}
	
	while(scanf("%d", &a[0]) == 1 && a[0]){
		for(int i = 1; i < 24; i++) scanf("%d", &a[i]);
		if(is_target()){
			printf("No moves needed\n");
		}
		else{
			for(int maxd = 1; ;maxd++){
				if(dfs(0, maxd)) break;
			}
		}
		printf("%d\n", a[6]);
	}
	return 0;
}

