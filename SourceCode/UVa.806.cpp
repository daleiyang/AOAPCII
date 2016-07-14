#include<cstdio>
#include<string>
#include<cstring>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const int maxn = 64;

char input[maxn+5];
int m[maxn][maxn];
vector<int> v;

int getval(string s){
	int ans = 0;
	for(unsigned int i = 0; i < s.length(); i++)
		ans = ans * 5 + s[i]-'0';
	return ans;	
}

void img2num(int r, int c, int w, string s){
	int sum = 0;
	for(int i = r; i < r+w; i++)
		for(int j = c; j < c+w; j++)
			sum += m[i][j];
	if(sum == w*w) v.push_back(getval(s));
	else if(sum){
		img2num(r		, c		, w/2, "1"+s);
		img2num(r		, c+w/2	, w/2, "2"+s);
		img2num(r+w/2	, c		, w/2, "3"+s);
		img2num(r+w/2	, c+w/2	, w/2, "4"+s);
		//img2num(r		, c+w/2	, w/2, "1"+s);
		//img2num(r		, c		, w/2, "2"+s);
		//img2num(r+w/2	, c+w/2	, w/2, "3"+s);
		//img2num(r+w/2	, c		, w/2, "4"+s);
	}
}

int main(){
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("UVa.806.in", "r", stdin);
	freopen("UVa.806.out", "w", stdout);
#endif
	int n, kase = 0, t;
	while(scanf("%d", &n) == 1 && n){
		memset(m, 0, sizeof(m));
		if(kase) printf("\n");
		printf("Image %d\n", ++kase);
		if(n > 0){
			v.clear();
			for(int i = 0; i < n; i++){
				scanf("%s", input);
				for(int j = 0; j < n; j++){
					m[i][j] = input[j]-'0';
				}
			}
			img2num(0, 0, n, "");
			sort(v.begin(), v.end());
			if(v.size()){
				printf("%d", v[0]); unsigned int i = 1;
				while(i < v.size()){
					printf(" %d", v[i]);
					i++;
					if(i%12 == 0 && i < v.size()) {printf("\n%d", v[i]);i++;}
				}
				printf("\n");
			}
			printf("Total number of black nodes = %d\n", (int)v.size());
		}
		if(n < 0){
			while(scanf("%d", &t) == 1 && t != -1){
				int r = 0, c =0, w = -n;
				while(t%5){
					w /= 2;
					switch(t%5){
						case 1: break;
						case 2: {c += w; break;}
						case 3: {r += w; break;}
						case 4: {r += w; c += w; break;}
						//case 1: {c += w; break;}
						//case 2: break;
						//case 3: {r += w; c += w; break;}
						//case 4: {r += w; break;}
					}
					t /= 5;
				}
				for(int i = r; i < r+w; i++)
					for(int j = c; j < c+w; j++)
						m[i][j] = 1;
			}
			for(int i = 0; i < -n; i++){
				for(int j = 0; j < -n; j++){
					if(m[i][j]==0) printf(".");
					else printf("*");
				}
				printf("\n");
			}
		}
	}
	return 0;
}

