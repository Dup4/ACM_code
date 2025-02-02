#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 100010
const ll p = 998244353;
int n, a[N], num[N];
vector<vector<int>> vec;
int sze[20];

int getlen(int x) {
    int res = 0;
    while (x) {
        ++res;
        x /= 10;
    }
    return res;
}

ll f(ll x, int a, int b, int n) {
    vector<int> vec, A(22, 0);
    while (x) {
        vec.push_back(x % 10);
        x /= 10;
    }
    reverse(vec.begin(), vec.end());
    int len = a + b;
    if (a >= b) {
        auto it = vec.begin();
        for (int i = 1; i <= a - b + 1; ++i) {
            A[i] = *it;
            ++it;
        }
        for (int i = a - b + 3; i <= len; i += 2) {
            A[i] = *it;
            ++it;
        }
    } else {
        auto it = vec.begin();
        for (int i = b - a + 1; i <= len; i += 2) {
            A[i] = *it;
            ++it;
        }
    }
    //	for (int i = 1; i <= len; ++i) printf("%d%c", A[i], " \n"[i == len]);
    ll tot = 0;
    for (int i = 1; i <= len; ++i) {
        tot = tot * 10 + A[i];
        tot %= p;
    }
    return tot * n % p;
}

ll g(ll x, int b, int a, int n) {
    vector<int> vec, A(22, 0);
    while (x) {
        vec.push_back(x % 10);
        x /= 10;
    }
    reverse(vec.begin(), vec.end());
    int len = a + b;
    if (a >= b) {
        auto it = vec.begin();
        for (int i = a - b + 2; i <= len; i += 2) {
            A[i] = *it;
            ++it;
        }
    } else {
        auto it = vec.begin();
        for (int i = 1; i <= b - a; ++i) {
            A[i] = *it;
            ++it;
        }
        for (int i = b - a + 2; i <= len; i += 2) {
            A[i] = *it;
            ++it;
        }
    }
    ll tot = 0;
    for (int i = 1; i <= len; ++i) {
        tot = tot * 10 + A[i];
        tot %= p;
    }
    return tot * n % p;
}

int main() {
    while (scanf("%d", &n) != EOF) {
        vec.clear();
        vec.resize(20);
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
            vec[getlen(a[i])].push_back(a[i]);
        }
        for (int i = 1; i <= 10; ++i) sze[i] = (int)vec[i].size();
        ll res = 0;
        for (int i = 1; i <= 10; ++i)
            if (sze[i]) {
                for (auto it : vec[i]) {
                    for (int j = 1; j <= 10; ++j)
                        if (sze[j]) {
                            res += f(it, i, j, sze[j]);
                            res %= p;
                            res += g(it, i, j, sze[j]);
                            res %= p;
                        }
                }
            }
        printf("%lld\n", res);
    }
    return 0;
}
