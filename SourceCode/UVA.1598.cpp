#include<cstdio>
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
	cout << "QUOTE ";
	if(bpq.empty()) {cout << "0 0 - ";}
	else{cout << buysize[bpq.top()] << " " << bpq.top() << " - ";}
	if(spq.empty()) {cout << "0 99999" << endl;}
	else{cout << sellsize[spq.top()] << " " << spq.top() << endl;}
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
			if(t == 2) {cout << "TRADE " << orders[buy[p][i]].s << " " << price << endl;} //new order is for sell. find corresponding buy order for it.
			q -= orders[buy[p][i]].s; 
			buysize[p] -= orders[buy[p][i]].s; 
			orders[buy[p][i]].s = 0; 
			buyidx[p] = i; 
			i++; 
			continue;
		}
		
		if(orders[buy[p][i]].s >= q){
			if(t == 2) {cout << "TRADE " << q << " " << price << endl;} //new order is for sell. find corresponding buy order for it.
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
			if(t == 1) {cout << "TRADE " << orders[sell[p][i]].s << " " << price << endl; } //new order is for buy. find corresponding sell order for it.
			q -= orders[sell[p][i]].s; 
			sellsize[p] -= orders[sell[p][i]].s; 
			orders[sell[p][i]].s = 0; 
			sellidx[p] = i; 
			i++; 
			continue;
		}
		
		if(orders[sell[p][i]].s >= q){
			if(t == 1) {cout << "TRADE " << q << " " << price << endl; }  //new order is for buy. find corresponding sell order for it.
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
	int T, size, price, id, t, idx, kase = 0;; string s, s1;
	while(cin >> T){
		clean();
		getline(cin, s);
		if(kase++) {cout << endl;}
		while(T--){
			cin >> s; 
			if(s == "CANCEL"){
				cin >> id; getline(cin, s1);
				orders.push_back(order(3, 0, 0));
				
				if(orders[id-1].t == 1){buysize[orders[id-1].p] -= orders[id-1].s;}
				else if(orders[id-1].t == 2){sellsize[orders[id-1].p] -= orders[id-1].s;}
				orders[id-1].s = 0;
				
				cleanTop();
				quote();
				continue;
			}
			if(s == "BUY" || s == "SELL"){
				cin >> size >> price; getline(cin, s1);
				t = s=="BUY" ? 1 : 2;
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

