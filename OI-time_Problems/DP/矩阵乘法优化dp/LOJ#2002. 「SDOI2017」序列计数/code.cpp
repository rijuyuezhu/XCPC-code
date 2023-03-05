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
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXP = 105, MAXM = 2e7 + 5, P = 20170408;
int pls(int a, int b) {return a + b < P ? a + b : a + b - P;}
int mns(int a, int b) {return a < b ? a + P - b : a - b;}
int mul(int a, int b) {return 1ll * a * b % P;}
int qpow(int a, int n) {int ret = 1; for(; n; n >>= 1, a = mul(a, a)) if(n & 1) ret = mul(ret, a); return ret;}
int n, m, p, ip[MAXM], pr[MAXM], tot, c[MAXP], ans1, ans2;
void Sieve(int n) {
	ip[1] = 1;
	for(int i = 2; i <= n; i++) {
		if(!ip[i]) {
			pr[++tot] = i;
		}
		for(int j = 1; j <= tot && 1ll * i * pr[j] <= n; j++) {
			ip[i * pr[j]] = 1;
			if(i % pr[j] == 0) break;
		}
	}
}
struct Matrix {
	int a[MAXP][MAXP];
	int n;
	void set(int n) {this->n = n;}
	void clear() {for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) a[i][j] = 0;}
	void setU() {for(int i = 0; i < n; i++) for(int j = 0; j < n; j++) a[i][j] = (i == j);}
	int* operator [] (int k) {return a[k];}
	const int* operator [] (int k)const {return a[k];}
	Matrix operator * (const Matrix& b)const {
		Matrix c; c.n = n; c.clear();
		for(int i = 0; i < n; i++)
			for(int k = 0; k < n; k++)
				for(int j = 0; j < n; j++)
					c[i][j] = pls(c[i][j], mul(a[i][k], b[k][j]));
		return c;
	}
	Matrix operator ^ (int n)const {
		Matrix a = *this, ret; ret.n = this->n; ret.setU();
		for(; n; n >>= 1, a = a * a) if(n & 1) ret = ret * a;
		return ret;
	}
}A;
int calc() {
	A.n = p; A.clear();
	for(int i = 0; i < p; i++)
		for(int j = 0; j < p; j++) {
			int nxt = i + j < p ? i + j : i + j - p;
			A[nxt][i] = pls(A[nxt][i], c[j]);
		}
	A = A ^ n;
	return A[0][0];
}
int main() {
	n = read(); m = read(); p = read();
	Sieve(m);
	for(int i = 0; i < p; i++) c[i] = 0;
	for(int i = 1; i <= m; i++) c[i % p]++;
	ans1 = calc();
	for(int i = 0; i < p; i++) c[i] = 0;
	for(int i = 1; i <= m; i++) if(ip[i]) c[i % p]++;
	ans2 = calc();
	printf("%d\n", mns(ans1, ans2));
	return 0;
}
