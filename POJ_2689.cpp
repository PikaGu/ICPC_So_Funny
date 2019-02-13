#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#include<vector>
#include<queue>
#define INF 0x3f3f3f3f
#define LL long long
#define debug(x) cout << "[" << x << "]" << endl
using namespace std;

const int N = 1e6;
bool vis[N+100], p[N+100];
vector<int> prime;

void init(int n){
    for (int i = 2; i <= n; i++){
        if (vis[i]) continue;
        prime.push_back(i);
        for (int j = 2*i; j <= n; j += i) vis[j] = 1;
    }
}

int main(){
    freopen("/home/qaqorz/PikaGu/test.txt", "r", stdin);
    init(50000);
    LL l, r;
    while (scanf("%lld%lld", &l, &r) == 2){
        l = max(2LL, l);
        memset(p, 0, sizeof p);
        for (int i = 0; i < (int)prime.size(); i++){
            LL a = (l+prime[i]-1)/prime[i];
            LL b = r/prime[i];
            a = max(2LL, a);
            for (int j = a; j <= b; j++) p[j*prime[i]-l] = 1;
        }
        int mx = 0, mn = INF;
        int x1, y1, x2, y2, pre = -1;
        for (int i = 0; i <= r-l; i++){
            if (p[i]) continue;
            if (pre == -1){
                pre = i;
                continue;
            }
            if (mx < i-pre) mx = i-pre, x2 = pre+l, y2 = i+l;
            if (mn > i-pre) mn = i-pre, x1 = pre+l, y1 = i+l;
            pre = i;
        }
        if (!mx) printf("There are no adjacent primes.\n");
        else printf("%d,%d are closest, %d,%d are most distant.\n", x1, y1, x2, y2);
    }
    return 0;
}