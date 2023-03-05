// https://www.luogu.com.cn/problem/P5686
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
typedef long long ll;
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 5e5 + 5;
const int P = 1e9 + 7;
int pls(int a, int b) {return a + b >= P ? a + b - P : a + b;}
int mns(int a, int b) {return a < b ? a - b + P : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}

int n, a[MAXN], b[MAXN];
int sa[MAXN], sb[MAXN];
int psa[MAXN], psb[MAXN], psab[MAXN];
int ans;
int main() {
    n = read();
    for(int i = 1; i <= n; i++) a[i] = read(), sa[i] = pls(sa[i-1], a[i]);
    for(int i = 1; i <= n; i++) b[i] = read(), sb[i] = pls(sb[i-1], b[i]);
    for(int i = n; i >= 0; i--) psa[i] = pls(psa[i+1], sa[i]);
    for(int i = n; i >= 0; i--) psb[i] = pls(psb[i+1], sb[i]);
    for(int i = n; i >= 0; i--) psab[i] = pls(psab[i+1], mul(sa[i], sb[i]));
    for(int i = 1; i <= n; i++)
        ans = pls(ans, pls(psab[i], mns(mul(n-i+1, mul(sa[i-1], sb[i-1])), pls(mul(sa[i-1], psb[i]), mul(sb[i-1], psa[i])))));
    printf("%d\n", ans);
    return 0;
}