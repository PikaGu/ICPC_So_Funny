#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define LL long long
#define uLL unsigned long long
#define INF 0x3f3f3f3f
#define debug(x) cout << #x << " = " << x << endl;
#define lid id << 1
#define rid id << 1 | 1
using namespace std;

const int mx = 50010;
int a[mx], ans[mx];
struct node{
    int l, r, id;
    bool operator < (const node& b) const {
        return l > b.l;
    }
}p[mx];
int tree[mx], b[mx];
int n;

inline int lowbit(int x){
    return x&(-x);
}

void add(int x, int v){
    while (x <= n){
        tree[x] = max(tree[x], v);
        x += lowbit(x);
    }
}

int query(int x){
    int ans = 0;
    while (x > 0){
        ans = max(ans, tree[x]);
        x -= lowbit(x);
    }
    return ans;
}

int main(){
    int t, q;
    scanf("%d", &t);
    while (t--){
        memset(b, 0, sizeof b);
        memset(tree, 0, sizeof tree);
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", &a[i]);
        scanf("%d", &q);
        for (int i = 1; i <= q; i++) {
            scanf("%d%d", &p[i].l, &p[i].r);
            p[i].id = i;
        }
        sort(p+1, p+q+1);
        int i = 1, j = n;
        while (i <= q){
            while (j >= 1 && j >= p[i].l){
                for (int k = 1; k*k <= a[j]; k++){
                    if (a[j] % k != 0) continue;
                    if (b[k]) add(b[k], k);
                    b[k] = j;
                    if (k*k != a[j]){
                        if (b[a[j]/k]) add(b[a[j]/k], a[j]/k);
                        b[a[j]/k] = j;
                    }
                }
                j--;
            }
            while (i <= q && p[i].l > j) {
                ans[p[i].id] = query(p[i].r);
                i++;
            }
        }
        for (int k = 1; k <= q; k++) printf("%d\n", ans[k]);
    }
    return 0;
}