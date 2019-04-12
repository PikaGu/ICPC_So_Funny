#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#define LL long long
#define INF 0x3f3f3f3f
#define debug(x) cout << #x << " = " << x << endl;
using namespace std;
#define lid id << 1
#define rid id << 1 | 1

const int mx = 1e5+7;
int a[mx];
int ls[mx<<2], rs[mx<<2], ms[mx<<2];

void push_up(int l, int r, int id){
    ls[id] = ls[lid];
    rs[id] = rs[rid];
    ms[id] = max(ms[lid], ms[rid]);
    int mid = (l+r)>>1;
    if (a[mid] < a[mid+1]) {
        ms[id] = max(ms[id], rs[lid]+ls[rid]);
        if (ls[id] == mid - l + 1) ls[id] += ls[rid];
        if (rs[id] == r - mid) rs[id] += rs[lid];
    }
}

void build(int l, int r, int id){
    if (l == r){
        scanf("%d", &a[l]);
        ls[id] = rs[id] = ms[id] = 1;
        return;
    }
    int mid = (l+r)>>1;
    build(l, mid, lid);
    build(mid+1, r, rid);
    push_up(l, r, id);
}

void upd(int l, int r, int k, int id, int x){
    if (l == r){
        a[l] = x;
        return;
    }
    int mid = (l+r)>>1;
    if (k <= mid) upd(l, mid, k, lid, x);
    else upd(mid+1, r, k, rid, x);
    push_up(l, r, id);
}

int query(int L, int R, int l, int r, int id){
    if (l <= L && R <= r) return ms[id];
    int mid = (L+R)>>1;
    int ans = 0;
    if (l <= mid) ans = max(ans, query(L, mid, l, r, lid));
    if (mid < r) ans = max(ans, query(mid+1, R, l, r, rid));
    //重点！！！！
    if (l <= mid && mid < r && a[mid] < a[mid+1])
        ans = max(ans, min(mid-l+1, rs[lid])+min(r-mid, ls[rid]));
    return ans;
}

int main(){
    int t, n, q;
    scanf("%d", &t);
    while (t--){
        scanf("%d%d", &n, &q);
        build(1, n, 1);
        char s[3];
        int l, r;
        while (q--){
            scanf("%s%d%d", s, &l, &r);
            if (s[0] == 'U') upd(1, n, l+1, 1, r);
            else printf("%d\n", query(1, n, l+1, r+1, 1));
        }
    }
    return 0;
}