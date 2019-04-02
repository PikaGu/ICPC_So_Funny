#include <bits/stdc++.h>
#define LL long long
#define INF 0x3f3f3f3f
#define debug(x) cout << #x << " = " << x << endl;
using namespace std;

const int mx = 5e4+10;
const double eps = 1e-8;

struct point{
    double x, y;
    point(double x=0, double y=0): x(x), y(y){}
    point operator + (const point& a) const {
        return point(x+a.x, y+a.y);
    }
    bool operator < (const point& a) const {
        if (fabs(a.x-x) < eps) return y < a.y;
        return x < a.x;
    }
}p[mx];
point rotate(double x, double y, double t){
    double s = sin(t), c = cos(t);
    return point(x*c-y*s, y*c+x*s);
}

int s[mx];

bool check(int a, int b, int c){
    return (p[a].x-p[b].x)*(p[c].y-p[b].y) < (p[a].y-p[b].y)*(p[c].x-p[b].x);
}

double dis(point& a, point& b){
    double dx = a.x-b.x;
    double dy = a.y-b.y;
    return sqrt(dx*dx+dy*dy);
}

int main(){
    int n, cnt = 0;
    double a, b, r;
    scanf("%d%lf%lf%lf", &n, &b, &a, &r);
    double x, y, t;
    for (int i = 1; i <= n; i++){
        scanf("%lf%lf%lf", &x, &y, &t);
        x += eps, y += eps, t += eps;
        p[++cnt] = rotate(a/2-r, -b/2+r, t)+point(x, y);
        p[++cnt] = rotate(a/2-r, b/2-r, t)+point(x, y);
        p[++cnt] = rotate(-a/2+r, -b/2+r, t)+point(x, y);
        p[++cnt] = rotate(-a/2+r, b/2-r, t)+point(x, y);
    }
    sort(p+1, p+cnt+1);
    int top = 0;
    for (int i = 1; i <= cnt; i++){
        while (top > 1 && check(i, s[top], s[top-1])) top--;
        s[++top] = i;
    }
    int tmp = top;
    for (int i = cnt-1; i >= 1; i--){
        while (top > tmp && check(i, s[top], s[top-1])) top--;
        s[++top] = i;
    }
    double ans = 0;
    for (int i = 1; i < top; i++) ans += dis(p[s[i]], p[s[i+1]]);
    printf("%.2f\n", ans+2*acos(-1)*r);
    return 0;
}