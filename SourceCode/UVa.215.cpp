#include<cstdio>
#include<cstring>
#include<cctype>
#include<vector>
using namespace std;

const int r = 20+1, c = 10+1, len = 75+1;

struct node{
	int type; // 1 means value, 2 means expression
	int sign; // 1 mean '+', -1 means '-'
	int r, c;
	int value;// if this node is value not expression
	node(int type, int sign = 0, int r = 0, int c = 0, int value = 0)
		:type(type), sign(sign), r(r), c(c), value(value){}
};
vector<node> v[r][c];
int type[r][c], value[r][c], circle[r][c], vis[r][c], n, m;
char exp[r][c][len];

void input(){
	memset(v, 0, sizeof(v));
	memset(type, 0, sizeof(type));
	memset(value, 0, sizeof(value));
	memset(circle, 0, sizeof(circle));
	memset(exp, 0, sizeof(exp));
	
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			scanf("%s", exp[i][j]);
			int slen = strlen(exp[i][j]);
			int idx = 0, sign;
			if(isalpha(exp[i][j][0])){
				v[i][j].push_back(node(2, 1, exp[i][j][0]-'A', exp[i][j][1]-'0', 0));
				idx = 2;
			}else{
				int t = 0;
				if(exp[i][j][0] == '-') {idx = 1; sign = -1;} else {idx = 0; sign = 1;}
				do{t = t*10 + exp[i][j][idx++]-'0';}
				while(isdigit(exp[i][j][idx]));
				v[i][j].push_back(node(1, sign, 0, 0, t));
			}
			while(idx < slen && (exp[i][j][idx] == '+' || exp[i][j][idx] == '-')){
					sign = exp[i][j][idx] == '+' ? 1 : -1;
					idx++;
					if(isdigit(exp[i][j][idx])){
						int t = 0;
						do{t = t*10 + exp[i][j][idx++]-'0';}
						while(isdigit(exp[i][j][idx]));
						v[i][j].push_back(node(1, sign, 0, 0, t));
					}
					else if(isalpha(exp[i][j][idx])){
						v[i][j].push_back(node(2, sign, exp[i][j][idx]-'A', exp[i][j][idx+1]-'0', 0));
						idx += 2;
					}
			}
			type[i][j] = 2; //is express;
		}
	}
}

bool calculate(int & w, int r, int c){
	if(type[r][c] == 1){
		w = value[r][c];
		return true;
	}else{
		vis[r][c] = -1; int z = 0;
		for(unsigned int i = 0; i < v[r][c].size(); i++){
			if(v[r][c][i].type == 2 && vis[v[r][c][i].r][v[r][c][i].c] < 0) {return false;}
			else{
				int t;
				if(v[r][c][i].type == 1) {t = v[r][c][i].value;}
				else if(v[r][c][i].type == 2){
					if(!calculate(t, v[r][c][i].r, v[r][c][i].c)){return false;}
				}
				z += t * v[r][c][i].sign;
			}
		}
		w = z; 
		value[r][c] = z;
		type[r][c] = 1;
		vis[r][c] = 0;
		return true;
	}
}

void solve(){
	bool f = true; int x;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			memset(vis, 0, sizeof(vis));
			if(!calculate(x, i, j)){
				circle[i][j] = 1;
				if(f) f = false;
			}
		}
	}
	if(f){
		for(int i = 0; i < m; i++){
			if(i) {printf("     %d", i);}
			else  {printf("      %d", i);}
		}
		printf("\n");
		for(int i = 0; i < n; i++){
			printf("%c", 'A'+i);
			for(int j = 0; j < m; j++){
				printf("%6d", value[i][j]);
			}
			printf("\n");
		}
	}
	else{
		for(int i = 0; i < n; i++){
			for(int j = 0; j < m; j++){
				if(circle[i][j] == 1){
					printf("%c%d: %s\n", 'A'+i, j, exp[i][j]);
				}
			}
		}
	}
}

int main(){
#ifdef LOCAL
		freopen("UVa.215.in", "r", stdin);
		freopen("UVa.215.out", "w", stdout);
#endif
	while(scanf("%d%d", &n, &m) == 2 && n && m){
		input();
		solve();
		printf("\n");
	}
	return 0;
}

