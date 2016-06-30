#include<cstdio>
#include<cstring>
using namespace std;

const int len = 32;
const int maxn = 1024 + 128;

char s[maxn];
int m[len][len], cnt;

void build(const char * s, int & p, int r, int c, int w){
	char t = s[p++];
	if(t == 'p'){
		build(s, p, r,     c,     w/2);
		build(s, p, r+w/2, c,     w/2);
		build(s, p, r+w/2, c+w/2, w/2);
		build(s, p, r,     c+w/2, w/2);
		/*
		build(s, p, r,     c+w/2, w/2);
		build(s, p, r,     c,     w/2);
		build(s, p, r+w/2, c,     w/2);
		build(s, p, r+w/2, c+w/2, w/2);
		*/
	}
	else if(t == 'f'){
		for(int i = r; i < r+w; i++)
			for(int j = c; j < c+w; j++)
				if(m[i][j] == 0){
					m[i][j] = 1; cnt++;
				}
	}
}

int main(){
#ifdef LOCAL
	freopen("UVa.297.in", "r", stdin);
	freopen("UVa.297.out", "w",stdout);
#endif
	int T;
	scanf("%d", &T);
	while(T--){
		memset(m, 0, sizeof(m)); cnt = 0;
		for(int i = 0; i < 2; i++){
			scanf("%s", s);
			int p = 0;
			build(s, p, 0, 0, len);
		}
		printf("There are %d black pixels.\n", cnt);
	}
	return 0;
}

