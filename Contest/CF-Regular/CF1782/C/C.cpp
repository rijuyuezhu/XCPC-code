#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;
constexpr int INF = 0x3f3f3f3f;
int n;
string s;
vector<int> snum, id;
vector<int> add, mns;

bool cmp(int a, int b) {
    return snum[a] > snum[b];
}

void work() {
    cin >> n >> s;
    int ans = INF;
    string ansstring;
    snum = vector<int>(26);
    for(auto ch : s)
        snum[ch - 'a']++;
    for(int ty = 1; ty <= 26; ty++)
        if(n % ty == 0) {
            id = vector<int>(26);
            for(int i = 0; i < 26; i++)
                id[i] = i;
            int eve = n / ty;
            sort(id.begin(), id.end(), cmp);
            add = vector<int>();
            mns = vector<int>(26);
            for(int i = 0; i < ty; i++) {
                int c = id[i];
                if(snum[c] < eve) {
                    for(int k = snum[c]; k < eve; k++)
                        add.push_back(c);
                } else if(snum[c] > eve) {
                    for(int k = snum[c]; k > eve; k--)
                        mns[c]++;
                }
            }
            for(int i = ty; i < 26; i++) {
                int c = id[i];
                for(int k = snum[c]; k > 0; k--)
                    mns[c]++;
            }
            int ret = 0;
            string retstring = s;
            for(auto &ch : retstring) {
                int c = ch - 'a';
                if(mns[c]) {
                    ch = add.back() + 'a';
                    add.pop_back();
                    mns[c]--;
                    ret++;
                }
            }
            if(ret < ans) {
                ans = ret;
                ansstring = retstring;
            }
        }
    cout << ans << '\n' << ansstring << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while(t--)
        work();
    return 0;
}
