#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef int Tou[4];
Tou a, b, c;
bool flag;
void Input(Tou x) {
    cin >> x[0] >> x[1] >> x[2] >> x[3];
    sort(x, x + 4);
}
bool beat(Tou a, Tou b) {
    int win = 0, total = 0;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++) {
            if(a[i] > b[j])
                win++;
            if(a[i] != b[j])
                total++;
        }
    return win > total - win;
}
bool check() {
    if(( beat(a, b) && beat(b, c) && beat(c, a) ) || ( beat(b, a) && beat(a, c) && beat(c, b) )) {
        return 1;
    }
    else
        return 0;
}
void dfs(int step, int bgval) {
    if(step == 4) {
        if(check())
            flag = 1;
        return ;
    }
    for(int i = bgval; i <= 10 && !flag; i++) {
        c[step] = i;
        dfs(step+1, i);
    }
}
void work() {
    Input(a), Input(b);
    flag = 0;
    dfs(0, 1);
    if(flag)
        printf("yes\n");
    else
        printf("no\n");
}
int main() {
    int T;
    cin >> T;
    while(T--)
        work();
    return 0;
}