#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;


constexpr int MAXB = 30;
constexpr int INF = 0x3f3f3f3f;
struct Node {
    int type;//0 means m, and 1 means d
    int num;//the num
    bool operator < (const Node b)const {
        if(type != b.type)
            return type < b.type;
        else
            return num < b.num;
    }
    bool operator == (const Node b)const {
        return type == b.type && num == b.num;
    }
};

void Input();
void Work();
string Convert_to_string(int v);
int Count_one(const string& s);
bool Merge();
void Init_table();
string Generate_combine(const string& s1, const string& s2);
bool CheckOver(const string &str, int num);
void Output();
void PrintItem(const string &str);

namespace DLX {
    constexpr int MAXN = 2e6 + 5;
    constexpr int MAXITEM = 2e6 + 5;
    int n, m, tot;
    int U[MAXITEM], D[MAXITEM], L[MAXITEM], R[MAXITEM], row[MAXITEM], col[MAXITEM], siz[MAXN], rh[MAXN];
    int ans[MAXN], ansStep = INF, bestAns[MAXN];

    void init(int _n, int _m) {
        n = _n, m = _m;
        tot = m+1;
        for(int i = 0; i <= m; i++) {
            U[i] = D[i] = i;
            L[i] = i-1;
            R[i] = i+1;
            siz[i] = 0;
        }
        for(int i = 1; i <= n; i++)
            rh[i] = -1;
        L[0] = m; R[m] = 0;
    }

    void ins(int r, int c) {
        ++siz[c];
        row[tot] = r;
        col[tot] = c;
        D[tot] = c;
        U[tot] = U[c];
        D[U[c]] = tot;
        U[c] = tot;
        if(rh[r] == -1) {
            rh[r] = L[tot] = R[tot] = tot;
        } else {
            R[tot] = rh[r];
            L[tot] = L[rh[r]];
            R[L[rh[r]]] = tot;
            L[rh[r]] = tot;
        }
        ++tot;
    }

    void del(int c) {
        for(int i = D[c]; i != c; i = D[i]) {
            R[L[i]] = R[i];
            L[R[i]] = L[i];
        }
    }

    void res(int c) {
        for(int i = U[c]; i != c; i = U[i]) {
            R[L[i]] = L[R[i]] = i;
        }
    }
    
    void dance(int step) {
        if(R[0] == 0) {
            if(step < ansStep) {
                ansStep = step;
                for(int i = 0; i < ansStep; i++)
                    bestAns[i] = ans[i];
            }
            return ;
        }
        int c = R[0];
        for(int i = R[0]; i != 0; i = R[i])
            if(siz[i] < siz[c])
                c = i;
        for(int i = D[c]; i != c; i = D[i]) {
            ans[step] = row[i];
            del(i);
            for(int j = R[i]; j != i; j = R[j])
                del(j);
            dance(step + 1);
            for(int j = L[i]; j != i; j = L[j])
                res(j);
            res(i);
        }
    }
}

int n; //the number of variants
int num_m; // the number of mX variants
vector<Node> inputs;
vector<vector<string> > table, newTable;
vector<string> Ustr;

int main() {
    Input();
    Work();
    Output();
    return 0;
}

void Input() {
    printf("Please input the number of variants: (<=26)");
    scanf("%d", &n);
    printf("Please input the items, like m2, d4, etc. And use space to divide them, end your item with -1\n");
    while(1) {
        char ch;
        int id;
        scanf(" %c%d", &ch, &id);
        if(ch == '-')
            break;
        else if(ch == 'm')
            inputs.push_back({0, id});
        else if(ch == 'd')
            inputs.push_back({1, id});
    }
    sort(inputs.begin(), inputs.end());
    int newSize = unique(inputs.begin(), inputs.end()) - inputs.begin();
    inputs.resize(newSize);
    for(auto val : inputs)
        if(val.type == 0)
            ++num_m;
}

void Output() {
    printf("The simplest sum of product is the sum of:\n");
    for(int i = 0; i < DLX::ansStep; i++)
        PrintItem(Ustr[DLX::bestAns[i]-1]);
}

void PrintItem(const string &str) {
    for(int i = 0; i < n; i++) {
        if(str[i] == '0') 
            printf("~%c", i+'A');
        else if(str[i] == '1')
            printf(" %c", i+'A');
        else
            printf("  ");
    }
    printf("\n");
}

void Work() {
    Init_table();
    while(Merge());
    sort(Ustr.begin(), Ustr.end());
    int newSize = unique(Ustr.begin(), Ustr.end()) - Ustr.begin();
    Ustr.resize(newSize);

    //Dancing link X algorithm to find.
    DLX::init(Ustr.size(), num_m);
    for(int i = 0; i < (int)Ustr.size(); i++) {
        const string &str = Ustr[i];
        for(int j = 0; j < num_m; j++) {
            if(CheckOver(str, inputs[j].num)) {
                DLX::ins(i+1, j+1);
            }
        }
    }
    DLX::dance(0);
}

string Convert_to_string(int v) {
    string ret;
    for(int i = n-1; i >= 0; i--)
        if((v >> i) & 1)
            ret.push_back('1');
        else
            ret.push_back('0');
    return ret + '0';
}

bool Merge() {
    newTable.clear();
    newTable.resize(n+1);
    bool success = 0;
    for(int i = 0; i < n; i++) {
        int j = i + 1;
        for(auto &str1 : table[i]) {
            for(auto &str2 : table[j]) {
                string newStr = Generate_combine(str1, str2);
                if(newStr.empty())
                    continue;
                success = 1;
                int c1 = Count_one(newStr);
                newTable[c1].push_back(newStr);
                str1[n] = '1'; str2[n] = '1';
            }
        }
    }
    for(int i = 0; i < n+1; i++)
        for(const auto &str : table[i])
            if(str[n] == '0') {
                Ustr.push_back(str.substr(0, n));
            }
    table = newTable;
    return success;
}

void Init_table() {
    table.resize(n+1);
    for(auto val : inputs) {
        string ret = Convert_to_string(val.num);
        int c1 = Count_one(ret);
        table[c1].push_back(ret);
    }
    for(auto &vec : table) {
        if(vec.empty()) continue;
        sort(vec.begin(), vec.end());
        int newSize = unique(vec.begin(), vec.end()) - vec.begin();
        vec.resize(newSize);
    }
}

int Count_one(const string& s) {
    int ans = 0;
    for(int i = 0; i < n; i++)
        if(s[i] == '1')
            ++ans;
    return ans;
}

string Generate_combine(const string& s1, const string& s2) {
    string ret;
    bool mdy = 0;
    for(int i = 0; i < n; i++) {
        if(s1[i] == s2[i])
            ret.push_back(s1[i]);
        else {
            if(s1[i] == '-' || s2[i] == '-')
                return string();
            else if(mdy)
                return string();
            else {
                mdy = 1;
                ret.push_back('-');
            }
        }
    }
    if(!mdy)
        return string();
    return ret + '0';
}

bool CheckOver(const string &str, int num) {
    for(int i = 0; i < n; i++)
        if(   (((num >> (n-i-1)) & 1) && str[i] == '0')
           || ((~(num >> (n-i-1)) & 1) && str[i] == '1'))
            return 0;
    return 1;
}