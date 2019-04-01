#include <bits/stdc++.h>
#define LL long long
#define INF 0x3f3f3f3f
#define debug(x) cout << #x << " = " << x << endl;
using namespace std;

const int mx = 1e5+7;
const double eps = 1e-6;
struct point{
    double x, y;
}p[mx];
inline bool cmp(point& a, point& b){
    if (fabs(a.y-b.y) < eps) return a.x < b.x;
    return a.y < b.y;
}
int s[mx];
int top = 0;

bool judge(int a, int b, int c){
    return (p[a].y-p[b].y)*(p[b].x-p[c].x) > (p[a].x-p[b].x)*(p[b].y-p[c].y);
}

double dis(int a, int b){
    double dx = p[a].x-p[b].x;
    double dy = p[a].y-p[b].y;
    return sqrt(dx*dx+dy*dy);
}

void init(){
    s[1] = 1, s[2] = 2, top = 2;
}

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lf%lf", &p[i].x, &p[i].y);
    sort(p+1, p+n+1, cmp);
    init();
    for (int i = 3; i <= n; i++){
        while (top > 1 && !judge(i, s[top], s[top-1])) top--;
        s[++top] = i;
    }
    double ans = 0;
    for (int i = 2; i <= top; i++) ans += dis(s[i], s[i-1]);
    init();
    for (int i = 3; i <= n; i++){
        while (top > 1 && judge(i, s[top], s[top-1])) top--;
        s[++top] = i;
    }
    for (int i = 2; i <= top; i++) ans += dis(s[i], s[i-1]);
    printf("%.2f\n", ans);
    return 0;
}