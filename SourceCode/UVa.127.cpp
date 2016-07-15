#include<cstdio>
#include<cstring>
using namespace std;

const int maxn = 52;

char s[5];
int LEFT[maxn+1], RIGHT[maxn+1];

struct card{
	char value, suit;
};

struct pile{
	card cards[maxn+1];
	int n;
} piles[maxn+1];

void init(){
	for(int i = 1; i <= maxn; i++){
		RIGHT[i] = (i+1)%(maxn+1);
		LEFT[i] = i-1;
	}
	LEFT[0] = maxn; RIGHT[0] = 1;
}

void link(int left, int right){
	RIGHT[left] = right;
	LEFT[right] = left;
}

bool move(int x, int y){
	if(piles[x].cards[piles[x].n].value == piles[y].cards[piles[y].n].value 
		|| piles[x].cards[piles[x].n].suit == piles[y].cards[piles[y].n].suit){

		piles[x].n++;
		piles[x].cards[piles[x].n].value = piles[y].cards[piles[y].n].value;
		piles[x].cards[piles[x].n].suit  = piles[y].cards[piles[y].n].suit;
		piles[y].n--;

		if(!piles[y].n){
			link(LEFT[y], RIGHT[y]);
		}
		
		return true;
	}
	return false;
}

void solve(){
	int i = RIGHT[0], t;
	while(RIGHT[i] != 0){
		//try to move i+1 to i;
		if(move(i, RIGHT[i])){
			i = RIGHT[0]; continue;
		}

		//try to move i+2 to i+1;
		if(RIGHT[RIGHT[i]] !=0){
			if(move(RIGHT[i], RIGHT[RIGHT[i]])){
				i = RIGHT[0]; continue;
			}
		}

		//try to move i+3 to i+1;
		bool f = true; t = i;
		for(int j = 1; j <= 3; j++){
			t = RIGHT[t];
			if(!t){
				f = false; break;
			}
		}
		if(f && move(i, t)){
			i = RIGHT[0]; continue;
		}
		
		//try to move i+3 to i+2;
		if(f && move(RIGHT[RIGHT[i]], RIGHT[RIGHT[RIGHT[i]]])){
			i = RIGHT[0]; continue;
		}
		
		i = RIGHT[i];
	}
}

int main(){
#ifdef LOCAL
		freopen("UVa.127.in", "r", stdin);
		freopen("UVa.127.out", "w", stdout);
#endif
	while(scanf("%s", s) == 1 && s[0] != '#'){
		memset(piles, 0, sizeof(piles));
		init();
		piles[1].cards[1].value = s[0]; 
		piles[1].cards[1].suit = s[1]; 
		piles[1].n = 1;
		for(int i = 2; i < maxn + 1; i++){
			scanf("%s", s);
			piles[i].cards[1].value = s[0];
			piles[i].cards[1].suit = s[1];
			piles[i].n = 1;
		}
		solve();
		int cnt = 0, idx = 0;
		while(RIGHT[idx]) {
			cnt++;
			idx = RIGHT[idx];
		}
		if(cnt == 1) printf("%d pile remaining:", cnt);
		else printf("%d piles remaining:", cnt);
		idx = 0;
		do{
			int t = piles[RIGHT[idx]].n;
			printf(" %d", t);
			idx = RIGHT[idx];
		}while(RIGHT[idx]);
		printf("\n");
	}
	return 0;
}

