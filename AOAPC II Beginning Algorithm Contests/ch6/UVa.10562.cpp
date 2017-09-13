#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 200 + 5;
char G[maxn][maxn];
int n;

bool isNode(char c){
	return (c != '-') && (c != '|') && (c != ' ') && (c != '#') && (c != '\n');
}

void build(int row, int col){
	printf("%c(", G[row][col]);
	if((row < n -1) && (G[row + 1][col] == '|')){
		int le = col;
		while(le >= 0  && G[row + 2][le] == '-') le--;
		le++;
		while(G[row + 2][le] == '-' &&  G[row + 3][le] != '\0'){
			if(isNode(G[row + 3][le])){build(row + 3, le);}
			le++;
		}
	}
	printf(")");
}

void solve(){
	printf("(");
	if(n){
		for(unsigned int i = 0; i < strlen(G[0]); i++)
			if(isNode(G[0][i])){ build(0, i);} //print subtree for this node.	
	}
	printf(")\n");
}

int main(){
#ifdef LOCAL
	freopen("UVa.10562.in", "r", stdin);
	freopen("UVa.10562.out", "w", stdout);
#endif
	int T;
	fgets(G[0], maxn, stdin);
	sscanf(G[0], "%d", &T);
	while(T--){
		n = 0;
		for(;;){
			fgets(G[n], maxn, stdin);
			if(G[n][0] == '#') break;
			else n++;
		}
		solve();
	}
	return 0;
}

