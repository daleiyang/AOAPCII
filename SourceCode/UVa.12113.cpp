#include<cstdio>
#include<cstring>
#include<ctime>
using namespace std;

const int R = 5, C = 9, N = 9;

char T[R][C], A[R][C];
int center[N][2] = {{1, 2}, {1, 4}, {1, 6}, {2, 2}, {2, 4}, {2, 6}, {3, 2}, {3, 4}, {3, 6}};

bool input(){
	char s[100];
	for(int i = 0; i < 5; i++){
		fgets(s, 100, stdin);
		for(int j = 0; j < 10; j++){
			if(j == 0 && s[j] == '0') return false;
			if(s[j] == '#') break;
			else T[i][j] = s[j];
		}
	}
	return true;
}

bool dfs(int d){
	if(!memcmp(A, T, sizeof(T))) 
		return true;
	if(d == 6) return false;

	int b[R][C];
	memcpy(b, A, sizeof(b));
	for(int i = 0; i < N; i++){
		//draw the border
		int x = center[i][0];
		int y = center[i][1];
		A[x-1][y-1] = A[x-1][y+1] = '_'; //up
		A[x+1][y-1] = A[x+1][y+1] = '_'; //down
		A[x][y-2] = A[x+1][y-2] = '|'; //left
		A[x][y+2] = A[x+1][y+2] = '|'; //right		
		//clean insider
		A[x][y] = A[x][y-1] = A[x][y+1] = A[x+1][y] = ' ';
		if(dfs(d+1)) return true;
		memcpy(A, b, sizeof(A));
	}
	return false;
}

int main(){
#ifdef LOCAL
		freopen("UVa.12113.in", "r", stdin);
		freopen("UVa.12113.out", "w", stdout);
#endif
	int kase = 0;
	while(input()){
		printf("Case %d: ", ++ kase);
		memset(A, ' ', sizeof(A));
		if(dfs(0)) printf("Yes\n");
		else printf("No\n");
	}
	//printf("Time used = %.4f\n", (double)clock()/CLOCKS_PER_SEC);
	return 0;
}

