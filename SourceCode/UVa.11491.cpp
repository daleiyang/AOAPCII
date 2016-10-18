#include<cstdio>
#include<queue>
using namespace std;

struct node{
	int pos;
	char val;
	node(int pos = 0, char val = '0'):pos(pos),val(val){}
	bool operator < (const node & rhs) const{
		return (val < rhs.val || (val == rhs.val && pos > rhs.pos));
	}
};

priority_queue<node> q;

int main(){
#ifdef LOCAL
		freopen("UVa.11491.in", "r", stdin);
		freopen("UVa.11491.out", "w", stdout);
#endif
	int d, n;
	while(scanf("%d %d", &n, &d) == 2 && n){
		while(!q.empty()) q.pop();
		getchar();
		for(int i = 0; i <= d; i++){
			q.push(node(i, getchar()));
		}
		int left = -1;
		for(int i = 0; i < n-d; i++){
			while(!q.empty()){
				node temp = q.top(); q.pop();
				if(temp.pos > left){
					printf("%c", temp.val);
					left = temp.pos;
					break;
				}
			}
			q.push(node(d+i+1, getchar()));
		}
		printf("\n");
	}
	return 0;
}

