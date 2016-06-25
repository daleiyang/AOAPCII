#include<cstdio>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

int opnum, bednum, otime, opToBed, opreset, bedreset, pnum;
struct patient{
	int id, stime, rtime, roomId, sstart, send, bedId, bstart, bend;
	char name[10];
	patient(int id = 0, int stime = 0, int rtime = 0):id(id), stime(stime), rtime(rtime){}
};
vector<patient> p;
bool cmp1(const patient & p1, const patient & p2){
	return p1.id < p2.id;
}
bool cmp3(const patient & p1, const patient & p2){
	return ((p1.send) < (p2.send)) 
		|| (((p1.send) == (p2.send))  && p1.roomId < p2.roomId);
}
struct roombed{
	int id, sstart, send, total;
	roombed(int id = 0, int sstart = 0, int send = 0, int total = 0)
		:id(id), sstart(sstart), send(send), total(total){}
};
vector<roombed> r, b;
struct cmp2{
	bool operator()(const int a, const int b) const{
		return (r[a].send > r[b].send) 
			|| (r[a].send == r[b].send && r[a].id > r[b].id);
	}
};
typedef priority_queue<int, vector<int>, cmp2> PQ;
PQ pq;

int main(){
#ifdef LOCAL
	freopen("UVA.212.in", "r", stdin);
	freopen("UVA.212.out", "w", stdout);
#endif
	while(scanf("%d%d%d%d%d%d%d", &opnum, &bednum, &otime, &opToBed, &opreset, &bedreset, &pnum) == 7){
		p.clear(); r.clear(); b.clear();
		PQ empty; swap(pq, empty);
		for(int i = 1; i <= pnum; i++){
			patient p1;
			p1.id = i;
			scanf("%s%d%d", p1.name, &p1.stime, &p1.rtime);
			p.push_back(p1);
		}
		for(int i = 1; i <= opnum; i++){r.push_back(roombed(i));}
		for(int i = 1; i <= bednum; i++){b.push_back(roombed(i));}
		sort(p.begin(), p.end(), cmp1);
		for(unsigned int i = 0; i < r.size(); i++){pq.push(i);}
		for(unsigned int i = 0; i < p.size(); i++){
			int t = pq.top();
			p[i].roomId = r[t].id;
			p[i].sstart = r[t].send;
			p[i].send = p[i].sstart + p[i].stime;
			r[t].sstart = p[i].sstart;
			r[t].send = r[t].sstart + p[i].stime + opreset;
			r[t].total += p[i].stime;
			pq.pop();
			pq.push(t);
		}
		sort(p.begin(), p.end(), cmp3);
		for(unsigned int i = 0; i < p.size(); i++){
			for(unsigned int j = 0; j < b.size(); j++){
				if(p[i].send >= (b[j].send == 0 ? b[j].send : b[j].send + bedreset)){
					p[i].bedId = b[j].id;
					p[i].bstart = b[j].sstart = p[i].send + opToBed;
					p[i].bend = b[j].send = p[i].bstart + p[i].rtime;
					b[j].total += p[i].rtime;
					break;
				}
			}
		}
		sort(p.begin(), p.end(), cmp1);
		puts(" Patient          Operating Room          Recovery Room");
		puts(" #  Name     Room#  Begin   End      Bed#  Begin    End");
		puts(" ------------------------------------------------------");
		for(unsigned int i = 0; i < p.size(); i++){
			printf("%2d  %-9s %2d  %3d:%02d  %3d:%02d    %3d  %3d:%02d  %3d:%02d\n",
				p[i].id, p[i].name, p[i].roomId, p[i].sstart/60+otime, p[i].sstart%60,
				p[i].send/60+otime, p[i].send%60, p[i].bedId, p[i].bstart/60+otime, p[i].bstart%60,
				p[i].bend/60+otime, p[i].bend%60
			);
		}
		int maxt = 0;
		for(unsigned int i = 0; i < p.size(); i++){maxt = max(maxt, p[i].bend);}
		puts("");
		puts("Facility Utilization");
		puts("Type  # Minutes  % Used");
		puts("-------------------------");
		for(unsigned int i = 0; i < r.size(); i++){
			printf("Room %2d %7d %7.2lf\n",r[i].id, r[i].total, maxt == 0 ? 0:(double)r[i].total*100/maxt);
		}
		for(unsigned int i = 0; i < b.size(); i++){
			printf("Bed  %2d %7d %7.2lf\n",b[i].id, b[i].total, maxt == 0 ? 0:(double)b[i].total*100/maxt);
		}
		puts("");
	}
	return 0;
}

