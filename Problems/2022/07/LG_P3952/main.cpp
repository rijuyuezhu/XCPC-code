/*
 * @Author: rijuyuezhu
 * @Date: 2022-07-27 15:34:58
 * @Description: https://www.luogu.com.cn/problem/P3952
 * @Tag: 模拟，栈
*/
#include<cstdio>
#include<algorithm>
using namespace std;
#define N 1000
int in_complexity, ans_complexity;
int is_err, cnt_norun, cnt_go, _sta, used[205];
char buff[30];
struct Node {
   char name;
   int cnt;
}sta[105];
void get_in_complexity() {
   scanf("%s", buff);
   if(buff[2] == '1') {
      in_complexity = 0;
   } else {
      sscanf(buff, "O(n^%d)", &in_complexity);
   }
   getchar(); // get the '\n' in the line end
}

void solve() { 
   if(is_err) return ;
   if(buff[0] == 'F') {
      char svar[5], sx[5], sy[5];
      char var;
      int x, y;
      sscanf(buff, "F %s %s %s", svar, sx, sy);
      var = svar[0];
      if(sx[0] == 'n') x = N;
      else sscanf(sx, "%d", &x);
      if(sy[0] == 'n') y = N;
      else sscanf(sy, "%d", &y);
      if(used[var]) {
         is_err = 1;
         return ;
      }
      used[var] = 1;
      sta[++_sta] = (Node){var, y-x};
      if(y-x < 0) cnt_norun++;
      if(y-x >= 100) cnt_go++;
      if(cnt_norun == 0) ans_complexity = max(ans_complexity, cnt_go);
   } else {
      if(_sta == 0) {
         is_err = 1;
         return ;
      }
      used[sta[_sta].name] = 0;
      int num = sta[_sta].cnt;
      if(num < 0) cnt_norun--;
      if(num >= 100) cnt_go--;
      --_sta;
   }
}

void work() {
   int L;
   scanf("%d", &L);
   get_in_complexity();
   ans_complexity = is_err = cnt_norun = cnt_go = _sta = 0;
   for(int i = 'a'; i <= 'z'; i++) used[i] = 0;
   for(int i = 1; i <= L; i++) {
      fgets(buff, 30, stdin);
      solve();
   }
   if(_sta > 0) is_err = 1;
   //print the ans
   if(is_err) {
      printf("ERR\n");
   } else if(in_complexity == ans_complexity) {
      printf("Yes\n");
   } else {
      printf("No\n");
   }
}
int main() {
   #ifdef LOCAL
   freopen("main.in", "r", stdin);
   #endif
   int t; scanf("%d", &t);
   while(t--) work();
   return 0;
}