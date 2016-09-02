#include<cstdio>
#include<cstring>
#include<cctype>
#include<stack>
#include<utility>
using namespace std;

typedef pair<int, int> PII;

int len, len2;
char s[20], c[20];
bool ans;

void print(){
	printf("  ");
	for(int i = 0; i < len2; i++){
		if(c[i] == 'D') continue;
		else if(c[i] == 'A') printf("*");
		else if(c[i] == 'B') printf("+");
		else if(c[i] == 'C') printf("-");
		else printf("%c", c[i]);
	}
	printf("=\n");
}

void validate(){
	int idx = 0;
	bool valid = false;
	char buff[10];
	stack<PII> st;
	deque<PII> dq;
	
	for(int i = 0; i < len2; i++){
		if(c[i] == 'A' || c[i] =='B' || c[i] == 'C' ) {valid = true;} //need at least one op
		if(c[i] == 'D') continue; //ignore black space
		
		if(isalpha(c[i]) || (i == len2-1)){
			//parse number
			if(i == len2 -1){
				buff[idx++] = c[i];
			}
			if(idx > 1 && buff[0] == '0') return; //such as "03"
			int v = 0;
			for(int j = 0; j < idx; j++){
				v = v*10+buff[j]-'0';
			}
			if(v == 0 && idx > 1) return; //such as ''00"

			//push numver into stack
			if(!dq.empty()){
				if(dq.back().first == 0 && dq.back().second == 0){   //o for *, 1 for +, 2 for -
					dq.pop_back();
					int left = dq.back().second;
					dq.pop_back();
					dq.push_back(PII(1, left*v));
				}else{
					dq.push_back(PII(1, v));
				}
			}else{
				dq.push_back(PII(1, v));
			}

			//push op into stack
			if(i < len2-1) {
				int op;
				if(c[i] == 'A') op = 0;
				else if(c[i] == 'B') op = 1;
				else if(c[i] == 'C') op = 2;
				dq.push_back(PII(0, op));
			}
			idx = 0;
		}
		else buff[idx++] = c[i];
	}

	if(!valid) return;

	int left, right, op;
	while(1){
		left = dq.front().second;
		dq.pop_front();
		if(!dq.empty()) {
			op = dq.front().second;
			dq.pop_front();
			right = dq.front().second;
			dq.pop_front();
			if(op == 1) left = left + right;
			else if(op == 2) left = left - right;
			dq.push_front(PII(1, left));
		}
		else {
			if(left == 2000){
				ans = true;
				print(); 
				return;
			}
			else return;
		}
	}
}

void dfs(int d){
	if(d == len){
		validate();
		return;
	}
	c[d*2] = s[d];
	if(d == len-1) {
		dfs(d+1);
	}
	else{
		//A for *, B for +, C for -, D for space
		for(int i = 0; i < 4; i++){ 
			c[d*2+1] = 'A'+i;
			dfs(d+1);
		}
	}
}

int main(){
#ifdef LOCAL
	freopen("UVa.817.in", "r", stdin);
	freopen("UVa.817.out", "w", stdout);
#endif
	int kase = 0;
	while(scanf("%s", s) == 1 && s[0] != '='){
		printf("Problem %d\n", ++kase);
		len = strlen(s);
		len--; len2 = 2*len-1;
		ans = false;
		dfs(0);
		if(!ans){printf("  IMPOSSIBLE\n");}
	}
	return 0;
}

