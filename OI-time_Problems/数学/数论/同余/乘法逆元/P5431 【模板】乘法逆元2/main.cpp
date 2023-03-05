#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#include<vector>
using namespace std;
typedef long long ll;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
    for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
    for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + ch - '0';
    return x * f;
}
const int MAXN = 5e6 + 5;
int n, p, k;
int a[MAXN], s, pre[MAXN], nxt[MAXN];
int pls(int a, int b) {return a + b < p ? a + b : a + b - p;}
int mns(int a, int b) {return a < b ? a - b + p : a - b;}
int mul(int a, int b) {return 1ll * a * b % p;}

void exgcd(int a, int b, int& x, int& y) {
    if(!b) x = 1, y = 0;
    else exgcd(b, a % b, y, x), y -= (a / b) * x;
}
int inv(int a) {
    int x, y;
    exgcd(a, p, x, y);
    return (x % p + p) % p;
}
int main() {
    n = read(); p = read(); k = read();
    s = 1;
    for(int i = 1; i <= n; i++) a[i] = read();
    pre[0] = 1;
    for(int i = 1; i <= n; i++) pre[i] = mul(pre[i-1], a[i]);
    nxt[n+1] = 1;
    for(int i = n; i >= 1; i--) nxt[i] = mul(nxt[i+1], a[i]);

    int ans = 0, base = 1;
    for(int i = 1; i <= n; i++) {
        base = mul(base, k);
        ans = pls(ans, mul(base, mul(pre[i-1], nxt[i+1])));
    }
    printf("%d\n", mul(ans, inv(pre[n])));

    return 0;
}