#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#define INF 0x3f3f3f3f
#define debug(x) cout << #x << " = " << x << endl;
#define lid id << 1
#define rid id << 1 | 1
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;

const int mx = 50010;
int a[mx], gcd[mx<<2];
int g[mx*20];//gcd为i的区间有g[i]个

void push_up(int id){
    gcd[id] = __gcd(gcd[lid], gcd[rid]);
}

void build(int l, int r, int id){
    if (l == r){
        scanf("%d", &a[l]);
        gcd[id] = a[l];
        return;
    }
    int mid = (l+r)>>1;
    build(l, mid, lid);
    build(mid+1, r, rid);
    push_up(id);
}

int query(int L, int R, int id, int l, int r){
    if (l <= L && R <= r) return gcd[id];
    int mid = (L+R)>>1;
    if (l <= mid && mid < r)
        return __gcd(query(L, mid, lid, l, r), query(mid+1, R, rid, l, r));
    if (l <= mid) return query(L, mid, lid, l, r);
    return query(mid+1, R, rid, l, r);
}

pii queryl(int l, int r, int id, int v, int k){
    if (r <= k){
        if (gcd[id] % v == 0) return make_pair(v, l);
        if (l == r) return make_pair(__gcd(gcd[id], v), l);
    }
    int mid = (l+r)>>1;
    if (k <= mid) return queryl(l, mid, lid, v, k);
    pii tmp = queryl(mid+1, r, rid, v, k);
    if (tmp.first < v) return tmp;
    return queryl(l, mid, lid, v, k);
}

pii queryr(int l, int r, int id, int v, int k){
    if (k <= l){
        if (gcd[id] % v == 0) return make_pair(v, l);
        if (l == r) return make_pair(__gcd(gcd[id], v), l);
    }
    int mid = (l+r)>>1;
    if (k > mid) return queryr(mid+1, r, rid, v, k);
    pii tmp = queryr(l, mid, lid, v, k);
    if (tmp.first < v) return tmp;
    return queryr(mid+1, r, rid, v, k);
}

void upd(int l, int r, int id, int k, int v){
    if (l == r){
        gcd[id] = a[l] = v;
        return;
    }
    int mid = (l+r)>>1;
    if (k <= mid) upd(l, mid, lid, k, v);
    else upd(mid+1, r, rid, k, v);
    push_up(id);
}

void calc(int p, int& sum, int n, int f){
    vector<pii> vl, vr;
    int now = a[p], last = query(1, n, 1, 1, p), cur = p;
    vl.push_back(make_pair(now, cur));
    while (now != last){
        pii tmp = queryl(1, n, 1, now, cur);
        vl.push_back(tmp);
        now = tmp.first, cur = tmp.second;
    }
    vl.push_back(make_pair(last, 0));

    now = a[p], last = query(1, n, 1, p, n), cur = p;
    vr.push_back(make_pair(now, cur));
    while (now != last){
        pii tmp = queryr(1, n, 1, now, cur);
        vr.push_back(tmp);
        now = tmp.first, cur = tmp.second;
    }
    vr.push_back(make_pair(last, n+1));

    for (int i = 1; i < vl.size(); i++){
        int x = vl[i-1].second-vl[i].second;
        for (int j = 1; j < vr.size(); j++){
            int y = vr[j].second-vr[j-1].second;
            int num = f*x*y;
            int tmp = __gcd(vl[i-1].first, vr[j-1].first);
            if (g[tmp] == 0) sum++;
            g[tmp] += num;
            if (g[tmp] == 0) sum--;
        }
    }
}

int main(){
    int t, n, q, ks = 0;
    scanf("%d", &t);
    while (t--){
        memset(g, 0, sizeof g);
        scanf("%d%d", &n, &q);
        build(1, n, 1);
        int sum = 0;
        for (int i = 1; i <= n; i++){
            int now = a[i], pos = i;
            int last = query(1, n, 1, 1, i);
            while (now != last){
                //first: gcd
                //second: pos
                pii tmp = queryl(1, n, 1, now, pos);
                if (!g[now]) sum++;
                g[now] += pos-tmp.second;
                pos = tmp.second;
                now = tmp.first;
            }
            if (!g[last]) sum++;
            g[last] += pos;
        }
        printf("Case #%d:\n", ++ks);
        int p, v;
        while (q--){
            scanf("%d%d", &p, &v);
            calc(p, sum, n, -1);
            upd(1, n, 1, p, v);
            calc(p, sum, n, 1);
            printf("%d\n", sum);
        }
    }
    return 0;
}