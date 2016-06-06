#include<cstdio>
#include<vector>
#include<ctime>
#include<algorithm>
#include<cassert>
using namespace std;

void fill_random_int(vector<int> & v, int count){
	v.clear();
	for(int i=0; i< count; i++){
		v.push_back(rand());
	}
}
vector<int> fill_random_int(int count){
	vector<int> v;
	for(int i=0; i< count; i++){
		v.push_back(rand());
	}
	return v;
}
void test_sort(vector<int> & v){
	sort(v.begin(), v.end());
	for(unsigned int i=0; i<v.size()-1; i++){
		assert(v[i]<=v[i+1]);
	}
}
int main(){
	srand(time(NULL));
	vector<int> v;
	fill_random_int(v, 1000000);
	//vector<int> v=fill_random_int(1000000);
	test_sort(v);
	printf("Time uased = %.4f", (double)clock()/CLOCKS_PER_SEC);
	return 0;
}

