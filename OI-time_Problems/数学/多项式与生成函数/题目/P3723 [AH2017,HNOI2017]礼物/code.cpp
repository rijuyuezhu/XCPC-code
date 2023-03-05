#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef long long ll;
typedef double db;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const db PI = acos(-1.0);
const ll INF = 1e18;
const int MAXN = 300005;
int n, m;
struct Complex {
	db x, y;
	Complex(db x = 0, db y = 0) :x(x), y(y) {}
	Complex operator + (const Complex& B)const {return Complex(x + B.x, y + B.y);}
	Complex operator - (const Complex& B)const {return Complex(x - B.x, y - B.y);}
	Complex operator * (const Complex& B)const {return Complex(x * B.x - y * B.y, x * B.y + y * B.x);}
}A[MAXN], B[MAXN];
ll a[MAXN], b[MAXN];
ll ans1, ans;
ll sa, sb, sa2, sb2;
int lim, id[MAXN];

void FFT(Complex f[], int fl) {
	for(int i = 0; i < lim; i++)
		if(i < id[i]) swap(f[i], f[id[i]]);
	for(int l = 2; l <= lim; l <<= 1) {
		int hl = l >> 1;
		Complex w0(cos(2 * PI / l), sin(2 * PI / l) * fl);
		for(int i = 0; i < lim; i += l) {
			Complex w(1, 0);
			for(int j = i; j < i + hl; j++, w = w * w0) {
				Complex tt = w * f[j + hl];
				f[j + hl] = f[j] - tt;
				f[j] = f[j] + tt;
			}
		}
	}
}
int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; i++) A[i].x = a[i] = read();
	for(int i = 1; i <= n; i++) B[i].x = b[i] = read();
	for(int i = 1; i <= n; i++) {
		sa += a[i], sb += b[i];
		sa2 += a[i] * a[i], sb2 += b[i] * b[i];
	}
	db c = -db(sa - sb) / n;
	ll c1 = floor(c), c2 = ceil(c);
	ans1 = min(1ll * n * c1 * c1 + 2ll * c1 * (sa - sb), 1ll * n * c2 * c2 + 2ll * c2 * (sa - sb)) + sa2 + sb2;
	for(int i = 1; i <= n; i++) A[i + n].x = A[i].x;
	reverse(B + 1, B + 1 + n);
	for(lim = 1; lim <= n * 3; lim <<= 1);
	id[0] = 0;
	for(int i = 1; i < lim; i++) id[i] = (id[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
	FFT(A, 1); FFT(B, 1);
	for(int i = 0; i < lim; i++) A[i] = A[i] * B[i];
	FFT(A, -1);
	for(int i = 0; i < lim; i++) A[i].x = (ll)(A[i].x / lim + 0.5);
	ans = INF;
	for(int i = 1; i <= n; i++)
		ans = min(ans, ans1 - 2 * (ll)A[i + n].x);
	printf("%lld\n", ans);
	return 0;
}
