#include<cstdio>
#include<cstring>
using namespace std;

const int maxnode = 4000004;
const int digit_size = 10;
int ch[maxnode][digit_size];
int val[maxnode];
int sz;

struct Trie{
	Trie(){
		sz = 1; 
		memset(ch[0], 0, sizeof(ch[0]));
		memset(val, 0, sizeof(val));
	}
	
	int idx(char c){return c - '0';}

	void insert(char * s, int v){
		int u = 0, n = strlen(s);
		for(int i = 0; i < n; i++){
			int c = idx(s[i]);
			if(!ch[u][c]){
				memset(ch[sz], 0, sizeof(ch[sz]));
				val[sz] = v;
				ch[u][c] = sz++;
			}
			u = ch[u][c];
		}
	}

	int search(char * key){
		int u = 0; int len = strlen(key);
		for(int i = 0; i < len; i++){
			if(!ch[u][idx(key[i])]) {return -1;}
			u = ch[u][idx(key[i])];
		}
		return val[u];
	}
};

int F[2][21000];
char FF[42], IN[42];

int main(){
#ifdef LOCAL
	freopen("UVA.12333.in", "r", stdin);
	freopen("UVA.12333.out", "w", stdout);
#endif
	//Fibonacci 100000
	memset(F, 0, sizeof(F));
	F[0][0] = F[1][0] = 1;
	Trie trie;
	FF[0]='1'; FF[1]='\0';
	trie.insert(FF, 0);
	int s = 0, l = 1, p, q, r, count;
	for(int i = 2; i < 100000; i++){
		p = i%2; q = (i+1)%2;
		for(int j = s; j < l; j++){
			F[p][j] = F[p][j] + F[q][j];
		}
		for(int j = s; j < l; j++){
			if(F[p][j] >= 10){
				F[p][j+1] += 1;
				F[p][j] -= 10;
			}
		}
		if(F[p][l]) l++;
		if((l - s) > 50) s++;
		r = l - 1; count = 0;
		while(r >=0 && count < 40){
			FF[count++] = F[p][r--] + '0';
		}
		FF[count] = '\0';
		trie.insert(FF, i);
	}
	FF[0]='1'; FF[1]='\0';
	int T;
	scanf("%d", &T);
	for(int i = 1; i <= T; i++){
		scanf("%s", IN);
		printf("Case #%d: %d\n", i, trie.search(IN));
	}
	return 0;
}

