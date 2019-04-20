#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#define LL long long
#define INF 0x3f3f3f3f
#define debug(x) cout << #x << " = " << x << endl;
#define lid id << 1
#define rid id << 1 | 1
using namespace std;

const int mx = 1e5+7;
vector<int> G[mx];
int a[mx], b[mx], root[mx];
int p[mx][30], rk[mx];//LCA
int tot = 1;
int ls[mx*40], rs[mx*40], sum[mx*40];//主席树

void upd(int& rt, int l, int r, int k){
    ls[tot] = ls[rt], rs[tot] = rs[rt], sum[tot] = sum[rt]+1;
    rt = tot++;
    if (l == r) return;
    int mid = (l+r)>>1;
    if (k <= mid) upd(ls[rt], l, mid, k);
    else upd(rs[rt], mid+1, r, k);
}

const int S = 18;

void dfs(int u, int fa, int cnt){
    p[u][0] = fa;
    rk[u] = rk[fa]+1;
    for (int i = 1; i < S; i++) p[u][i] = p[p[u][i-1]][i-1];
    root[u] = root[fa];
    upd(root[u], 1, cnt, a[u]);
    for (int i = 0; i < G[u].size(); i++){
        int v = G[u][i];
        if (v == fa) continue;
        dfs(v, u, cnt);
    }
}

int lca(int x, int y){
    if (rk[x] < rk[y]) swap(x, y);
    int k;
    for (k = 0; (1<<(k+1)) <= rk[x]; k++);
    for (int i = k; i >= 0; i--)
        if (rk[x] - (1<<i) >= rk[y]) x = p[x][i];
    if (x == y) return x;
    for (int i = k; i >= 0; i--){
        if (p[x][i] && p[x][i] != p[y][i]){
            x = p[x][i];
            y = p[y][i];
        }
    }
    return p[x][0];
}

int query(int u, int v, int t, int fa, int l, int r, int k){
    if (l >= r) return l;
    int mid = (l+r)>>1;
    int x = sum[ls[v]]+sum[ls[u]]-sum[ls[t]]-sum[ls[fa]];
    if (k <= x) return query(ls[u], ls[v], ls[t], ls[fa], l, mid, k);
    return query(rs[u], rs[v], rs[t], rs[fa], mid+1, r, k-x);
}

int main(){
    int n, q;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    sort(b+1, b+n+1);
    int m = unique(b+1, b+n+1)-(b+1);
    for (int i = 1; i <= n; i++)
        a[i] = lower_bound(b+1, b+m+1, a[i])-b;
    int u, v, k;
    for (int i = 1; i < n; i++){
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1, 0, n);
    while (q--){
        scanf("%d%d%d", &u, &v, &k);
        int t = lca(u, v);
        int ans = query(root[u], root[v], root[t], root[p[t][0]], 1, n, k);
        printf("%d\n", b[ans]);
    }
    return 0;
}