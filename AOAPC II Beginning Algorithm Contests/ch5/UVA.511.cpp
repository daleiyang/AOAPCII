#include<iostream>
#include<sstream>
#include<cstdio>
#include<algorithm>
#include<cassert>
#include<vector>
#include<set>
#include<map>
#include<cmath>
using namespace std;

struct m{
	string name;
	double x1, y1, x2, y2, cx, cy, ratio, lrx, lry, minx;
	double area;
	m(string name, double x1, double y1, double x2, double y2){
		this->name = name;
		this->x1 = x1; 
		this->y1 = y1; 
		this->x2 = x2; 
		this->y2 = y2;
		this->area = fabs((x1-x2)*(y1-y2));
		this->cx = (x1+x2)/2; 
		this->cy = (y1+y2)/2;
		this->ratio = fabs((y1-y2)/(x1-x2));
		this->lrx = max(x1, x2); 
		this->lry = min(y1, y2);
		this->minx = min(x1, x2);
	}
	bool operator < (const m & m2) const{
		return area > m2.area;
	}
	bool contains(double x, double y){
		return ((x1 <= x && x <= x2) || (x2 <= x && x <= x1))
			&& ((y1 <= y && y <= y2) || (y2 <= y && y <= y1));
	}
};
vector<m> vm;

const double EPS=1e-7;
struct po{
	int mid;
	double dCenter, dLR;
	po(int mid, double x, double y){
		m t = vm[mid];
		this->mid = mid;
		this->dCenter = (t.cx-x)*(t.cx-x) + (t.cy-y)*(t.cy-y);
		this->dLR = (t.lrx-x)*(t.lrx-x) + (t.lry-y)*(t.lry-y);
	}
	bool operator < (const po & po2) const{
		m t = vm[mid], t2 = vm[po2.mid];
		return (dCenter < po2.dCenter) || (fabs(dCenter - po2.dCenter) < EPS && 
			((t.ratio < t2.ratio) || (fabs(t.ratio - t2.ratio) < EPS && 
				((dLR > po2.dLR) || (fabs(dLR - po2.dLR) < EPS && (t.minx < t2.minx)))
			))
		);
	}
};

typedef pair<double, double> p;
map<string, p> ml;
typedef unsigned int UI;

void input(){
	string s, name;
	double x1, y1, x2, y2;
	getline(cin, s);
	assert(s == "MAPS");
	while(getline(cin ,s) && s != "LOCATIONS"){
		stringstream ss(s);
		ss >> name >> x1 >> y1 >> x2 >> y2;
		vm.push_back(m(name, x1, y1, x2, y2));
	}
	sort(vm.begin(), vm.end());
	while(getline(cin ,s) && s != "REQUESTS"){
		stringstream ss(s);
		ss >> name >> x1 >> y1;
		ml[name] = p(x1, y1);
	}
}

int breakTie(vector<int> & t, double x, double y){
	int mid;
	if(t.size() == 1){mid = t[0];}
	if(t.size() > 1){
		vector<po> tie;
		for(UI i = 0; i < t.size(); i++){tie.push_back(po(t[i], x, y));}
		sort(tie.begin(), tie.end());
		mid = tie[0].mid;
	}
	return mid;
}

int main(){
	ios::sync_with_stdio(false);
#ifdef LOCAL
	freopen("UVA.511.in", "r", stdin);
	freopen("UVA.511.out", "w", stdout);
#endif
	input();
	string s, name; double x, y; UI L;
	while(getline(cin ,s) && s != "END"){
		stringstream ss(s);
		ss >> name >> L;
		if(!ml.count(name)) {
			cout << name << " at detail level " << L << " unknown location"<< endl;
			continue;
		}
		x = ml[name].first; y = ml[name].second;
		vector<vector<int> > cm; double pre = -1;
		for(UI i = 0; i < vm.size(); i++){
			if(vm[i].contains(x, y)){
				if(fabs(vm[i].area - pre) > EPS){
					vector<int> v; v.push_back(i);
					cm.push_back(v);
					pre = vm[i].area;
				}else{
					cm[cm.size()-1].push_back(i);
				}
			}
		}
		if(cm.size() == 0) {
			cout << name << " at detail level " << L << " no map contains that location"<< endl;
			continue;
		}
		if(cm.size() >= L){
			int mid = breakTie(cm[L-1], x, y);
			cout << name << " at detail level " << L << " using " << vm[mid].name << endl;
			continue;
		}
		if(cm.size() < L){
			int mid = breakTie(cm[cm.size()-1], x, y);	
			cout << name << " at detail level " << L << " no map at that detail level; using " << vm[mid].name << endl;
			continue;
		}
	}
	return 0;
}

