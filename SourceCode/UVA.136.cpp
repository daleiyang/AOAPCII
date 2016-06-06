#include<iostream>
#include<set>
#include<queue>
#include<vector>
using namespace std;
typedef long long LL;
int main(){
	const int m[]={2,3,5};
	set<LL> s;
	priority_queue<LL, vector<LL>, greater<LL> > pq;
	pq.push(1);
	s.insert(1);
	int c=0;
	for(;;){
		LL t=pq.top(); pq.pop();
		c++;
		if(c==1500) {cout<<"The 1500'th ugly number is "<<t<<"."<<endl; break;}
		for(int i=0; i<3; i++){
			LL t2=t*m[i];
			if(!s.count(t2)){s.insert(t2); pq.push(t2);}
		}
	}
	return 0;
}

