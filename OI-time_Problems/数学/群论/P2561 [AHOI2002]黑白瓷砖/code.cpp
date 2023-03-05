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
const int MAXN = 22, MAXS = 250;
struct Bint {
	int A[405], n;
	Bint(int x = 0) {
		memset(A, 0x00, sizeof A);
		if(!x) n = 1; 
		else {
			n = 0;
			while(x) {
				A[n++] = x % 10;
				x /= 10;
			}
		}
	}
	int& operator [] (int k) {return A[k];}
	int operator [] (int k)const {return A[k];}
	Bint operator + (const Bint& B)const {
		Bint C; C.n = max(n, B.n);
		for(int i = 0; i < C.n; i++) {
			C[i] += A[i] + B[i];
			if(C[i] >= 10) C[i] -= 10, C[i+1]++;
		}
		if(C[C.n]) C.n++;
		while(C.n > 1 && C[C.n-1] == 0) C.n--;
		return C;
	}
	Bint operator * (int k)const {
		Bint C; C.n = n + 10;
		for(int i = 0; i < C.n; i++) {
			C[i] += A[i] * k;
			C[i+1] += C[i] / 10; C[i] %= 10;
		}
		while(C.n > 1 && C[C.n-1] == 0) C.n--;
		return C;
	}
	Bint operator / (int k)const {
		Bint C; C.n = n;
		int now = 0;
		for(int i = C.n-1; i >= 0; i--) {
			now = now * 10 + A[i];
			C[i] = now / k; now %= k;
		}
		while(C.n > 1 && C[C.n-1] == 0) C.n--;
		return C;
	}
	void print() {
		for(int i = n-1; i >= 0; i--) printf("%d", A[i]);
	}
}pw2[MAXS], ans;
int n, tot;
int main() {
	n = read(); tot = n * (n + 1) / 2;
	pw2[0] = 1;
	for(int i = 1; i <= tot; i++) pw2[i] = pw2[i-1] + pw2[i-1];
	ans = ans + pw2[tot];
	ans = ans + pw2[tot % 3 ? (tot - 1) / 3 + 1 : tot / 3] * 2;
	ans = ans + pw2[(tot - (n+1)/2) / 2 + (n+1)/2] * 3;
	ans = ans / 6;
	ans.print();
	printf("\n");
	return 0;
}
