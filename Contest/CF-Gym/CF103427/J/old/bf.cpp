#include <iostream>
#include <algorithm>
#include <queue>
#include <string>
#include <map>
using namespace std;
string a, b;
string ru(string s, int i, int j) {
    for(int k = i; k <= j; k++)
        s[k] = (s[k] == '9' ? '0' : s[k]+1);
    return s;
}
string rd(string s, int i, int j) {
    for(int k = i; k <= j; k++)
        s[k] = (s[k] == '0' ? '9' : s[k]-1);
    return s;
}
void work() {
    queue<string> q;
    map<string, int> mp;
    map<string, string> pre;
    cin >> a >> b;
    mp[a] = 0;
    q.push(a);
    while(q.size()) {
        string s = q.front(); q.pop();
        int sz = mp[s];
        if(s == b) {
            cout << sz << '\n';
            while(s != a) {
                cout << s << '\n';
                s = pre[s];
            }
            return ;
        }
        for(int i = 0; i < 4; i++)
            for(int j = i; j < 4; j++) {
                string t = ru(s, i, j);
                if(mp.find(t) == mp.end()) {
                    mp[t] = sz + 1;
                    pre[t] = s;
                    q.push(t);
                }
                t = rd(s, i, j);
                if(mp.find(t) == mp.end()) {
                    mp[t] = sz + 1;
                    pre[t] = s;
                    q.push(t);
                }
            }
    }
    return;
}
int main() {
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while(T--)
        work();
    return 0;
}
