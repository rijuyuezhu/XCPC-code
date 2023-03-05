/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-30 08:05:37
 * @Description: https://www.luogu.com.cn/problem/P3990
 * @Tag: 数学，矩阵，快速幂，DP
*/
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
char In[1 << 20], *ss = In, *tt = In;
#define getchar() (ss == tt && (tt = (ss = In) + fread(In, 1, 1 << 20, stdin), tt == ss) ? EOF : *ss++)
ll read() {
   ll x = 0, f = 1; char ch = getchar();
   for(; ch < '0' || ch > '9'; ch = getchar()) if(ch == '-') f = -1;
   for(; ch >= '0' && ch <= '9'; ch = getchar()) x = x * 10 + int(ch - '0');
   return x * f;
}

const int MAXN = 105;
const int P = 30011;
struct mint {
   int v;
   mint(int v = 0) : v(v) {}
};
int MOD(int v) {return v >= P ? v - P : v;}
mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
mint operator * (mint a, mint b) {return a.v * b.v % P;}
int Mat_size;
struct Mat {
   mint A[MAXN][MAXN];
   mint* operator [] (int k) {return A[k];}
   const mint* operator [] (int k)const {return A[k];}
   void clear() {
      for(int i = 1; i <= Mat_size; i++)
         for(int j = 1; j <= Mat_size; j++)
            A[i][j] = 0;
   }
   void unit() {
      for(int i = 1; i <= Mat_size; i++)
         for(int j = 1; j <= Mat_size; j++)
            A[i][j] = (i == j);
   }
};
Mat operator * (const Mat& a, const Mat& b) {
   Mat c; c.clear();
   for(int i = 1; i <= Mat_size; i++)
      for(int k = 1; k <= Mat_size; k++)
         for(int j = 1; j <= Mat_size; j++)
            c[i][j] = c[i][j] + a[i][k] * b[k][j];
   return c;
}
Mat qpow(Mat a, int n) {
   Mat ret; ret.unit();
   for(; n; n >>= 1, a = a * a)
      if(n & 1) ret = ret * a;
   return ret;
}

int n, m;
Mat B, ans;
int main() {
   n = read(), m = read();
   if(m == 1) {
      printf("%d\n", n == 1 ? 1 : 0);
   } else if(m == 2) {
      printf("%d\n", n == 1 || n == 2 ? 1 : 0);
   } else {
      Mat_size = 2 * n; B.clear();
      for(int i = 1; i <= n; i++) {
         B[i][i] = B[i+n][i] = B[i][i+n] = 1;
         if(i > 1) B[i][i-1] = 1;
         if(i < n) B[i][i+1] = 1;
      }
      ans = qpow(B, m-3);
      if(n == 1) printf("%d\n", (ans[n][1] + ans[n][n+1]).v);
      else if(n == 2) printf("%d\n", (2 * ans[n][1] + 2 * ans[n][2] + ans[n][n+1] + ans[n][n+1]).v);
      else printf("%d\n", (2 * ans[n][1] + 2 * ans[n][2] + ans[n][3] + ans[n][n+1] + ans[n][n+2]).v);
   }
   return 0;
}