#include<cstdio>
#include<queue>
using namespace std;

struct Item{
    int QNum, Period, Time;
    bool operator < (const Item& rhs) const{
        return Time > rhs.Time || (Time == rhs.Time && QNum > rhs.QNum);
    }
};

int main(){
#ifdef LOCAL
	freopen("UVA.1203.in", "r", stdin);
	freopen("UVA.1203.out", "w", stdout);
#endif
    priority_queue<Item> pq;
    char s[20];

    while(scanf("%s", s) && s[0] != '#'){
        Item item;
        scanf("%d%d", &item.QNum, &item.Period);
        item.Time = item.Period;
        pq.push(item);
    }
    int k;
    scanf("%d", &k);
    while(k--){
         Item r = pq.top(); pq.pop();
         printf("%d\n", r.QNum);
         r.Time += r.Period;
         pq.push(r);       
    }
    return 0;
}
