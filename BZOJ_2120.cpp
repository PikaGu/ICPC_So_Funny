#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <set>
#define LL long long
#define INF 0x3f3f3f3f
#define debug(x) cout << #x << " = " << x << endl;
using namespace std;

const int mx = 1e6+7;
int a[mx], vis[mx*2], ans[mx];
int sz;
struct node{
    int l, r, t, id;
    bool operator < (const node& b) const {
        if (l/sz != b.l/sz) return l < b.l;
        if (r/sz != b.r/sz) return r < b.r;
        return t < b.t;
    }
}q[mx];
struct Change{
    int p, v;
}c[mx];
int qnum = 0, cnum = 0, sum = 0;

void add(int x){
    if (++vis[x] == 1) sum++;
}

void del(int x){
    if (--vis[x] == 0) sum--;
}

void change(int now, int i){
    if (q[i].l <= c[now].p && c[now].p <= q[i].r){
        del(a[c[now].p]);
        add(c[now].v);
    }
    swap(c[now].v, a[c[now].p]);
}

void mo(){
    int l = 1, r = 0, now = 0;
    for (int i = 1; i <= qnum; i++){
        while (l < q[i].l) del(a[l++]);
        while (l > q[i].l) add(a[--l]);
        while (r < q[i].r) add(a[++r]);
        while (r > q[i].r) del(a[r--]);
        while (now < q[i].t) change(++now, i);
        while (now > q[i].t) change(now--, i);
        ans[q[i].id] = sum;
    }
    for (int i = 1; i <= qnum; i++)
        printf("%d\n", ans[i]);
}

int main(){
    int n, m;
    scanf("%d%d", &n, &m);
    sz = pow(n, 2.0/3);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    char s[3];
    for (int i = 1; i <= m; i++){
        scanf("%s", s);
        if (s[0] == 'Q'){
            qnum++;
            scanf("%d%d", &q[qnum].l, &q[qnum].r);
            q[qnum].id = qnum;
            q[qnum].t = cnum;
        }
        else{
            cnum++;
            scanf("%d%d", &c[cnum].p, &c[cnum].v);
        }
    }
    sort(q+1, q+qnum+1);
    mo();
    return 0;
}