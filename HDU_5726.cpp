#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#define INF 0x3f3f3f3f
#define debug(x) cout << #x << " = " << x << endl;
#define lid id << 1
#define rid id << 1 | 1
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;

const int mx = 1e5+7;
int a[mx], g[mx<<2];
map<int, LL> ans, mp[2];

void push_up(int id){
    g[id] = __gcd(g[lid], g[rid]);
}

void build(int l, int r, int id){
    if (l == r){
        scanf("%d", &a[l]);
        g[id] = a[l];
        return;
    }
    int mid = (l+r)>>1;
    build(l, mid, lid);
    build(mid+1, r, rid);
    push_up(id);
}

int query(int L, int R, int id, int l, int r){
    if (l <= L && R <= r) return g[id];
    int mid = (L+R)>>1;
    if (r <= mid) return query(L, mid, lid, l, r);
    if (mid < l) return query(mid+1, R, rid, l, r);
    return __gcd(query(L, mid, lid, l, r), query(mid+1, R, rid, l, r));
}

int main(){
    int t, n, q, ks = 0;
    scanf("%d", &t);
    while (t--){
        scanf("%d", &n);
        build(1, n, 1);
        ans.clear();
        mp[0].clear();
        for (int i = 1; i <= n; i++){
            mp[1] = mp[0];
            mp[0].clear();
            ans[a[i]]++;
            mp[0][a[i]]++;
            for (auto x : mp[1]){
                int k = __gcd(a[i], x.first);
                ans[k] += x.second;
                mp[0][k] += x.second;
            }
            mp[1].clear();
        }
        scanf("%d", &q);
        int l, r;
        printf("Case #%d:\n", ++ks);
        while (q--){
            scanf("%d%d", &l, &r);
            int k = query(1, n, 1, l, r);
            printf("%d %lld\n", k, ans[k]);
        }
    }
    return 0;
}