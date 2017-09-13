#include<cstdio>
#include<iostream>
#include<queue>
using namespace std;

int main(){
#ifdef LOCAL
	freopen("UVA.10935.in", "r", stdin);
	freopen("UVA.10935.out", "w", stdout);
#endif
	int n;
	while(cin >> n && n){
		queue<int> q; int kase = 0;
		for(int i = 1; i <= n; i++) q.push(i);
		cout << "Discarded cards:";
		while(q.size()>=2){
			if(kase++) cout<<",";
			cout << " " << q.front(); q.pop();
			q.push(q.front()); q.pop();
		}
		cout << "\nRemaining card: " << q.front() << endl;
	}
	return 0;
}

