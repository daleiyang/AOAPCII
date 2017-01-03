#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;

const int maxn = 768;
int a[maxn], b[maxn];

struct Item{
    int s, b;
    Item(int s, int b): s(s), b(b){}
    bool operator < (const Item & rhs) const{
        return s > rhs.s;
    }
};

void merge(int* x, int* y, int n){
    priority_queue<Item> pq;
    for(int i = 0; i < n; i++) pq.push(Item(x[i]+y[0], 0));
    for(int i = 0; i < n; i++){
        Item item = pq.top(); pq.pop();
        x[i] = item.s;
        int b = item.b;
        pq.push(Item(item.s-y[b]+y[b+1], b+1));
    }
}

int main(){
#ifdef LOCAL
	freopen("UVA.11997.in", "r", stdin);
	freopen("UVA.11997.out", "w", stdout);
#endif
    int n;
    while(scanf("%d", &n) == 1){
        for(int i = 0; i < n; i++) scanf("%d", &a[i]);
        sort(a, a+n);
        for(int i = 1; i < n; i++) {
            for(int j = 0; j < n; j++) scanf("%d", &b[j]);
            sort(b, b+n);
            merge(a, b, n);
        }
        for(int i = 0; i < n; i++){
            if(!i) printf("%d", a[0]);
            else printf(" %d", a[i]);
        }
        printf("\n");
    }
    return 0;
}
