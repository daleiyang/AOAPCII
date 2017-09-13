#include<cstdio>
#include<stack>
#include<cctype>
using namespace std;

const int maxn = 1000;
char input[maxn];

struct Matrix{
	int col, row;
	Matrix(int col = 0, int row = 0):col(col), row(row){}
} m[26];

bool parse(char * input, int & ans){
	int idx = 0; char c;
	stack<Matrix> s;
	Matrix a, b;
	while((c = input[idx++]) != '\0'){
		if(c == ')'){
			b = s.top(); s.pop();
			a = s.top(); s.pop();
			if(a.row != b.col) return false;
			ans += a.row*a.col*b.row;
			s.push(Matrix(a.col, b.row));
		}
		else if(isalpha(c)){
			s.push(m[c-'A']);
		}
	}
	return true;
}

int main(){
#ifdef LOCAL
	freopen("UVA.442.in", "r", stdin);
	freopen("UVA.442.out", "w", stdout);
#endif
	int n, a, b; char t[2];
	scanf("%d", &n);
	while(n--){
		scanf("%s%d%d", t, &a, &b);
		m[t[0]-'A'].col = a;
		m[t[0]-'A'].row = b;
	}
	while(scanf("%s", input) != EOF){
		int ans = 0;
		if(parse(input, ans)){printf("%d\n", ans);}
		else {printf("error\n");}
	}
	return 0;
}

