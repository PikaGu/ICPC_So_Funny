#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#define INF 0x3f3f3f3f
#define debug(x) cout << #x << " = " << x << endl;
using namespace std;
typedef long long LL;
typedef pair<int, int> pii;

const int mx = 2e6+7;
int ls[mx<<5], rs[mx<<5], sum[mx<<5]; //主席树
int L[mx], R[mx]; //路径
int root[mx]; //存树根
int a[mx]; //离散化数组
int b[mx]; //原数组
struct Query{
    int type;
    int x, y, k;
}q[mx]; //存询问
int n, tot = 1;
int cntl = 0, cntr = 0;

inline int lowbit(int x){
    return x & (-x);
}

//主席树的修改几乎没有变化
void upd(int& rt, int l, int r, int k, int v){
    ls[tot] = ls[rt], rs[tot] = rs[rt], sum[tot] = sum[rt]+v;
    rt = tot++;
    if (l == r) return;
    int mid = (l+r)>>1;
    if (k <= mid) upd(ls[rt], l, mid, k, v);
    else upd(rs[rt], mid+1, r, k, v);
}

//修改BIT是修改每一个结点上的主席树
void bit_add(int x, int l, int r, int c, int v){
    while (x <= n){
        upd(root[x], l, r, c, v);
        x += lowbit(x);
    }
}

int query(int l, int r, int k){
    if (l >= r) return l;
    //这里的前缀和找第k大同静态主席树
    //只不过套了树状数组之后
    //需要树状数组来定位
    int suml = 0, sumr = 0;
    for (int i = 1; i <= cntl; i++) suml += sum[ls[L[i]]];
    for (int i = 1; i <= cntr; i++) sumr += sum[ls[R[i]]];
    int mid = (l+r)>>1;
    if (sumr-suml >= k){
        //如果左边够k个数往左找
        //同时把路径变成这棵子树上的路径
        for (int i = 1; i <= cntl; i++) L[i] = ls[L[i]];
        for (int i = 1; i <= cntr; i++) R[i] = ls[R[i]];
        return query(l, mid, k);
    } else {
        //往右找
        for (int i = 1; i <= cntl; i++) L[i] = rs[L[i]];
        for (int i = 1; i <= cntr; i++) R[i] = rs[R[i]];
        return query(mid+1, r, k-(sumr-suml));
    }
}

int main() {
    int m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
        b[i] = a[i]; //用b[]存一下原来的
    }
    int cnt = n;
    char s[10];
    for (int i = 1; i <= m; i++){
        scanf("%s%d%d", s, &q[i].x, &q[i].y);
        if (s[0] == 'Q'){
            scanf("%d", &q[i].k);
            q[i].type = 1;
            q[i].x--;
        } else {
            q[i].type = 0;
            a[++cnt] = q[i].y; //待修改的数加进离散化
        }
    }
    //这一段是离散化
    sort(a+1, a+cnt+1);
    cnt = unique(a+1, a+cnt+1)-a-1;
    //以及把原数组加进树里
    for (int i = 1; i <= n; i++){
        int num = lower_bound(a+1, a+cnt+1, b[i])-a;
        bit_add(i, 1, cnt, num, 1);
    }

    for (int i = 1; i <= m; i++){
        if (q[i].type){
            //处理出被查询区间在树状数组上
            //对应的主席树的路径
            //即两个端点的前缀
            cntl = cntr = 0;
            for (int j = q[i].x; j > 0; j -= lowbit(j)) L[++cntl] = root[j];
            for (int j = q[i].y; j > 0; j -= lowbit(j)) R[++cntr] = root[j];
            printf("%d\n", a[query(1, cnt, q[i].k)]);
        } else {
            //先删掉
            int num = lower_bound(a+1, a+cnt+1, b[q[i].x])-a;
            bit_add(q[i].x, 1, cnt, num, -1);
            //再加回来
            num = lower_bound(a+1, a+cnt+1, q[i].y)-a;
            bit_add(q[i].x, 1, cnt, num, 1);
            //然后外面也关联一下
            b[q[i].x] = q[i].y;
        }
    }
    return 0;
}