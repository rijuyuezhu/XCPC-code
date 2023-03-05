#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
//char In[1 << 20], *ss = In, *tt = In;
//#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), ss == tt) ? EOF : *ss++)
ll read() {
	ll x = 0, f = 1; char ch = getchar();
	for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
	return x * f;
}
const int MAXL = 2e4 + 5, N = 8, NN = 100000000;
char buff[MAXL];
struct Bigint {
	int n; ll A[MAXL / N + 5];
	Bigint(ll x = 0) {
		n = 0; memset(A, 0x00, sizeof A);
		if(x == 0) n = 1;
		else {
			while(x) {
				A[n++] = x % NN;
				x /= NN;
			}
		}
	}
	void Read() {
		n = 0; memset(A, 0x00, sizeof A);
		scanf("%s", buff+1); int len = strlen(buff+1);
		for(int i = len; i >= 1; i -= N) {
			int j = max(1, i - N + 1);
			for(int k = j; k <= i; k++) A[n] = A[n] * 10 + int(buff[k] - '0');
			n++;
		}
	}
	void Write() {
		printf("%lld", A[n-1]);
		for(int i = n-2; i >= 0; i--) printf("%08lld", A[i]);
	}
	void clrpre0() {while(n > 1 && A[n-1] == 0) n--;}
	ll& operator [] (const int& k) {return A[k];}
	const ll& operator [] (const int& k)const {return A[k];}
	Bigint operator + (const Bigint& B)const {
		Bigint C; C.n = max(n, B.n);
		for(int i = 0; i < C.n; i++) {
			C[i] += A[i] + B[i];
			if(C[i] >= NN) C[i+1]++, C[i] -= NN;
		}
		if(C[C.n]) C.n++;
		C.clrpre0();
		return C;
	}
	bool operator < (const Bigint& B)const {
		if(n != B.n) return n < B.n;
		for(int i = n-1; i >= 0; i--)
			if(A[i] != B[i]) return A[i] < B[i];
		return 0;
	}
	Bigint operator - (const Bigint& B)const {//be sure that *this >= B
		Bigint C; C.n = n;
		for(int i = 0; i < C.n; i++) {
			C[i] += A[i] - B[i];
			if(C[i] < 0) C[i+1]--, C[i] += NN;
		}
		C.clrpre0();
		return C;
	}
	Bigint operator * (const Bigint& B)const {
		Bigint C; C.n = n + B.n - 1;
		for(int i = 0; i < n; i++)
			for(int j = 0; j < B.n; j++)
				C[i+j] += A[i] * B[j], C[i+j+1] += C[i+j] / NN, C[i+j] %= NN;
		if(C[C.n]) C.n++;
		C.clrpre0();
		return C;
	}
	Bigint operator * (const ll& k) const {
		Bigint C; C.n = n;
		for(int i = 0; i < C.n; i++)
			C[i] += A[i] * k, C[i+1] += C[i] / NN, C[i] %= NN;
		if(C[C.n]) C.n++;
		C.clrpre0();
		return C;
	}
	pair<Bigint, Bigint> div(const Bigint& B)const {
		Bigint C, D;
		C.n = n; D.n = 0;
		for(int i = C.n-1; i >= 0; i--) {
			D.n++; for(int j = D.n-1; j >= 1; j--) D[j] = D[j-1];
			D[0] = A[i];
			ll l = 0, r = NN-1;
			while(l <= r) {
				ll m = (l + r) >> 1;
				if(!(D < B * m)) l = m + 1, C[i] = m;
				else r = m - 1;
			}
			D = D - B * C[i];
		}
		C.clrpre0(), D.clrpre0();
		return make_pair(C, D);
	}
	Bigint operator / (const Bigint& B)const {
		return div(B).first;
	}
	Bigint operator % (const Bigint& B)const {
		return div(B).second;
	}
};
Bigint a, b;
pair<Bigint, Bigint> c;
int main() {
	//freopen("P1932_10.in", "r", stdin);
	//freopen("code.out", "w", stdout);
	a.Read(); b.Read();
	(a + b).Write(); puts("");
	if(a < b) {
		putchar('-');
		(b - a).Write();
	} else (a - b).Write();
	puts("");
	(a * b).Write();
	puts("");
	c = a.div(b);
	c.first.Write();
	puts("");
	c.second.Write();
	puts("");
	
	return 0;
}
