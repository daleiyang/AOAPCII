#include<stdio.h>
#include<string.h>
const int maxn=1005;
const double EPS=1e-5;
struct student{
	char SID[15];
	int CID;
	char Name[15];
	int sc[5];
	int total;
	double avg;
	int removed;
} s[maxn];
int n=0;
void add(){
	for(;;){
		printf("Please enter the SID, CID, name and four scores. Enter 0 to finish.\n");
		scanf("%s", s[n].SID);
		if(strcmp(s[n].SID, "0")==0) break;
		scanf("%d%s%d%d%d%d", &s[n].CID, s[n].Name, &s[n].sc[0], &s[n].sc[1], &s[n].sc[2], &s[n].sc[3]);
		int i;
		for(i=0; i<n; i++){if(s[i].removed==0 && strcmp(s[i].SID, s[n].SID)==0) break;}
		if(i<n) {printf("Duplicated SID.\n"); continue;}
		s[n].total=s[n].sc[0]+s[n].sc[1]+s[n].sc[2]+s[n].sc[3];
		s[n].avg=s[n].total/4.0+EPS;
		s[n].removed=0;
		n++;
	}
}
void deleteS(){
	char a[15];
	for(;;){
		printf("Please enter SID or name. Enter 0 to finish.\n");
		scanf("%s", a);
		if(strcmp(a, "0")==0) break;
		int c=0;
		for(int i=0; i<n; i++){
			if(s[i].removed==0 && (strcmp(s[i].SID, a)==0 || strcmp(s[i].Name, a)==0)){
				s[i].removed=1; c++;
			}
		}
		printf("%d student(s) removed.\n", c);
	}
}
void query(){
	char a[15];
	for(;;){
		printf("Please enter SID or name. Enter 0 to finish.\n");
		scanf("%s", a);
		if(strcmp(a, "0")==0) break;
		for(int i=0; i<n; i++){
			if(s[i].removed==0 && (strcmp(s[i].SID, a)==0 || strcmp(s[i].Name, a)==0)){
				int rank=0;
				for(int j=0; j<n; j++){
					if(s[j].removed==0 && s[i].total<s[j].total)
						rank++;
				}
				printf("%d %s %d %s %d %d %d %d %d %.2f\n", rank+1, s[i].SID, s[i].CID, s[i].Name, s[i].sc[0], s[i].sc[1], s[i].sc[2], s[i].sc[3], s[i].total, s[i].total/4.0+EPS);
			}
		}
	}
}
void statistics(){
	int cid;
	printf("Please enter class ID, 0 for the whole statistics.\n");
	scanf("%d", &cid);
	int c=0, m=0, e=0, p=0, cnt=0;
	int pass[maxn]; int cp[4]; int cf[4];
	memset(pass, -1, sizeof(pass));
	memset(cp, 0, sizeof(cp));
	memset(cf, 0, sizeof(cf));
	for(int i=0; i<n; i++){
		if(s[i].removed==1) continue;
		if(cid!=0 && s[i].CID!=cid) continue;
		c+=s[i].sc[0]; m+=s[i].sc[1]; e+=s[i].sc[2]; p+=s[i].sc[3]; pass[i]=0;
		if(s[i].sc[0]>=60) {pass[i]++; cp[0]++;} else{cf[0]++;}
		if(s[i].sc[1]>=60) {pass[i]++; cp[1]++;} else{cf[1]++;}
		if(s[i].sc[2]>=60) {pass[i]++; cp[2]++;} else{cf[2]++;}
		if(s[i].sc[3]>=60) {pass[i]++; cp[3]++;} else{cf[3]++;}
		cnt++;
	}
	printf("Chinese\nAverage Score: %.2lf\nNumber of passed students: %d\nNumber of failed students: %d\n\n", ((double)c)/cnt+EPS, cp[0], cf[0]);
	printf("Mathematics\nAverage Score: %.2lf\nNumber of passed students: %d\nNumber of failed students: %d\n\n", ((double)m)/cnt+EPS, cp[1], cf[1]);
	printf("English\nAverage Score: %.2lf\nNumber of passed students: %d\nNumber of failed students: %d\n\n", ((double)e)/cnt+EPS, cp[2], cf[2]);
	printf("Programming\nAverage Score: %.2lf\nNumber of passed students: %d\nNumber of failed students: %d\n\n", ((double)p)/cnt+EPS, cp[3], cf[3]);
	int x=0; for(int i=0; i<n; i++) if(pass[i]==4) x++;
	printf("Overall:\nNumber of students who passed all subjects: %d\n", x);
	x=0; for(int i=0; i<n; i++) if(pass[i]>=3) x++;
	printf("Number of students who passed 3 or more subjects: %d\n", x);
	x=0; for(int i=0; i<n; i++) if(pass[i]>=2) x++;
	printf("Number of students who passed 2 or more subjects: %d\n", x);
	x=0; for(int i=0; i<n; i++) if(pass[i]>=1) x++;
	printf("Number of students who passed 1 or more subjects: %d\n", x);
	x=0; for(int i=0; i<n; i++) if(pass[i]==0) x++;
	printf("Number of students who failed all subjects: %d\n\n", x);
}
int main(){
#ifdef LOCAL
		freopen("UVA.12412.in", "r", stdin);
		freopen("UVA.12412.out", "w", stdout);
#endif
	memset(s, 0, sizeof(student)*maxn);
	for(;;){
		printf("Welcome to Student Performance Management System (SPMS).\n\n1 - Add\n2 - Remove\n3 - Query\n4 - Show ranking\n5 - Show Statistics\n0 - Exit\n\n");
		int z;
		scanf("%d", &z);
		if(z==1){add();}
		if(z==2){deleteS();}
		if(z==3){query();}
		if(z==4){printf("Showing the ranklist hurts students' self-esteem. Don't do that.\n");}
		if(z==5){statistics();}
		if(z==0) break;
	}
	return 0;
}

