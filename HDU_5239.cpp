#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<cstdlib> 
#define INF 0x3f3f3f3f
#define uLL unsigned long long
#define debug(x) cout << "[" << x << "]" << endl
using namespace std;
#define lid id << 1
#define rid id << 1 | 1

const uLL mod = 9223372034707292160ull;
const int mx = 1e5+7;
struct tree{
	int l, r;
	bool v;
	uLL sum;
}tree[mx<<2];
uLL ans = 0;
uLL a[mx];

uLL qmul(uLL x, uLL n){
	x %= mod;
	n %= mod;
	uLL res = 0;
	while (n){
		if (n & 1ull) res = (res + x) % mod;
		x = (x + x) % mod;
		n >>= 1ull; 
	}
	return res;
}

void push_up(int id){
	tree[id].sum = (tree[lid].sum + tree[rid].sum)%mod;
	tree[id].v = tree[lid].v & tree[rid].v;
}

void build(int l, int r, int id){
	tree[id].l = l;
	tree[id].r = r;
	tree[id].v = 0;
	if (l == r){
		tree[id].sum = a[l];
		return;
	}
	int mid = (l+r)>>1;
	build(l, mid, lid);
	build(mid+1, r, rid);
	push_up(id);
}

void upd(int l, int r, int id){
	if (tree[id].v && tree[id].l >= l && tree[id].r <= r) return;
	if (tree[id].l == tree[id].r){
		uLL tmp = qmul(tree[id].sum, tree[id].sum);
		if (tmp == tree[id].sum) tree[id].v = 1;
		tree[id].sum = tmp;
		return;
	}
	int mid = (tree[id].l + tree[id].r)>>1;
	if (r <= mid) upd(l, r, lid);
	else if (mid < l) upd(l, r, rid);
	else upd(l, mid, lid), upd(mid+1, r, rid);
	push_up(id);
}

uLL query(int l, int r, int id){
	if (tree[id].l == l && tree[id].r == r) return tree[id].sum%mod;
	int mid = (tree[id].l + tree[id].r)>>1;
	if (r <= mid) return query(l, r, lid);
	if (mid < l) return query(l, r, rid);
	return ( query(l, mid, lid) + query(mid+1, r, rid) )%mod;
}

int main(){
	freopen("/home/qaqorz/PikaGu/test.txt", "r", stdin);
	int t, kase = 0;
	scanf("%d", &t);
	while (t--){
		ans = 0;
		int n, q;
		scanf("%d%d", &n, &q);
		printf("Case #%d:\n", ++kase);
		for (int i = 1; i <= n; i++) scanf("%llu", &a[i]);
		build(1, n, 1);
		while (q--){
			int l, r;
			scanf("%d%d", &l, &r);
			ans = (ans + query(l, r, 1))%mod;
			printf("%llu\n", ans);
			upd(l, r, 1);
			//for (int i = 1; i <= n; i++) debug(query(i, i, 1));
		}
	}
	return 0;
}