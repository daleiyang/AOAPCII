#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 1001*100+10;

struct SuffixArray{
	int s[maxn];
	int sa[maxn];
	int rank[maxn];
	int height[maxn];
	int t[maxn], t2[maxn], c[maxn];
	int n;

	void clear(){n = 0; memset(sa, 0, sizeof(sa));}

	void build_sa(int m){
		int i, *x = t, *y = t2;
		for(i = 0; i < m; i++) c[i] = 0;
		for(i = 0; i < n; i++) c[x[i] = s[i]]++;
		for(i = 1; i < m; i++) c[i] += c[i-1];
		for(i = n-1; i >= 0; i--) sa[--c[x[i]]] = i;
		for(int k = 1; k <= n; k <<= 1){
			int p = 0;
			for(i = n-k; i < n; i++) y[p++] = i;
			for(i = 0; i < n; i++) if(sa[i] >= k) y[p++] = sa[i]-k;
			for(i = 0; i < m; i++) c[i] = 0;
			for(i = 0; i < n; i++) c[x[y[i]]]++;
			for(i = 0; i < m; i++) c[i] += c[i-1];
			for(i = n-1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
			swap(x, y);
			p = 1; x[sa[0]] = 0;
			for(i = 1; i < n; i++)
				x[sa[i]] = y[sa[i-1]] == y[sa[i]] && y[sa[i-1]+k] == y[sa[i]+k] ? p-1 : p++;
			if(p >= n) break;
			m = p;
		}
	}

	void build_height(){
		int i, k = 0;
		for(i = 0; i < n; i++) rank[sa[i]] = i;
		for(i = 0; i < n; i++){
			if(k) k--;
			int j = sa[rank[i]-1];
			while(s[i+k] == s[j+k]) k++;
			height[rank[i]] = k;
		}
	}
};

const int maxc = 100+10;
const int maxl = 1000+10;

SuffixArray sa;
int n;
char word[maxl];
int idx[maxn];
int flag[maxc];

bool good(int L, int R){
	memset(flag, 0, sizeof(flag));
	if(R-L <= n/2) return false;
	int cnt = 0;
	for(int i = L; i < R; i++){
		int x = idx[sa.sa[i]];
		if(x != n && !flag[x]){
			flag[x] = 1; cnt++;
		}
	}
	return cnt > n/2;
}

void print_sub(int L, int R){
	for(int i = L; i < R; i++)
		printf("%c", sa.s[i]-1+'a');
	printf("\n");
}

bool print_solution(int len, int print){
	int L = 0;
	for(int R = 1; R <= sa.n; R++){
		if(R == sa.n || sa.height[R] < len){
			if(good(L, R)){
				if(print) print_sub(sa.sa[L], sa.sa[L]+len);
				else return true;
			}
			L = R;
		}
	}
	return false;
}

void solve(int maxlen){
	if(!print_solution(1, false))
		printf("?\n");
	else{
		int L = 1, R= maxlen, M;
		while(L < R){
			M = L + (R-L+1)/2;
			if(print_solution(M, false)) L = M;
			else R = M-1;
		}
		print_solution(L, true);
	}
}

void add(int ch, int i){
	idx[sa.n] = i;
	sa.s[sa.n++] = ch;
}

int main(){
#ifdef LOCAL
		freopen("UVa.11107.in", "r", stdin);
		freopen("UVa.11107.out", "w", stdout);
#endif
	int kase = 0;
	while(scanf("%d", &n) == 1 && n){
		if(kase++ > 0) printf("\n");
		int maxlen = 0;
		sa.clear();
		for(int i = 0; i < n; i++){
			scanf("%s", word);
			int sz = strlen(word);
			maxlen = max(maxlen, sz);
			for(int j = 0; j < sz; j++)
				add(word[j]-'a'+1, i);
			add(100+i, n);
		}
		add(0, n);

		if(n == 1) printf("%s\n", word);
		else{
			sa.build_sa(100+n);
			sa.build_height();
			solve(maxlen);
		}
	}
	return 0;
}

