#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
typedef double db;
typedef long long ll;
//char In[1 << 20], *ss = In, *tt = In;
//#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXN = 4e5 + 5;
const db PI = acos(-1.0);

struct Complex {
	db x, y;
	Complex(db a = 0, db b = 0) : x(a), y(b) {}
	Complex operator + (const Complex& B)const {return Complex(x + B.x, y + B.y);}
	Complex operator - (const Complex& B)const {return Complex(x - B.x, y - B.y);}
	Complex operator * (const Complex& B)const {return Complex(x * B.x - y * B.y, x * B.y + y * B.x);}
}F[MAXN], G[MAXN], H[MAXN];
int n;
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
				Complex tt = w * f[j+hl];
				f[j+hl] = f[j] - tt;
				f[j] = f[j] + tt;
			}
		}
	}
}
int main() {
	n = read();
	for(int i = 1; i <= n; i++) {
		scanf("%lf", &F[i].x);
		G[n-i].x = F[i].x;
		H[i].x = 1.0 / i / i;
	}
	for(lim = 1; lim <= (n << 1); lim <<= 1);
	id[0] = 0;
	for(int i = 1; i < lim; i++) id[i] = (id[i >> 1] >> 1) | ((i & 1) ? (lim >> 1) : 0);
	FFT(F, 1); FFT(G, 1); FFT(H, 1);
	for(int i = 0; i < lim; i++) F[i] = F[i] * H[i];
	for(int i = 0; i < lim; i++) G[i] = G[i] * H[i];
	FFT(F, -1); FFT(G, -1);
	for(int i = 0; i < lim; i++)
		F[i].x /= lim, G[i].x /= lim;
	for(int i = 1; i <= n; i++)
		printf("%lf\n", F[i].x - G[n-i].x);
	return 0;
}
