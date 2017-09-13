#include<cstdio>
using namespace std;

const int maxn = 8;
int cnt, C[maxn];

void search(int cur){
	if(cur == maxn) cnt++;
	else{
		for(int i = 0; i < maxn; i++){
			int ok = 1;
			C[cur] = i;
			for(int j = 0; j < cur; j++){
				if(C[cur] == C[j] || cur-C[cur] == j-C[j] || cur+C[cur] == j+C[j]){
					ok = 0; break;
				}
			}
			if(ok){
				search(cur+1);
			}
		}
	}
}

int main(){
	cnt = 0;
	search(0);
	printf("%d", cnt);
	return 0;
}

