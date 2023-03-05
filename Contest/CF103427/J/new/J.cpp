#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
using namespace std;
constexpr int MAXV = 9999;
constexpr int pow10[] = {1, 10, 100, 1000};
int step[MAXV+1];
queue<int> que;
void upbit(int &v, int b) {
    int ori = (v / pow10[b]) % 10;
    int now = (ori == 9 ? 0 : ori + 1);
    v += (now - ori) * pow10[b];
}
void downbit(int &v, int b) {
    int ori = (v / pow10[b]) % 10;
    int now = (ori == 0 ? 9 : ori - 1);
    v += (now - ori) * pow10[b];
}
void init() {
    for(int i = 0; i <= MAXV; i++)
        step[i] = -1;
    que.push(0);
    step[0] = 0;
    while(que.size()) {
        int u = que.front(); que.pop();
        for(int i = 0; i < 4; i++)
            for(int j = i; j < 4; j++) {
                int v = u;
                for(int k = i; k <= j; k++)
                    upbit(v, k);
                if(step[v] == -1) {
                    step[v] = step[u] + 1;
                    que.push(v);
                }
                v = u;
                for(int k = i; k <= j; k++)
                    downbit(v, k);
                if(step[v] == -1) {
                    step[v] = step[u] + 1;
                    que.push(v);
                }
            }
    }
}
string a, b;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    init();
    int T;
    cin >> T;
    while(T--) {
        cin >> a >> b;
        int x = 0;
        for(int i = 0; i < 4; i++)
            x += ((b[i] - a[i] + 10) % 10) * pow10[i];
        cout << step[x] << '\n';
    }
    return 0;
}
