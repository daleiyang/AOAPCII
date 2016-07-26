#include<cstdio>
using namespace std;

const int maxn = 1024;
int A[maxn], n, L, cnt;

void print(int cur){
	for(int i = 0; i < cur; i++){
		if(i > 0 && i%64 == 0){
			printf("\n%c", 'A'+A[i]);
		}else if(i > 0 && i%4 == 0){
			printf(" %c", 'A'+A[i]);
		}
		else printf("%c", 'A'+A[i]);
	}
	printf("\n%d\n", cur);
}

int dfs(int cur){
	if(cnt == n){
		print(cur);
		return 0;
	}else{
		for(int i = 0; i < L; i++){
			A[cur] = i;
			int hard = 1;
			for(int j = cur - 1; j >= cur/2; j--){
				int x = j, y = cur, repeat = 1;
				while(y > j){
					if(A[y] != A[x]){
						repeat = 0; 
						break;
					}
					y--; x--;
				}
				if(repeat){
					hard = 0; break;
				}
			}
			if(hard){
				cnt++;
				if(!dfs(cur+1)) return 0;
			}
		}
	}
	return 1;
}

int main(){
#ifdef LOCAL
	freopen("UVa.129.in", "r", stdin);
	freopen("UVa.129.out", "w", stdout);
#endif
	while(scanf("%d%d", &n, &L) == 2 && n){
		cnt = 0;
		dfs(0);
	}
	return 0;
}

