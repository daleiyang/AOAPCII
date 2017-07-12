#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

struct Point{
    double x, y;
    Point(double x = 0, double y = 0):x(x), y(y){}
};
typedef Point Vector;
Vector operator + (Vector A, Vector B) {return Vector(A.x+B.x, A.y+B.y);}
Vector operator - (Point A, Point B) {return Vector(A.x-B.x, A.y-B.y);}
Vector operator * (Vector A, double p) {return Vector(A.x*p, A.y*p);}
Vector operator / (Vector A, double p) {return Vector(A.x/p, A.y/p);}
bool operator < (const Point& a, const Point& b){return a.x < b.x || (a.x == b.x && a.y < b.y);}
const double eps = 1e-10;
int dcmp(double x){
    if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}
bool operator == (const Point& a, const Point& b){
    return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}
double Dot(Vector A, Vector B) {return A.x*B.x + A.y*B.y;}
double Length(Vector A) {return sqrt(Dot(A, A));}
double Angle(Vector A, Vector B) {return acos(Dot(A, B) / Length(A) / Length(B));}
double Cross(Vector A, Vector B) {return A.x*B.y- A.y*B.x;}
double Area2(Point A, Point B, Point C){return Cross(B-A, C-A);}
Vector Rotate(Vector A, double rad){
    return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));
}
Vector Normal(Vector A){
    double L = Length(A);
    return Vector(-A.y/L, A.x/L);
}
Point GetLineIntersection(Point P, Vector v, Point Q, Vector w){
    Vector u = P-Q;
    double t = Cross(w, u) / Cross(v, w);
    return P+v*t;
}
double DistanceToLine(Point P, Point A, Point B){
    Vector v1 = B - A, v2 = P - A;
    return fabs(Cross(v1, v2)) / Length(v1);
}
double DistanceToSegment(Point P, Point A, Point B){
    if(A==B) return Length(P-A);
    Vector v1 = B - A, v2 = P - A, v3 = P - B;
    if(dcmp(Dot(v1, v2)) < 0) return Length(v2);
    else if(dcmp(Dot(v1, v3)) > 0) return Length(v3);
    else return fabs(Cross(v1, v2)) / Length(v1);
}
Point GetLineProjection(Point P, Point A, Point B){
    Vector v = B-A;
    return A+v*(Dot(v, P-A) / Dot(v, v));
}
bool SegmentProperIntersection(Point a1, Point a2, Point b1, Point b2){
    double c1 = Cross(a2-a1, b1-a1), c2 = Cross(a2-a1, b2-a1),
           c3 = Cross(b2-b1, a1-b1), c4 = Cross(b2-b1, a2-b1);
    return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}
bool OnSegment(Point p, Point a1, Point a2){
    return dcmp(Cross(a1-p, a2-p)) == 0 && dcmp(Dot(a1-p, a2-p)) < 0;
}
double PolygonArea(Point* p, int n){
    double area = 0;
    for(int i = 1; i < n-1; i++){
        area += Cross(p[i]-p[0], p[i+1]-p[0]);
    }
    return area/2;
}

const int maxn = 50+5;
double Max, Min;
Point P[maxn], Q[maxn];

Point read_point(){
    double x, y;
    scanf("%lf%lf", &x, &y);
    return Point(x, y);
}

void update(Point P, Point A, Point B){
    Min = min(Min, DistanceToSegment(P, A, B));
    Max = max(Max, Length(P-A));
    Max = max(Max, Length(P-B));
}

int main(){
#ifdef LOCAL
		freopen("UVa.11796.in", "r", stdin);
		freopen("UVa.11796.out", "w", stdout);
#endif
    int T, A, B;
    scanf("%d", &T);
    for(int kase = 1; kase <= T; kase++){
        scanf("%d%d", &A, &B);
        for(int i = 0; i < A; i++) P[i] = read_point();
        for(int i = 0; i < B; i++) Q[i] = read_point();

        double LenA = 0, LenB = 0;
        for(int i = 0; i < A-1; i++) LenA += Length(P[i+1]-P[i]);
        for(int i = 0; i < B-1; i++) LenB += Length(Q[i+1]-Q[i]);

        int Sa = 0, Sb = 0;
        Point Pa = P[0], Pb = Q[0];
        Min = 1e9, Max = -1e9;

        while(Sa < A-1 && Sb < B-1){
            double La = Length(P[Sa+1]-Pa);
            double Lb = Length(Q[Sb+1]-Pb);
            double T = min(La/LenA, Lb/LenB);
            Vector Va = (P[Sa+1]-Pa)/La*T*LenA;
            Vector Vb = (Q[Sb+1]-Pb)/Lb*T*LenB;
            update(Pa, Pb, Pb+Vb-Va);
            Pa = Pa + Va;
            Pb = Pb + Vb;
            if(Pa == P[Sa+1]) Sa++;
            if(Pb == Q[Sb+1]) Sb++;
        }
        printf("Case %d: %.0lf\n", kase, Max-Min);
    }
    return 0;
}
