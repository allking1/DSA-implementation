#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define ll long long
const int MAX_N = 100001;
const int LOG = 17;

ll dp[MAX_N][LOG];
/* sparse table xây dựng giống quy hoạch động nhưng khác ở chỗ, dp[i][j] thì i là chỉ số bắt đầu j là độ dài 2^j tính từ i,
vì thế có thể giảm khối lượng tính toán đối với những bài gcd, min, max trên đoạn [L R] */

// Hàm tính log2 nhanh
int fastLog2(int x) {
    return 31 - __builtin_clz(x);
}

// Hàm tính GCD
ll gcd(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

// Xây dựng Sparse Table cho GCD
void buildSparseTable(vector<ll>& arr, int n) {
    for (int i = 1; i <= n; i++)
        dp[i][0] = arr[i];

    for (int j = 1; (1 << j) <= n; j++) {
        for (int i = 1; i + (1 << j) - 1 <= n; i++) {
            dp[i][j] = gcd(dp[i][j-1], dp[i + (1 << (j-1))][j-1]);
        }
    }
}

// Truy vấn GCD trên đoạn [l, r]
ll queryGCD(int l, int r) {
    int log = fastLog2(r - l + 1);
    return gcd(dp[l][log], dp[r - (1 << log) + 1][log]);
}

int main() {
    int n;
    cin >> n;
    vector<ll> a(n+1);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        dp[i][0] = a[i];
    }

    // Xây dựng Sparse Table
    buildSparseTable(a, n);

    // Tìm đoạn ngắn nhất có GCD = 1
    int l = 1, res = MAX_N;
    for (int r = 1; r <= n; r++) {
        while (l <= r && queryGCD(l, r) == 1) {
            res = min(res, r - l + 1);
            l++;  // Thu hẹp cửa sổ từ bên trái
        }
    }

    if (res == MAX_N)
        cout << -1;
    else
        cout << res;

    return 0;
}
