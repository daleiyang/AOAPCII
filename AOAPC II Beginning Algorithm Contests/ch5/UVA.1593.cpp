#include<iostream>
#include<sstream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;

vector<string> a[1000 + 5];
const int maxlen = 180 + 5;
int len[maxlen]; 

int main(){
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("UVA.1593.in", "r", stdin);
	freopen("UVA.1593.out", "w", stdout);
#endif
	memset(len, 0, maxlen);
	string line; int idx = 0;
	while(getline(cin, line)){
		stringstream ss(line);
		string x; int i = 0;
		while(ss >> x){
			len[i] = max(len[i], (int)x.length());
			a[idx].push_back(x);
			i++;
		}
		idx++;
	}
	
	for(int i = 0; i < idx; i++){
		int size = a[i].size();
		for(int j = 0; j < size; j++){
			cout << a[i][j];
			if(j < size - 1){for(unsigned int k = 0; k < len[j] - a[i][j].size() + 1; k++) cout << " ";}
		}
		cout << endl;
	}
	return 0;
}

