#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
#define LL long long
#define INF 0x3f3f3f3f
#define debug(x) cout << #x << " = " << x << endl
using namespace std;

const int mx = 1e5+10;
int ls[mx<<5], rs[mx<<5], sum[mx<<5];
int a[mx], b[mx], tree[mx];
int tot;

int build(int l, int r){
    int rt = ++tot;
    sum[rt] = 0;
    if (l == r) return rt;
    int mid = (l+r)>>1;
    ls[rt] = build(l, mid);
    rs[rt] = build(mid+1, r);
    return rt;
}

int upd(int l, int r, int id, int k){
    int rt = ++tot;
    ls[rt] = ls[id], rs[rt] = rs[id], sum[rt] = sum[id]+1;
    if (l == r) return rt;
    int mid = (l+r)>>1;
    if (k <= mid) ls[rt] = upd(l, mid, ls[id], k);
    else rs[rt] = upd(mid+1, r, rs[id], k);
    return rt;
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
    while (scanf("%d%d", &n, &q) == 2){
        tot = 0;
        for (int i = 1; i <= n; i++){
            scanf("%d", &a[i]);
            b[i] = a[i];
        }
        sort(b+1, b+n+1);
        int len = unique(b+1, b+n+1)-b-1;
        tree[0] = build(1, len);
        for (int i = 1; i <= n; i++){
            int k = lower_bound(b+1, b+len+1, a[i])-b;
            tree[i] = upd(1, len, tree[i-1], k);
        }
        while(q--){
            int x, y;
            scanf("%d%d", &x, &y);
            int l = 1, r = y-x+1, ans = 1;
            while (l <= r){
                int mid = (l+r)>>1;
                if (b[query(tree[x-1], tree[y], 1, len, (y-x+2)-mid)] >= mid) l = mid+1, ans = mid;
                else r = mid-1;
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}