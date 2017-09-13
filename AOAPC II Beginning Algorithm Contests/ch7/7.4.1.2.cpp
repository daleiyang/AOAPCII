#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 8;
int cnt, vis[3][100];

void search(int cur){
	if(cur == maxn) cnt++;
	else{
		for(int i = 0; i < maxn; i++){
			if(!vis[0][i] && !vis[1][cur+i] && !vis[2][cur-i+maxn]){
				vis[0][i] = vis[1][cur+i] = vis[2][cur-i+maxn] = 1;
				search(cur+1);
				vis[0][i] = vis[1][cur+i] = vis[2][cur-i+maxn] = 0;
			}
		}
	}
}

int main(){
	cnt  = 0;
	memset(vis, 0, sizeof(vis));
	search(0);
	printf("%d", cnt);
	return 0;
}

