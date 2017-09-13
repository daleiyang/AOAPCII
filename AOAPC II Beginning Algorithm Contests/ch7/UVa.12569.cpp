//http://www.cnblogs.com/Emerald/p/4734017.html
#include<cstdio>
#include<cstring>
#include<vector>
#include<utility>
using namespace std;

const int maxn  = (1<<15)+50;
int vis[maxn][15+2];
struct Node{
	int robot, ob, step;
};
typedef pair<int, int> Move;
Node q[maxn*17];
Move mv[maxn*17];
int movePath[maxn*17];
vector<int> link[17];
int n, m, s, target;
int start;

void Read(){
	scanf("%d%d%d%d", &n, &m, &s, &target);
	s--; target--; start = 0;
	int tmp;
	for(int i = 0; i < m; i++){
		scanf("%d", &tmp);
		start |= (1<<(tmp-1));
	}
	for(int i = 0; i < n; i++){
		link[i].clear();
	}
	int x, y;
	for(int i = 0; i < n-1; i++){
		scanf("%d%d", &x, &y);
		link[x-1].push_back(y-1);
		link[y-1].push_back(x-1);
	}
}

void print(int rear){
	vector<Move> v;
	while(rear){
		v.push_back(mv[rear]);
		rear = movePath[rear];
	}
	vector<Move>::iterator it;
	for(it = v.end()-1; it >= v.begin(); it--){
		printf("%d %d\n", it->first+1, it->second+1);
	}
}

void bfs(){
	int front = 0, rear = 1;
	q[front].ob = start;
	q[front].robot = s;
	q[front].step = 0;
	memset(vis, 0, sizeof(vis));
	vis[q[front].ob][q[front].robot] = 1;
	while(front < rear){
		Node & t = q[front];
		if(t.robot == target){
			printf("%d\n", t.step);
			print(front);
			return;
		}
		for(int i = 0; i < n; i++){
			if((t.ob & (1<<i)) || t.robot == i){
				for(size_t j = 0; j < link[i].size(); j++){
					int nextNode = link[i][j];
					if((t.ob&(1<<nextNode)) || t.robot == nextNode) continue;
					Node next = t;
					if(i == t.robot){
						next.robot = nextNode;
					}else{
						next.ob = (next.ob ^ (1<<i)) | (1<<nextNode);
					}
					next.step = t.step+1;
					if(!vis[next.ob][next.robot]){
						vis[next.ob][next.robot] = 1;
						mv[rear].first = i;
						mv[rear].second = nextNode;
						movePath[rear] = front;
						q[rear++] = next;
					}
				}
			}
		}
		front++;
	}
	printf("-1\n");
}

int main(){
#ifdef LOCAL
	freopen("UVa.12569.in", "r", stdin);
	freopen("UVa.12569.out", "w", stdout);
#endif
	int T, kase = 0;
	scanf("%d", &T);
	while(T--){
		Read();
		printf("Case %d: ", ++kase);
		bfs();
	}
	return 0;
}

