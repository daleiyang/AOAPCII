#include<cstdio>
#include<cstring>
#include<cctype>
using namespace std;

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
//condition 1 c[0] == '2' && c[1] == 'C' && c[2] == '6' && c[3] == 'C' && c[4] == '8' && c[5] == 'B' && c[6] == '3' && c[7] == 'A' && c[8] == '6' && c[9] == 'D' && c[10] == '9' && c[11] == 'D' && c[12] == '2' && c[13] == 'C' && c[14] == '6' && c[15] == 'D' && c[16] == '4'
	int idx = 0;
	bool valid = false;
	char buff[10];
	int q[20], front = 0, rear = 0;

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

			//push numver into stack and take care of *
			if(rear > 0){
				if(q[rear-1] == 0){   //0 for *, 1 for +, 2 for -
					rear--;
					int left = q[--rear];
					q[rear++] = left * v;
				}else{
					q[rear++] = v;
				}
			}else{
				q[rear++] = v;
			}

			//push op into stack
			if(i < len2-1) {
				int op;
				if(c[i] == 'A') op = 0;
				else if(c[i] == 'B') op = 1;
				else if(c[i] == 'C') op = 2;
				q[rear++] = op;
			}
			idx = 0;
		}
		else buff[idx++] = c[i];
	}

	if(!valid) return;

	//process the expression from left to right, only include + and -
	int left, right, op;
	left = q[front++];
	if(rear > 1){
		while(front < rear){
			op = q[front++];
			right = q[front++];
			if(op == 1) left = left + right;
			else if(op == 2) left = left - right;
		}
	}
	if(left == 2000){
		ans = true;
		print(); 
	}
	return;
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
