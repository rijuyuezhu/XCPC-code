/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-29 21:25:48
 * @Description: https://www.luogu.com.cn/problem/P1939
 * @Tag: 矩阵，DP，递推，快速幂 
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
const int P = 1e9 + 7;
struct mint {
   int v;
   mint(int v=0) : v(v) {}
};
int MOD(int v) {return v >= P ? v - P : v;}
mint operator + (mint a, mint b) {return MOD(a.v + b.v);}
mint operator - (mint a, mint b) {return MOD(a.v - b.v + P);}
mint operator * (mint a, mint b) {return 1ll * a.v * b.v % P;}

struct Mat {
   mint A[3][3];
   mint* operator [] (int k) {return A[k];}
   const mint* operator [] (int k)const {return A[k];}
   void clear() {
      for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) A[i][j] = 0;
   }
   void unit() {
      for(int i = 0; i < 3; i++) for(int j = 0; j < 3; j++) A[i][j] = (i == j);
   }
   Mat() {clear();}
};
Mat operator * (const Mat& A, const Mat& B) {
   Mat ret; 
   for(int i = 0; i < 3; i++)
      for(int k = 0; k < 3; k++)
         for(int j = 0; j < 3; j++)
            ret[i][j] = ret[i][j] + A[i][k] * B[k][j];
   return ret;
}
Mat qpow(Mat a, int n) {
   Mat ret; ret.unit();
   for(; n; n >>= 1, a = a * a)
      if(n & 1) ret = ret * a;
   return ret;
}
Mat B;
mint solve(int n) {
   if(n <= 3) return 1;
   Mat ans = qpow(B, n-3);
   return ans[0][0] + ans[0][1] + ans[0][2];
}
int main() {
   B[0][0] = B[0][2] = B[1][0] = B[2][1] = 1;
   int T = read();
   while(T--) {
      int n = read();
      printf("%d\n", solve(n).v);
   }
   return 0;
}