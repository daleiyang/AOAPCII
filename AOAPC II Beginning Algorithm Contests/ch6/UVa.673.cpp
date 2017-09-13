#include<cstdio>
#include<cstring>
#include<stack>
using namespace std;

const int maxn = 128 + 5;
char line[maxn];

int main(){
#ifdef LOCAL
	freopen("UVa.673.in", "r", stdin);
	freopen("UVa.673.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	fgets(line, maxn, stdin);
	while(T--){
		stack<char> s;
		bool f = true;
		fgets(line, maxn, stdin);
		int i = 0;
		while(line[i] != '\n' && line[i] != '\r'){
			if(line[i] == ')'){
				if(!s.empty() && s.top() == '(') s.pop();
				else {f = false;  break;}
			}
			else if(line[i] == ']'){
				if(!s.empty() && s.top() == '[') s.pop();
				else {f = false;  break;}
			}
			else s.push(line[i]);
			i++;
		}
		if(s.empty() && f) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}

