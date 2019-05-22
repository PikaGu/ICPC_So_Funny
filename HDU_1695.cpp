#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
#define debug(x) cout << #x << " = " << x << endl;
#define lid id << 1
#define rid id << 1 | 1
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<double,double> pdd;

const int mx = 1e6+10;
int mu[mx], prime[mx];
bool vis[mx];
int tot = 0;

void init(int n){
    mu[1] = 1;
    for (int i = 2; i <= n; i++){
        if (!vis[i]) prime[++tot] = i, mu[i] = -1;
        for (int j = 1; j <= tot && 1ll*i*prime[j] <= n; j++){
            vis[i*prime[j]] = 1;
            if (i % prime[j] == 0) {
                mu[i*prime[j]] = 0;
                break;
            }
            mu[i*prime[j]] = -mu[i];
        }
    }
    for (int i = 2; i <= n; i++) mu[i] += mu[i-1];
}

int main(){
    int t, k, ks = 0;
    scanf("%d", &t);
    init(1000000);
    int a, b, c, d;
    while (t--){
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &k);
        printf("Case %d: ", ++ks);
        if (!k){
            printf("0\n");
            continue;
        }
        if (b > d) swap(b, d);
        b /= k, d /= k;
        LL ans = 0, ans2 = 0;
        int last;
        for (int i = 1; i <= b; i = last+1){
            last = min(b/(b/i), d/(d/i));
            ans += 1ll*(mu[last]-mu[i-1])*(b/i)*(d/i);
        }
        for (int i = 1; i <= b; i = last+1){
            last = b/(b/i);
            ans2 += 1ll*(mu[last]-mu[i-1])*(b/i)*(b/i);
        }
        printf("%lld\n", ans-ans2/2);
    }
    return 0;
}
