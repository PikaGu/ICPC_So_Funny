#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
#define debug(x) cout << #x << " = " << x << endl;
#define lid id << 1
#define rid id << 1 | 1
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<double,double> pdd;

const int mx = 110;
const double eps = 1e-10;
double lx, ly, lz, rx, ry, rz;
struct point{
    double x, y, z;
    point(double x=0, double y=0, double z=0): x(x), y(y), z(z){}
}p[mx];
int n;

double f(double a, double b, double c){
    double ans = 0;
    for (int i = 1; i <= n; i++){
        double dx = a-p[i].x;
        double dy = b-p[i].y;
        double dz = c-p[i].z;
        ans = max(ans, sqrt(dx*dx+dy*dy+dz*dz));
    }
    return ans;
}

double check2(double a, double b){
    double l = lz, r = rz;
    while (r-l > eps){
        double lmid = l + (r-l)/3;
        double rmid = r - (r-l)/3;
        if (f(a, b, lmid) >= f(a, b, rmid)) l = lmid;
        else r = rmid;
    }
    return l;
}

pdd check(double k){
    double l = ly, r = ry;
    while (r-l > eps){
        double lmid = l + (r-l)/3;
        double rmid = r - (r-l)/3;
        if (f(k, lmid, check2(k, lmid)) >= f(k, rmid, check2(k, rmid)))
            l = lmid;
        else r = rmid;
    }
    return make_pair(l, check2(k, l));
}

double search(){
    double l = lx, r = rx;
    while (r-l > eps){
        double lmid = l + (r-l)/3;
        double rmid = r - (r-l)/3;
        pdd kl = check(lmid), kr = check(rmid);
        if (f(lmid, kl.first, kl.second) >= f(rmid, kr.first, kr.second))
            l = lmid;
        else r = rmid;
    }
    pdd k = check(l);
    return f(l, k.first, k.second);
}

int main(){
    scanf("%d", &n);
    lx = ly = lz = 1e5+7;
    rx = ry = rz = -1e5-7;
    for (int i = 1; i <= n; i++){
        scanf("%lf%lf%lf", &p[i].x, &p[i].y, &p[i].z);
        lx = min(lx, 1.0*p[i].x);
        ly = min(ly, 1.0*p[i].y);
        lz = min(lz, 1.0*p[i].z);
        rx = max(rx, 1.0*p[i].x);
        ry = max(ry, 1.0*p[i].y);
        rz = max(rz, 1.0*p[i].z);
    }
    double ans = search();
    printf("%.6f\n", ans);
    return 0;
}
