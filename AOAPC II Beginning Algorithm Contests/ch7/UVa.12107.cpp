#include<cstdio>
#include<cstring>
using namespace std;

char s[3][6];
char change[11] = {'*', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
int len[3], maxd;

int check_result(){
	char check_str[10];
	int t0 = 0, t1 =0, t2;
	for(int i = 0; i < len[0]; i++)
		t0 = t0 * 10 + s[0][i] - '0';
	for(int i = 0; i < len[1]; i++)
		t1 = t1 * 10 + s[1][i] - '0';
	t2 = t0 * t1;
	for(int i = 0; i< len[2]; i++){
		check_str[len[2]-i-1] = t2%10 + '0';
		t2 /= 10;
	}
	if(t2 != 0 || check_str[0] == '0') return 0;
	for(int i = 0; i < len[2]; i++)
		if(check_str[i] != s[2][i] && s[2][i] != '*') return 0;
	return 1;
}

int check(int a, int b){
	int flag = 0;
	if(a == 2){flag = check_result(); return flag;}
	int ta, tb;
	char ch = s[a][b];
	if(b == len[a]-1){ //if current position is the last char in the s[a].
		ta = a+1;
		tb = 0;
	}else{
		ta = a;
		tb = b+1;
	}
	if(s[a][b] == '*'){
		for(int i = 1; i <= 10; i++){
			if(b == 0 && i == 1) continue; //ignore '0'  in the first place of s[a].
			s[a][b] = change[i];
			flag += check(ta, tb);
			if(flag > 1) break; //prune. No need to proceed further.
		}
	}else{
		flag += check(ta, tb);
	}
	s[a][b] = ch;
	return flag;
}

int dfs(int a, int b, int d){
	int flag;
	if(d == maxd){ //replace desired number of changes. 
		flag = check(0, 0); //find the solution number for this combination.
		if(flag == 1) return 1;
		else return 0;
	}
	if(a == 3) return 0;
	int ta, tb;
	char tmp = s[a][b];
	if(b == len[a]-1){ //if current position is the last char in the s[a]
		ta = a+1;
		tb = 0;
	}else{
		ta = a;
		tb = b+1;
	}
	for(int i = 0; i <= 10; i++){
		if(b == 0 && i == 1) continue;  //ignore '0'  in the first place of s[a]
		if(tmp == change[i]){
			s[a][b] = tmp;
			flag = dfs(ta, tb, d); //don't make the change if they are the same;
		}else{
			s[a][b] = change[i];
			flag = dfs(ta, tb, d+1);
		}
		if(flag) break;
	}
	if(!flag) s[a][b] = tmp;
	return flag;
}

int main(){
#ifdef LOCAL
	freopen("UVa.12107.in", "r", stdin);
	freopen("UVa.12107.out", "w", stdout);
#endif
	int kase = 0;
	memset(s, 0, sizeof(s));
	while(scanf("%s%s%s", s[0], s[1], s[2]) == 3){
		for(int i = 0; i < 3; i++) len[i] = strlen(s[i]);
		printf("Case %d: ", ++kase);
		for(int i = 0;; i++){  //because the input guarantee solution existence.
			maxd = i;
			if(dfs(0, 0, 0)){   //s array index, index in each s element, how many item has been changed. This problem ask for minimized the change, so use IDA* to achieve this.
				printf("%s %s %s\n", s[0], s[1], s[2]); 
				break;
			}
		}
		memset(s, 0, sizeof(s));
	}
	return 0;
}

