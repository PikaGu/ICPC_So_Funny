#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define LL long long
#define INF 0x3f3f3f3f
#define debug(x) cout << #x << " = " << x << endl;
using namespace std;

const int mx = 1e5+7;
int tot = 1;
int a[mx], b[mx], root[mx];
int ls[mx<<5], rs[mx<<5], sum[mx<<5];

void upd(int &rt, int l, int r, int k){
    ls[tot] = ls[rt], rs[tot] = rs[rt], sum[tot] = sum[rt]+1;
    rt = tot++;
    if (l == r) return;
    int mid = (l+r)>>1;
    if (k <= mid) upd(ls[rt], l, mid, k);
    else upd(rs[rt], mid+1, r, k);
}

int query(int u, int v, int l, int r, int k){
    if (l >= r) return l;
    int x = sum[ls[v]] - sum[ls[u]];
    int mid = (l+r)>>1;
    if (k <= x) return query(ls[u], ls[v], l, mid, k);
    return query(rs[u], rs[v], mid+1, r, k-x);
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
    for (int i = 1; i <= n; i++){
        int k = lower_bound(b+1, b+m+1, a[i])-b;
        root[i] = root[i-1];
        upd(root[i], 1, n, k);
    }
    int l, r, k;
    while (q--){
        scanf("%d%d%d", &l, &r, &k);
        int x = query(root[l-1], root[r], 1, n, k);
        printf("%d\n", b[x]);
    }
    return 0;
}