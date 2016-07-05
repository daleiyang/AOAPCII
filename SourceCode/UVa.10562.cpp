#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 200 + 5;
char G[maxn][maxn];
int n;

void print(){
	for(int i = 0; i < n; i++)
		for(unsigned j = 0 ; j < strlen(G[i]); j++)
			printf("%c", G[i][j]);
}

bool isNode(char c){
	return (c != '-') && (c != '|') && (c != ' ') && (c != '#') && (c != '\n');
}

void build(int row, int col){
	if(row >= n - 1) return;
	int le = col, ri = col;
	if(G[row + 1][col] == '|'){
		while(le >= 0  && G[row + 2][le] == '-') le--;
		while(G[row + 2][ri] == '-') ri++;
	}
	le++; ri--;
	int len = strlen(G[row + 3]);
	for(int i = le; i <= ri && i < len; i++){
		if(isNode(G[row + 3][i])){
			printf("%c(", G[row + 3][i]);
			build(row + 3, i);
			printf(")");
		}
	}
}

void solve(){
	printf("(");
	if(n > 0){
		for(unsigned int i = 0; i < strlen(G[0]); i++){
			if(isNode(G[0][i])){
				printf("%c(", G[0][i]);
				build(0, i); //print subtree for this node.
				printf(")");
			}	
		}
	}
	printf(")\n");
}

int main(){
#ifdef LOCAL
	freopen("UVa.10562.in", "r", stdin);
	freopen("UVa.10562.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T); fgets(G[maxn], maxn, stdin);
	while(T--){
		memset(G, 0, sizeof(G));
		n = 0;
		for(;;){
			fgets(G[n], maxn, stdin);
			if(G[n][0] == '#') break;
			n++;
		}
		//print();
		solve();
	}
	return 0;
}

