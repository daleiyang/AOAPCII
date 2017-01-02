#include<cstdio>
#include<stack>
#include<queue>
using namespace std;

const int maxn = 1000 + 10;
int n, t[maxn], v[maxn];

bool checkstack(){
    stack<int> s;
    for(int i = 0; i < n; i++){
        if(t[i] == 2){
            if(s.empty()) return false;
            int x = s.top(); s.pop();
            if(x != v[i]) return false;
        }
        else s.push(v[i]);
    }
    return true;
}

bool checkqueue(){
    queue<int> q;
    for(int i = 0; i < n; i++){
        if(t[i] == 2){
            if(q.empty()) return false;
            int x = q.front(); q.pop();
            if(x != v[i]) return false;
        }
        else q.push(v[i]);
    }
    return true;
}

bool checkpq(){
    priority_queue<int> pq;
    for(int i = 0; i < n; i++){
        if(t[i] == 2){
            if(pq.empty()) return false;
            int x = pq.top(); pq.pop();
            if(x != v[i]) return false;
        }
        else pq.push(v[i]);
    }
    return true;
}

int main(){
#ifdef LOCAL
	freopen("UVA.11995.in", "r", stdin);
	freopen("UVA.11995.out", "w", stdout);
#endif
    while(scanf("%d", &n) == 1){
        for(int i = 0; i < n; i++) scanf("%d%d", &t[i], &v[i]);
        bool s = checkstack();
        bool q = checkqueue();
        bool p = checkpq();
        if(!s && !q && !p) printf("impossible\n");
        else if(s && !q && !p) printf("stack\n");
        else if(!s && q && !p) printf("queue\n");
        else if(!s && !q && p) printf("priority queue\n");
        else printf("not sure\n");
    }
    return 0;
}
