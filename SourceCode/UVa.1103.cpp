#include<cstdio>
#include<cstring>
#include<stack>
#include<utility>
using namespace std;

const int maxn = 200 + 10;

int G[maxn][maxn], word[6], h, m, cnt;
int dx[4] = {-1, 1, 0 , 0};
int dy[4] = {0 , 0, -1, 1};
char line[maxn], bin[256][5];
char name[6] =  {'A', 'D', 'J', 'K', 'S', 'W'};

typedef pair<int, int> p;


void init(){
	strcpy(bin['0'], "0000");
	strcpy(bin['1'], "0001");
	strcpy(bin['2'], "0010");
	strcpy(bin['3'], "0011");
	strcpy(bin['4'], "0100");
	strcpy(bin['5'], "0101");
	strcpy(bin['6'], "0110");
	strcpy(bin['7'], "0111");
	strcpy(bin['8'], "1000");
	strcpy(bin['9'], "1001");
	strcpy(bin['a'], "1010");
	strcpy(bin['b'], "1011");
	strcpy(bin['c'], "1100");
	strcpy(bin['d'], "1101");
	strcpy(bin['e'], "1110");
	strcpy(bin['f'], "1111");
}

void decode(char c, int row, int col){
	for(int i = 0; i < 4; i++){
		G[row][col+i] = bin[(int)c][i]-'0';
	}
}

void print(){
	for(int i = 0; i < h; i++){
		for(int j = 0; j < m; j++){
			printf("%d", G[i][j]);
		}
		printf("\n");
	}
}

bool inG(int x, int y){
	return (x >= 0 && x < h && y >= 0 && y < m);
}

void dfs0(int x, int y){
	stack<p> s;
	s.push(p(x, y));
	while(!s.empty()){
		p t = s.top(); s.pop();
		G[t.first][t.second] = -1;
		for(int i = 0; i < 4; i++){
			int nx = t.first + dx[i];
			int ny = t.second + dy[i];
			if(inG(nx, ny) && G[nx][ny] == 0){
				s.push(p(nx, ny));
			}
		}
	}
}


void dfs(int x, int y){	
	if(!inG(x, y) || G[x][y] != 0) return;
	G[x][y] = -1;
	for(int i = 0; i < 4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		dfs(nx, ny);
	}
}


void dfs2(int x, int y){
	if(!inG(x, y) || G[x][y] == -1) return;
	if(!G[x][y]){
		dfs(x, y);
		cnt++;
	}
	G[x][y] = -1;
	for(int i = 0; i < 4; i++){
		int nx = x + dx[i];
		int ny = y + dy[i];
		dfs2(nx, ny);
	}
}

int main(){
#ifdef LOCAL
	freopen("UVa.1103.in", "r", stdin);
	freopen("UVa.1103.out", "w", stdout);
#endif
	int kase = 0;
	init();
	while(scanf("%d%d", &h, &m) == 2 && h && m){
		memset(G, 0, sizeof(G));
		memset(word, 0, sizeof(word));
		for(int i = 1; i <= h; i++){
			scanf("%s", line);
			for(int j = 0; j < m; j++){
				decode(line[j], i, j*4+1);
			}
		}
		h += 2;
		m = m*4+2;
		dfs0(0, 0);
		//print();
		for(int i = 0; i < h; i++){
			for(int j = 0; j < m; j++){
				if(G[i][j] == 1) {
					cnt = 0;
					dfs2(i, j);
					if(cnt == 0){word[5]++;}
					else if(cnt == 1){word[0]++;}
					else if(cnt == 2){word[3]++;}
					else if(cnt == 3){word[2]++;}
					else if(cnt == 4){word[4]++;}
					else if(cnt == 5){word[1]++;}
				}
			}
		}
		printf("Case %d: ", ++kase);
		for(int i = 0; i < 6; i++){
			while(word[i]--){
				printf("%c", name[i]);
			}
		}
		printf("\n");
	}
	return 0;
}

