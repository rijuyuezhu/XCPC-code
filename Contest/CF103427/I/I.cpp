#include <algorithm>
#include <iostream>
#include <iomanip>
using namespace std;
using db = double;
constexpr db eps = 1e-8;
struct cp {
    db x, y;
    db Mo2()const {return x * x + y * y;}
    cp operator + (const cp &B)const {return {x + B.x, y + B.y};}
    cp operator - (const cp &B)const {return {x - B.x, y - B.y};}
    cp operator * (const cp &B)const {return {x * B.x - y * B.y, x * B.y + y * B.x};}
    cp operator / (const cp &B)const {return {(x * B.x + y * B.y) / B.Mo2(), (y * B.x - x * B.y) / B.Mo2()};}
};
istream& operator >> (istream &in, cp &B) {
    int a, b;
    in >> a >> b;
    B.x = a;
    B.y = b;
    return in;
}
ostream& operator << (ostream &out, const cp& B) {
    out << fixed << setprecision(8) << B.x << ' ' << B.y;
    return out;
}
cp z[4], w[4], a[4][5];
bool check1() {
    cp k = (w[1] - w[2]) / (z[1] - z[2]);
    cp b = w[1] - k * z[1];
    if((k * z[3] + b - w[3]).Mo2() < eps) {
        cout << k * z[0] + b << '\n';
        return 1;
    }
    return 0;
}
void Guass(int n) {
    int r = 1;
    for(int c = 1; c <= n; c++) {
        int num = r;
        for(int i = r+1; i <= n; i++)
            if(a[i][c].Mo2() > a[num][c].Mo2())
                num = i;
        if(num != r)
            for(int i = c; i <= n+1; i++)
                swap(a[r][i], a[num][i]);
        for(int i = r+1; i <= n; i++) {
            cp k = a[i][c] / a[r][c];
            for(int j = c; j <= n+1; j++)
                a[i][j] = a[i][j] - k * a[r][j];
        }
        r++;
    }
    for(int i = n; i >= 1; i--) {
        for(int j = i+1; j <= n; j++)
            a[i][n+1] = a[i][n+1] - a[j][n+1] * a[i][j];
        a[i][n+1] = a[i][n+1] / a[i][i];
    }
}
void work() {
    for(int i = 1; i <= 3; i++)
        cin >> z[i] >> w[i];
    cin >> z[0];
    if(check1())
        return;
    for(int i = 1; i <= 3; i++) {
        a[i][1] = z[i];
        a[i][2] = {1.0, 0.0};
        a[i][3] = {-w[i].x, -w[i].y};
        a[i][4] = w[i] * z[i];
    }
    Guass(3);
    cp A = a[1][4], B = a[2][4], D = a[3][4];
    cout << (A * z[0] + B) / (z[0] + D) << '\n';
}
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while(T--)
        work();
    return 0;
}
