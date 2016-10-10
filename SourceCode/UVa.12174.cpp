#include<cstdio>
#include<algorithm>
using namespace std;

const int maxn = 100000 + 5;
int s, n;
int x[maxn*3]; //all space we need. we need s-1 empty space in front of first element and after the last element to construct all sliding windows.
int ok[maxn*2]; //represent whether sliding windows is valid or not.
int cnt[maxn]; // used to calculate 
int tot; //calculate how many distinct number exists in a sliding windows.


int main(){
#ifdef LOCAL
		freopen("UVa.12174.in", "r", stdin);
		freopen("UVa.12174.out", "w", stdout);
#endif
	int T;
	scanf("%d", &T);
	while(T--){
		scanf("%d%d", &s, &n);
		fill(x, x + n+2*(s-1), -1); //we use n+2*(s-1) space.
		for(int i = 0; i < n; i++) scanf("%d", &x[i+s-1]); // real input starts from index = s-1
		
		fill(cnt+1, cnt+1+s, 0); // we need index starts from 1 to repersent real number.
		fill(ok, ok + n+s-1, 0); // here are n+s-1 sliding window we need to calculate.

		//check each n+s-1 sliding window to found if they are valid. index start from 0 to n+s-2.
		int sidx = s-1, eidx = n+s-2;  // start and end index for n.
		cnt[x[sidx]]++; //init for the first window
		tot = 1; //init for the first window
		for(int i = 0; i < n+s-1; i++){
			int t = 0; //how many n in this window
			for(int j = i; j < i+s; j++) 
				if((j >= sidx) && (j <= eidx)) t++;
			if(t == tot) ok[i]=1; //if the number of n in this window match tot, then this window is a valid window.

			//remove the first element and add the next element, update the cnt and tot for next iteration.
			if(x[i] != -1 && --cnt[x[i]] == 0) tot--;
			if(x[i+s] != -1 && cnt[x[i+s]]++ == 0) tot++;
		}

		int ans = s; //the max answser is "s". We need to remove invalid answer in the following logic.
		for(int i = 0; i < s; i++){ //check each "s" start position
			for(int j = i; j < n+s-1; j+=s){
				if(!ok[j]) {
					ans--; 
					break; //ingore this start position and check the next start position.
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

