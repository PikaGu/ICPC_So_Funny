#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
#define LL long long
#define INF 0x3f3f3f3f
#define debug(x) cout << #x << " = " << x << endl;
#define lid id << 1
#define rid id << 1 | 1
using namespace std;

const int mx = 2e5+7;
struct node{
    int l, r, id;
    bool operator < (const node& a) const {
        return r < a.r;
    }
}q[mx];
int a[mx], last[mx], pre[mx];
LL ans[mx];
LL maxx[mx<<2], lazy[mx<<2], sum[mx<<2], plazy[mx<<2];

void push_down(int id){
    if (lazy[id] || plazy[id]){
        plazy[lid] = max(plazy[lid], plazy[id]+lazy[lid]);
        plazy[rid] = max(plazy[rid], plazy[id]+lazy[rid]);
        maxx[lid] = max(sum[lid]+plazy[id], maxx[lid]);
        maxx[rid] = max(sum[rid]+plazy[id], maxx[rid]);
        sum[lid] += lazy[id];
        sum[rid] += lazy[id];
        lazy[lid] += lazy[id];
        lazy[rid] += lazy[id];
        lazy[id] = plazy[id] = 0;
    }
}

void push_up(int id){
    maxx[id] = max(maxx[lid], maxx[rid]);
    sum[id] = max(sum[lid], sum[rid]);
}

void upd(int L, int R, int id, int l, int r, int x){
    if (l <= L && R <= r){
        sum[id] += x;
        lazy[id] += x;
        plazy[id] = max(plazy[id], lazy[id]);
        maxx[id] = max(maxx[id], sum[id]);
        return;
    }
    push_down(id);
    int mid = (L+R)>>1;
    if (l <= mid) upd(L, mid, lid, l, r, x);
    if (mid < r) upd(mid+1, R, rid, l, r, x);
    push_up(id);
}

LL query(int L, int R, int id, int l, int r){
    if (l <= L && R <= r) return maxx[id];
    push_down(id);
    int mid = (L+R)>>1;
    LL ans = -1e15;
    if (l <= mid) ans = max(ans, query(L, mid, lid, l, r));
    if (mid < r) ans = max(ans, query(mid+1, R, rid, l, r));
    return ans;
}

int main(){
    int n, m;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        a[i] += 100001;
        pre[i] = last[a[i]]+1;
        last[a[i]] = i;
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; i++){
        scanf("%d%d", &q[i].l, &q[i].r);
        q[i].id = i;
    }
    sort(q+1, q+m+1);
    int j = 1;
    for (int i = 1; i <= m; i++){
        while (j <= q[i].r){
            upd(1, n, 1, pre[j], j, a[j] - 100001);
            j++;
        }
        ans[q[i].id] = query(1, n, 1, q[i].l, q[i].r);
    }
    for (int i = 1; i <= m; i++)
        printf("%lld\n", ans[i]);
    return 0;
}