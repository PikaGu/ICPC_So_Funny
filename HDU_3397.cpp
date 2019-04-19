#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define LL long long
#define INF 0x3f3f3f3f
#define debug(x) cout << #x << " = " << x << endl;
#define lid id << 1
#define rid id << 1 | 1
using namespace std;

const int mx = 1e5+7;
int col[mx<<2], sum[mx<<2];
int ls[mx<<2], rs[mx<<2], ms[mx<<2];

void push_up(int l, int r, int id){
    sum[id] = sum[lid] + sum[rid];
    col[id] = (col[lid] == col[rid] ? col[lid] : -1);
    ls[id] = ls[lid], rs[id] = rs[rid];
    ms[id] = max(ms[lid], ms[rid]);
    int mid = (l+r)>>1;
    if (ls[id] == mid-l+1) ls[id] += ls[rid];
    if (rs[id] == r-mid) rs[id] += rs[lid];
    ms[id] = max(ms[id], ls[rid] + rs[lid]);
}

void build(int l, int r, int id){
    if (l == r){
        scanf("%d", &col[id]);
        sum[id] = col[id];
        ls[id] = rs[id] = ms[id] = col[id];
        return;
    }
    int mid = (l+r)>>1;
    build(l, mid, lid);
    build(mid+1, r, rid);
    push_up(l, r, id);
}

void push_down(int l, int r, int id){
    if (col[id] != -1){
        col[lid] = col[rid] = col[id];
        int mid = (l+r)>>1;
        sum[lid] = col[id]*(mid-l+1);
        sum[rid] = col[id]*(r-mid);
        ls[lid] = rs[lid] = ms[lid] = col[id]*(mid-l+1);
        ls[rid] = rs[rid] = ms[rid] = col[id]*(r-mid);
    }
}

void upd(int L, int R, int id, int l, int r, int x){
    if (l <= L && R <= r && col[id] != -1){
        if (x == 2) col[id] ^= 1;
        else col[id] = x;
        sum[id] = col[id]*(R-L+1);
        ls[id] = rs[id] = ms[id] = col[id]*(R-L+1);
        return;
    }
    push_down(L, R, id);
    int mid = (L+R)>>1;
    if (l <= mid) upd(L, mid, lid, l, r, x);
    if (mid < r) upd(mid+1, R, rid, l, r, x);
    push_up(L, R, id);
}

int querySum(int L, int R, int id, int l, int r){
    if (l <= L && R <= r) return sum[id];
    push_down(L, R, id);
    int mid = (L+R)>>1;
    int ans = 0;
    if (l <= mid) ans += querySum(L, mid, lid, l, r);
    if (mid < r) ans += querySum(mid+1, R, rid, l, r);
    return ans;
}

int query(int L, int R, int id, int l, int r){
    if (l <= L && R <= r) return ms[id];
    push_down(L, R, id);
    int mid = (L+R)>>1;
    int ans = 0;
    if (l <= mid) ans = max(ans, query(L, mid, lid, l, r));
    if (mid < r) ans = max(ans, query(mid+1, R, rid, l, r));
    if (l <= mid && mid < r)
        ans = max(ans, min(mid-l+1, rs[lid])+min(r-mid, ls[rid]));
    return ans;
}

int main(){
    int t, n, q;
    scanf("%d", &t);
    while (t--){
        scanf("%d%d", &n, &q);
        build(1, n, 1);
        int op, l, r;
        while (q--){
            scanf("%d%d%d", &op, &l, &r);
            l++, r++;
            if (op <= 2) upd(1, n, 1, l, r, op);
            else if (op == 3)
                printf("%d\n", querySum(1, n, 1, l, r));
            else printf("%d\n", query(1, n, 1, l, r));
        }
    }
    return 0;
}