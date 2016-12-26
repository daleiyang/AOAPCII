#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;

const int maxn = 40000+5;
int n, m, pos;

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

SuffixArray sa;

void add(int ch){
	sa.s[sa.n++] = ch;
}

int possible(int len){
	if(m == 1){pos = 0; return true;}
	int c = 1, tpos = -1;
	pos = -1;
	for(int i = 1; i < sa.n; i++){
		if(sa.height[i] < len) {c = 1; tpos = -1;}
		else {c++; tpos = max(tpos, max(sa.sa[i], sa.sa[i-1]));}
		if(c >= m) pos = max(pos, tpos);
	}
	return pos >= 0;
}

int main(){
#ifdef LOCAL
			freopen("UVA.12206.in", "r", stdin);
			freopen("UVA.12206.out", "w", stdout);
#endif
	char s[maxn];
	while(scanf("%d", &m) == 1 && m){
		scanf("%s", s);
		n = strlen(s);

		sa.clear();
		for(int j = 0; j < n; j++) add(s[j]-'a'+1);
		add(0);

		sa.build_sa(26+1);
		sa.build_height();

		if(!possible(1)) printf("none\n");
		else{
			int L = 1, R = n, M;
			while(L < R){
				M = L + (R-L+1)/2;
				if(possible(M)) L = M;
				else R = M-1;
			}
			possible(L);
			printf("%d %d\n", L, pos);
		}
	}
	return 0;
}

