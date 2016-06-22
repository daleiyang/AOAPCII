#include<cstdio>
#include<cstring>
#include<iostream>
#include<sstream>
#include<queue>
#include<utility>
#include<algorithm>
#include<map>
#include<ctime>
using namespace std;

struct order{
	int t; // 1 for buy; 2 for sell; 3 for cancel
	int s, p;
	order(int t = 0, int s = 0, int p = 0):t(t), s(s), p(p){}
};
vector<order> orders;
map<int, vector<int> > buy, sell;
map<int, int> buyidx, sellidx, buysize, sellsize;
typedef priority_queue<int> PQB;
typedef priority_queue<int, vector<int>, greater<int> > PQS;
PQB bpq; PQS spq;

void clean(){
	orders.clear(); buy.clear(); sell.clear(); 
	buyidx.clear(); sellidx.clear(); 
	buysize.clear(); sellsize.clear();
	PQB emptyB; swap(bpq, emptyB); 
	PQS emptyS; swap(spq, emptyS);
}

void quote(){
	printf("QUOTE ");
	if(bpq.empty()) {printf("0 0 - ");}
	else{printf("%d %d - ", buysize[bpq.top()], bpq.top());}
	if(spq.empty()) {printf("0 99999\n");}
	else{ printf("%d %d\n", sellsize[spq.top()], spq.top());}
}

void cleanTop(){
	while(!bpq.empty() && buysize[bpq.top()] == 0) {bpq.pop();}
	while(!spq.empty() && sellsize[spq.top()] == 0) {spq.pop();}
}

void buyOrder(int p, int q, int price, int t){
	unsigned int i = buyidx[p];
	while(q > 0 && i < buy[p].size()){
		if(orders[buy[p][i]].s == 0) {
			buyidx[p] = i; 
			i++; 
			continue;
		}
		
		if(orders[buy[p][i]].s < q) {
			if(t == 2) {printf("TRADE %d %d\n", orders[buy[p][i]].s, price);} //new order is for sell. find corresponding buy order for it.
			q -= orders[buy[p][i]].s; 
			buysize[p] -= orders[buy[p][i]].s; 
			orders[buy[p][i]].s = 0; 
			buyidx[p] = i; 
			i++; 
			continue;
		}
		
		if(orders[buy[p][i]].s >= q){
			if(t == 2) {printf("TRADE %d %d\n", q, price);} //new order is for sell. find corresponding buy order for it.
			buysize[p] -= q; 
			orders[buy[p][i]].s -= q;
			q = 0; 
			buyidx[p] = i;
			break;
		}
	}
}

void sellOrder(int p, int q, int price, int t){
	unsigned int i = sellidx[p];
	while(q > 0 && i < sell[p].size()){
		if(orders[sell[p][i]].s == 0) {
			sellidx[p] = i; 
			i++; 
			continue;
		}
		
		if(orders[sell[p][i]].s < q) {
			if(t == 1) {printf("TRADE %d %d\n", orders[sell[p][i]].s, price);} //new order is for buy. find corresponding sell order for it.
			q -= orders[sell[p][i]].s; 
			sellsize[p] -= orders[sell[p][i]].s; 
			orders[sell[p][i]].s = 0; 
			sellidx[p] = i; 
			i++; 
			continue;
		}
		
		if(orders[sell[p][i]].s >= q){
			if(t == 1) {printf("TRADE %d %d\n", q, price);}  //new order is for buy. find corresponding sell order for it.
			sellsize[p] -= q; 
			orders[sell[p][i]].s -= q; 
			q = 0; 
			sellidx[p] = i; 
			break;
		}
	}
}

int main(){
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("UVA.1598.in", "r", stdin);
	freopen("UVA.1598.out", "w", stdout);
#endif
	int T, size, price, id, t, idx, kase = 0;; string s, s1; char input[10];
	while(scanf("%d", &T) == 1){
		clean();
		if(kase++) {printf("\n");}
		while(T--){
			scanf("%s", input);
			if(strcmp(input, "CANCEL") == 0){
				scanf("%d", &id);
				orders.push_back(order(3, 0, 0));
				
				if(orders[id-1].t == 1){buysize[orders[id-1].p] -= orders[id-1].s;}
				else if(orders[id-1].t == 2){sellsize[orders[id-1].p] -= orders[id-1].s;}
				orders[id-1].s = 0;
				
				cleanTop();
				quote();
				continue;
			}
			if((strcmp(input, "BUY") == 0) || (strcmp(input, "SELL") == 0)){
				scanf("%d%d", &size, &price);
				t = strcmp(input, "BUY") == 0 ? 1 : 2;
				orders.push_back(order(t, size, price));
				idx = orders.size()-1;
				if(t == 1){
					if(!buy.count(price)){
						vector<int> v;
						v.push_back(idx);
						buy[price] = v;
						buyidx[price] = 0;
						bpq.push(price);
						buysize[price] = size;
					}else{
						buy[price].push_back(idx);
						if(buysize[price] == 0) {bpq.push(price);}
						buysize[price] += size;
					}
				}
				else{
					if(!sell.count(price)){
						vector<int> v;
						v.push_back(idx);
						sell[price] = v;
						sellidx[price] = 0;
						spq.push(price);
						sellsize[price] = size;
					}else{
						sell[price].push_back(idx);
						if(sellsize[price] == 0) {spq.push(price);}
						sellsize[price] += size;
					}
				}
			}
			
			while(!bpq.empty() && !spq.empty() && bpq.top() >= spq.top()){
				int q = min(buysize[bpq.top()], sellsize[spq.top()]);
				int price;
				if(t == 1) {price = spq.top();} //take ask price
				else {price =  bpq.top();} //take bid price				
				buyOrder(bpq.top(), q, price, t);
				sellOrder(spq.top(), q, price, t);
				cleanTop();
			}
			quote();
		}
	}
	//printf("Time used = %.2f", (double)clock()/CLOCKS_PER_SEC);
	return 0;
}

