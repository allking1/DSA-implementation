#include <bits/stdc++.h>
using namespace std;

int a[100], v[100], n, k, tong = 0;
bool check = false; 

void backtrack(int i) {
    if (tong == k) {
        for (int j = 1; j < i; j++) cout << v[j] << " ";
        cout << endl;
        check = true;
        return;
    }
    
    for (int j = 0; j < n; j++) { 
        if (tong + a[j] <= k && a[j]>=v[i-1]) {  
            v[i] = a[j]; 
            tong += a[j];
            backtrack(i + 1); 
            tong -= a[j]; 
        }
    }
}

int main() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a, a + n); 
    backtrack(1);
    if (!check) cout << "no solution";
}

