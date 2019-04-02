#include <bits/stdc++.h>
#define LL long long
#define INF 0x3f3f3f3f
#define debug(x) cout << #x << " = " << x << endl;
using namespace std;

const int mx = 1e5+10;

struct node{
    int x, y;
    node(int x=0, int y=0): x(x), y(y){}
    node operator - (const node& a) const {
        return node(x-a.x, y-a.y);
    }
    int operator * (const node& a) const {
        return x*a.y-y*a.x;
    }
    bool operator < (const node& a) const {
        if (x == a.x) return y < a.y;
        return x < a.x;
    }
}p[mx];
int s[mx], top = 0;

bool check(int a, int b, int c){
    return 1ll*(p[a].y-p[b].y)*(p[b].x-p[c].x) <=
            1ll*(p[a].x-p[b].x)*(p[b].y-p[c].y);
}

void getConvex(int n){
    for (int i = 1; i <= n; i++){
        while (top > 1 && check(i, s[top], s[top-1])) top--;
        s[++top] = i;
    }
    int tmp = top;
    for (int i = n-1; i >= 1; i--){
        while (top > tmp && check(i, s[top], s[top-1])) top--;
        s[++top] = i;
    }
}

LL dis2(int a, int b){
    int dx = p[a].x-p[b].x, dy = p[a].y-p[b].y;
    return 1ll*dx*dx+1ll*dy*dy;
}

LL geth(int a, int b, int c){
    return 1ll*((p[a]-p[c])*(p[b]-p[c]));
}

int main(){
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &p[i].x, &p[i].y);
    sort(p+1, p+n+1);
    getConvex(n);
    int t = 1;
    LL ans = 0;
    if (top == 3){
        printf("%lld\n", dis2(s[1], s[2]));
        return 0;
    }
    for (int i = 1; i < top; i++){
        while (geth(s[i], s[i+1], s[t]) <= geth(s[i], s[i+1], s[t+1]))
            t = t%top+1;
        ans = max(ans, dis2(s[i], s[t]));
        ans = max(ans, dis2(s[i+1], s[t]));
    }
    printf("%lld\n", ans);
    return 0;
}