#include<cstdio>
using namespace std;

int s[20], o[20], ss[20], os[20], sc[20], oc[20];
int n, on, ocn;
bool f;

void print(){
	f = true;
	printf("  ");
	for(int i = 0; i < n-1; i++){
		printf("%d", s[i]);
		if(o[i] == 0) printf("*");
		if(o[i] == 1) printf("+");
		if(o[i] == 2) printf("-");
	}
	printf("%d=\n", s[n-1]);
}

bool valid(){
	on = 0;
	ss[on] = s[0];
 	for(int i = 0; i < n-1; i++){ //for each inserted char
 		if(o[i] != 3){
			os[on] = o[i];
			on++;
			ss[on] = s[i+1];
 		}
		else{
			if(ss[on] == 0) return false;
			ss[on] *= 10;
			ss[on] += s[i+1];
		}
	}
	if(on == 0) return false;
	return true;
}

void calcu(){
	if(!valid()) return;
	ocn = 0;
	sc[ocn] = ss[0]; 
	for(int i = 0; i < on; i++){
		if(os[i] == 0){
			sc[ocn] *= ss[i+1];
		}
		else{
			oc[ocn] = os[i];
			ocn++;
			sc[ocn] = ss[i+1];
		}
	}
	int h = sc[0];
	for(int i = 0; i < ocn; i++){
		if(oc[i] == 1) h += sc[i+1];
		if(oc[i] == 2) h -= sc[i+1];
	}
	if(h == 2000) print();
}

void dfs(int d){
	if(d == n-1){
		calcu();
		return;
	}
	for(int i = 0; i < 4; i++){
		o[d] = i;
		dfs(d+1);
	}
}

int main(){
#ifdef LOCAL
	freopen("UVa.817.in", "r", stdin);
	freopen("UVa.817.out", "w", stdout);
#endif
	int kase = 0;
	char buf[20];
	while(scanf("%s", buf) == 1 && buf[0] != '='){
		f = false;
		printf("Problem %d\n", ++kase);
		for(n = 0; buf[n] != '='; n++){
			s[n] = buf[n] - '0';
		}
		dfs(0);
		if(!f) printf("  IMPOSSIBLE\n");
	}
	return 0;
}

