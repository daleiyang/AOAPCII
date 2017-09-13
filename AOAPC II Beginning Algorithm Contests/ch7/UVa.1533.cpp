#include<cstdio>
#include<cstring>
#include<vector>
#include<utility>
#include<ctime>
using namespace std;

const int maxn = (1<<15)+50;
int vis[maxn];
struct Node{
	int state, step;
};
typedef pair<int, int> Move;
Node q[maxn*17];
Move mv[maxn*17];
int movePath[maxn*17];
int s, start, target;

int list[36][6] = {
		{0, 1, 3, 6, 10, -1}, {0, 2, 5, 9, 14, -1},
		{1, 3, 6, 10, -1}, {1, 4, 8, 13, -1},
		{2, 4, 7, 11, -1}, {2, 5, 9, 14, -1},
		{3, 1, 0, -1}, {3, 4, 5, -1}, {3, 6, 10, -1}, {3, 7, 12, -1},
		{4, 7, 11, -1}, {4, 8, 13, -1},
		{5, 2, 0, -1}, {5, 4, 3, -1}, {5, 8, 12, -1}, {5, 9, 14, -1},
		{6, 3, 1, 0, -1}, {6, 7, 8, 9, -1},
		{7, 4, 2, -1}, {7, 8, 9, -1},
		{8, 4, 1, -1}, {8, 7, 6, -1},
		{9, 5, 2, 0, -1}, {9, 8, 7, 6, -1},
		{10, 6, 3, 1, 0, -1}, {10, 11, 12, 13, 14, -1},
		{11, 7, 4, 2, -1}, {11, 12, 13, 14, -1},
		{12, 7, 3, -1}, {12, 8, 5, -1}, {12, 11, 10, -1}, {12, 13, 14, -1},
		{13, 8, 4, 1, -1}, {13, 12, 11, 10, -1}, 
		{14, 9, 5, 2, 0, -1}, {14, 13, 12, 11, 10, -1}
};

void print(int rear){
	vector<Move> v;
	while(rear){
		v.push_back(mv[rear]);
		rear = movePath[rear];
	}
	vector<Move>::iterator it;
	int kase = 0;
	for(it = v.end()-1; it >= v.begin(); it--){
		if(!kase) {kase = 1;} else {printf(" ");}
		printf("%d %d", it->first+1, it->second+1);
	}
	printf("\n");
}

bool bfs(){
	int front = 0, rear = 1;
	q[front].state = start;
	q[front].step = 0;
	memset(vis, 0, sizeof(vis));
	vis[q[front].state] = 1;
	while(front < rear){
		Node & t = q[front];
		if(t.state == target){
			printf("%d\n", t.step);
			print(front);
			return true;
		}
		for(int i = 0; i < 15; i++){
			if(t.state & (1<<i)){  //node i is not empty
				bool f2 = false;
				for(int j = 0; j < 36; j++){
					if(list[j][0] != i) {
						if(f2) break;
						else continue; //check the path start from i
					}
					f2 = true; int idx = 1; bool f = false;
					while(list[j][idx] != -1){
						int tmp = list[j][idx];
						if(t.state & (1<<tmp)) {
							f = true; 
							idx++; 
							continue;
						}
						if(!(t.state & (1<<tmp)) && !f) {
							break;
						} //find a not qulified empty node, we should ingore this path
						if(!(t.state & (1<<tmp)) && f) {//find a qulified empty node, mark [1, idx -1] to "0", mark idx to "1"
							Node n = t;
							for(int k = 0; k <= idx-1; k++){n.state ^= (1 << list[j][k]);}
							n.state |= (1<<list[j][idx]);
							n.step = t.step+1;
							if(!vis[n.state]){
								vis[n.state] = 1;
								mv[rear].first = i;
								mv[rear].second = list[j][idx];
								movePath[rear] = front;
								q[rear++] = n;
								break;
							}
							else break;
						}
					}
				}
			}
		}
		front++;
	}
	return false;
}

int main(){
#ifdef LOCAL
		freopen("UVa.1533.in", "r", stdin);
		freopen("UVa.1533.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d", &s);
		start = target = 0;
		for(int i = 0; i < 15; i++){
			if(i != s-1) {start |= (1<<i);}
			else{target |= (1<<i);}
		}
		if(!bfs()) {printf("IMPOSSIBLE\n");}
	}
	//printf("Time uased = %.4f", (double)clock()/CLOCKS_PER_SEC);
	return 0;
}

