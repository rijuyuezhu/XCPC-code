#include<cstdio>
#include<cstring>
#include<algorithm>
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
const int MAXN = 1e5 + 5, MAXQ = 2e4 + 5;
const ll P = 1ll << 31;
int Q;
struct Qry {
    int n, m, a, id;
    bool operator < (const Qry& B)const {
        return a < B.a;
    }
}q[MAXQ];
ll ans[MAXQ];
int lim;
int pr[MAXN], ip[MAXN], tot;
ll mu[MAXN], sp[MAXN], sigma[MAXN];
void init(int n) {
    ip[1] = 1; mu[1] = 1; sp[1] = 1; sigma[1] = 1;
    for(int i = 2; i <= n; i++) {
        if(!ip[i]) {
            pr[++tot] = i;
            mu[i] = -1; sp[i] = i + 1; sigma[i] = i + 1;
        }
        for(int j = 1; j <= tot && 1ll * i * pr[j] <= n; j++) {
            int k = i * pr[j];
            ip[k] = 1;
            if(i % pr[j]) {
                mu[k] = -mu[i]; sp[k] = pr[j] + 1; sigma[k] = sigma[i] * (pr[j] + 1);
            } else {
                mu[k] = 0; sp[k] = sp[i] * pr[j] + 1; sigma[k] = sigma[i] / sp[i] * sp[k];
                break;
            }
        }
    }
}

struct Node {
	ll sg, i;
	bool operator < (const Node& B)const {return sg < B.sg;}
}a[MAXN];

ll t[MAXN];
void add(int i, ll k) {
	for(; i <= lim; i += i & -i) t[i] = (t[i] + k) % P;
}
ll sum(int i) {
	ll ans = 0;
	for(; i; i -= i & -i) ans = (ans + t[i]) % P;
	return ans;
}
void apply(int i) {
	for(int j = 1; 1ll * i * j <= lim; j++)
		add(i * j, sigma[i] % P * mu[j] % P);
}
ll query(int n, int m) {
	ll ans = 0;
	for(int i = 1, j; i <= n && i <= m; i = j + 1) {
		j = min(n / (n / i), m / (m / i));
		ans = (ans + 1ll * (n / i) * (m / i) % P * (sum(j) - sum(i-1)) % P);
	}
	return (ans % P + P) % P;
}
int main() {
    Q = read();
    for(int i = 1; i <= Q; i++) {
        int n = read(), m = read(), a = read();
        q[i] = (Qry){n, m, a, i};
        lim = max(lim, max(n, m));
    }    
	init(lim);
	for(int i = 1; i <= lim; i++)
		a[i] = (Node){sigma[i], i};
	sort(q + 1, q + 1 + Q);
	sort(a + 1, a + 1 + lim);
	int tot = 1;
	for(int i = 1; i <= Q; i++) {
		while(tot <= lim && a[tot].sg <= q[i].a) {
			apply(a[tot].i);
			tot++;
		}
		ans[q[i].id] = query(q[i].n, q[i].m);
	}
	for(int i = 1; i <= Q; i++) printf("%lld\n", ans[i]);
    return 0;
}
