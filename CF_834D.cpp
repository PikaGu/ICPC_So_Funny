#include <bits/stdc++.h>
#define LL long long
#define INF 0x3f3f3f3f3f3f3f3f
#define debug(x) cout << #x << " = " << x << endl;
#define lid id << 1
#define rid id << 1 | 1
using namespace std;

const int mx = 35010;
int a[mx], dp[mx], last[mx];
int add[mx<<2], maxv[mx<<2];

void push_up(int id){
    maxv[id] = max(maxv[lid], maxv[rid]);
}

void push_down(int id){
    if (add[id]){
        maxv[lid] += add[id];
        maxv[rid] += add[id];
        add[lid] += add[id];
        add[rid] += add[id];
        add[id] = 0;
    }
}

void build(int l, int r, int id){
    add[id] = 0;
    if (l == r){
        maxv[id] = dp[l];
        return;
    }
    int mid = (l+r)>>1;
    build(l, mid, lid);
    build(mid+1, r, rid);
}

void upd(int l, int r, int id, int x, int y){
    if (x <= l && r <= y){
        add[id] += 1;
        maxv[id] += 1;
        return;
    }
    push_down(id);
    int mid = (l+r)>>1;
    if (x <= mid) upd(l, mid, lid, x, y);
    if (mid < y) upd(mid+1, r, rid, x, y);
    push_up(id);
}

int query(int l, int r, int id, int x, int y){
    if (x <= l && r <= y) return maxv[id];
    push_down(id);
    int mid = (l+r)>>1, ans = 0;
    if (x <= mid) ans = max(ans, query(l, mid, lid, x, y));
    if (mid < y) ans = max(ans, query(mid+1, r, rid, x, y));
    return ans;
}

int main(){
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
    for (int i = 1; i <= k; i++){
        build(0, n, 1);
        for (int j = 1; j <= n; j++){
            dp[j] = 0;
            last[a[j]] = 0;
        }
        for (int j = 1; j <= n; j++){
            upd(0, n, 1, last[a[j]], j-1);
            last[a[j]] = j;
            dp[j] = query(0, n, 1, 0, j-1);
        }
    }
    printf("%d\n", dp[n]);
    return 0;
}