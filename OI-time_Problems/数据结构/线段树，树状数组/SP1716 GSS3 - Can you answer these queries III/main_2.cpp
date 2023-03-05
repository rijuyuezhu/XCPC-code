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
const int INF = 0x3f3f3f3f;
const int MAXN = 50005;
struct Matrix {
	int A[3][3];
	Matrix() {
		for(int i = 0; i < 3; i++) 
			for(int j = 0; j < 3; j++)
				A[i][j] = -INF;
	}
	int* operator [] (const int& k) {return A[k];}
	const int* operator [] (const int& k)const {return A[k];}
	Matrix operator * (const Matrix& B)const {
		Matrix res;
		for(int k = 0; k < 3; k++)
			for(int i = 0; i < 3; i++)
				for(int j = 0; j < 3; j++) {
					res[i][j] = max(res[i][j], A[i][k] + B[k][j]);	
				}		
		return res;
	}
	void set(int v) {
		A[0][0] = A[0][2] = A[1][0] = A[1][2] = v;
		A[1][1] = A[2][2] = 0;
		A[0][1] = A[2][0] = A[2][1] = -INF;
	}
};

struct Segment_tree {
	#define ls o << 1
	#define rs o << 1 | 1
	Matrix val[MAXN << 2];
	void pushup(int o) {
		val[o] = val[rs] * val[ls];
	}
	void build(int o, int l, int r, int v[]) {
		if(l == r) {
			val[o].set(v[l]);
			return;
		}
		int m = (l + r) >> 1;
		build(ls, l, m, v);
		build(rs, m+1, r, v);
		pushup(o);
	}
	void mdypoint(int o, int l, int r, int x, int v) {
		if(l == r) {
			val[o].set(v);
			return;
		}
		int m = (l + r) >> 1;
		if(x <= m) mdypoint(ls, l, m, x, v);
		else mdypoint(rs, m+1, r, x, v);
		pushup(o);	
	}
	Matrix query(int o, int l, int r, int x, int y) {
		if(x <= l && r <= y) return val[o];
		int m = (l + r) >> 1;
		if(y <= m) return query(ls, l, m, x, y);
		else if(x > m) return query(rs, m+1, r, x, y);
		else return query(rs, m+1, r, x, y) * query(ls, l, m, x, y);
	}
	
	#undef ls
	#undef rs	
	
}tr;
int n, q;
int a[MAXN];
int main() {
    n = read();
    for(int i = 1; i <= n; i++) a[i] = read();
    tr.build(1, 1, n, a);
    q = read();
    while(q--) {
		int opt = read(), x = read(), y = read();
		if(opt == 0) {
			tr.mdypoint(1, 1, n, x, y);
		} else {
			Matrix a = tr.query(1, 1, n, x, y);
			printf("%d\n", max(a[1][0], a[1][2]));
		}	
	}
    return 0;
}
