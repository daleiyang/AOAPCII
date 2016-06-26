#include<cstdio>
#include<stack>
using namespace std;

const int maxn = 1001;

int target[maxn];

int main(){
#ifdef LOCAL
		freopen("UVA.514.in", "r", stdin);
		freopen("UVA.514.out", "w", stdout);
#endif
	int n;
	while(scanf("%d", &n) == 1 && n){
		while(scanf("%d", &target[1]) == 1 && target[1]){
			stack<int> s;
			for(int i = 2; i <= n; i++) {scanf("%d", &target[i]);}
			int A = 1, B = 1;
			bool ok = true;
			while(B <= n){
				if(A == target[B]){
					A++; B++;
				}
				else if(!s.empty() && (s.top() == target[B])){
					s.pop(); B++;
				}
				else if(A <= n){
					s.push(A++);
				}
				else {
					ok = false; break;
				}
			}
			printf("%s\n", ok?"Yes":"No");
		}
		printf("\n");
	}
	return 0;
}

