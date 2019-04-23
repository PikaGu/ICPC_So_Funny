#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
#define LL long long
#define INF 0x3f3f3f3f
#define debug(x) cout << #x << " = " << x << endl;
using namespace std;

const int mx = 2e6+7;
int a[mx];
int vis[mx], num[mx];
int n, sz, ans = 0;

struct node{
    int l, r, id;
    bool operator < (const node& a) const {
        if (l/sz == a.l/sz) return r < a.r;
        return l < a.l;
    }
}q[mx];

void add(int x){
    vis[a[x]]++;
    if (vis[a[x]] == 1) ans++;
}

void del(int x){
    vis[a[x]]--;
    if (vis[a[x]] == 0) ans--;
}

int main(){
    int m;
    scanf("%d", &n);
    sz = sqrt(n);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    scanf("%d", &m);
    for (int i = 1; i <= m; i++){
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
    }
    sort(q+1, q+m+1);
    int l = 1, r = 0;
    for (int i = 1; i <= m; i++){
        while (l < q[i].l) del(l), l++;
        while (l > q[i].l) l--, add(l);
        while (r < q[i].r) r++, add(r);
        while (r > q[i].r) del(r), r--;
        num[q[i].id] = ans;
    }
    for (int i = 1; i <= m; i++)
        printf("%d\n", num[i]);
    return 0;
}