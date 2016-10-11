#include<cstdio>
#include<vector>
using namespace std;

const int maxn =  1024 + 5;
char table[maxn][maxn];

int main(){
#ifdef LOCAL
		freopen("UVa.1609.in", "r", stdin);
		freopen("UVa.1609.out", "w", stdout);
#endif
	int n;
	while(scanf("%d", &n) == 1){
		for(int i = 1; i <= n; i++) scanf("%s", table[i]+1);

		vector<int> win, lose; //team 1 can win and lose
		for(int i = 2; i <= n; i++){
			if(table[1][i] == '1') win.push_back(i);
			else lose.push_back(i);
		}

		while(n>1){
			vector<int> win2, lose2, final;
			
			//phase 1
			for(unsigned int i = 0; i < lose.size(); i++){
				int tlose = lose[i];
				int match = false;
				for(unsigned int j = 0; j < win.size(); j++){
					int & twin = win[j];
					if(twin > 0 && table[twin][tlose] == '1'){
						printf("%d %d \n", twin, tlose);
						win2.push_back(twin);
						twin = 0;
						match = true;
						break;
					}	
				}
				if(!match) final.push_back(tlose);
			}

			//phase 2
			bool first = true;
			for(unsigned int i = 0; i < win.size(); i++){
				if(win[i] > 0){
					if(first) {
						printf("1 %d\n", win[i]);
						first = false;
					}
					else final.push_back(win[i]);
				}
			}

			//phase 3 and 4
			for(unsigned int i = 0; i < final.size(); i+=2){
				printf("%d %d\n", final[i], final[i+1]);
				int keep = final[i];
				if(table[final[i+1]][final[i]] == '1') keep = final[i+1];
				if(table[1][keep] == '1') win2.push_back(keep);
				else lose2.push_back(keep);
			}	

			win = win2;
			lose = lose2;
			n >>= 1;
		}
	}
	return 0;
}

