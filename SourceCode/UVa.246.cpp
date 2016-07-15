#include<cstdio>
#include<cstring>
#include<deque>
#include<queue>
#include<set>
using namespace std;

struct state{
	int v[70];
	state(){memset(v, 0, sizeof(v));}
	bool operator < (const state & x) const{
		return memcmp(v, x.v, sizeof(v)) < 0;
	}
};

queue<int> hand;
deque<int> piles[7];
set<state> s;

void check(deque<int> & pile){
	while(pile.size()>=3){
		int n = pile.size();
		if((pile[0]+pile[1]+pile[n-1])%10 == 0){
			hand.push(pile[0]);
			hand.push(pile[1]);
			hand.push(pile[n-1]);
			pile.pop_front();
			pile.pop_front();
			pile.pop_back();
		}
		else if((pile[0]+pile[n-2]+pile[n-1])%10 == 0){
			hand.push(pile[0]);
			hand.push(pile[n-2]);
			hand.push(pile[n-1]);
			pile.pop_front();
			pile.pop_back();
			pile.pop_back();
		}else if((pile[n-3]+pile[n-2]+pile[n-1])%10 == 0){
			hand.push(pile[n-3]);
			hand.push(pile[n-2]);
			hand.push(pile[n-1]);
			pile.pop_back();
			pile.pop_back();
			pile.pop_back();
		}
		else{ return;}
	}
}

int main(){
#ifdef LOCAL
	freopen("UVa.246.in", "r", stdin);
	freopen("UVa.246.out", "w",stdout);
#endif
	int n;
	while(scanf("%d", &n) == 1 && n){
		//clear
		while(!hand.empty()) hand.pop();
		for(int i = 0; i < 7; i++) piles[i].clear();
		s.clear();
		//input
		hand.push(n);
		for(int i = 1; i <= 51; i++){
			scanf("%d", &n); hand.push(n);
		}
		//init
		for(int i = 0; i < 7; i++){
			piles[i].push_back(hand.front()); hand.pop();
		}
		for(int i = 0; i < 7; i++){
			piles[i].push_back(hand.front()); hand.pop();
		}
		//start
		int step = 14;
		bool f = true;
		while(f){
			for(int i = 0; i < 7; i++){
				if(piles[i].size() == 0) continue;
				step++;
				piles[i].push_back(hand.front()); hand.pop();
				check(piles[i]);

				if(hand.size() == 0){
					printf("Loss: %d\n", step);
					f= false;
					break;
				}
				if(hand.size() == 52){
					printf("Win : %d\n", step);
					f= false;
					break;
				}

				state st; 
				int idx = 0;
				for(int j = 0; j < 7; j++){
					for(unsigned int k = 0; k < piles[j].size(); k++){
						st.v[idx++] = piles[j][k];
					}
					st.v[idx++] = 15;
				}
				
				queue<int> h = hand;
				while(!h.empty()){
					st.v[idx++] = h.front();
					h.pop();
				}
				st.v[idx++] = 15;

				if(s.count(st)){
					printf("Draw: %d\n", step);
					f= false;
					break;
				}

				s.insert(st);
			}
		}
	}
	return 0;
}

