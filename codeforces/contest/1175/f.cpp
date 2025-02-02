#include <bits/stdc++.h>
using namespace std;

#define N 300010
#define ull unsigned long long
int n, a[N];
ull hs[N], sum[N], f[N];

int calc(int x) {
    int ans = 0;
    int y = a[x];
    while (x < n && a[x + 1] != 1) {
        ++x;
        y = max(y, a[x]);
        if (x - y >= 0 && (sum[x] ^ sum[x - y]) == f[y]) {
            ++ans;
        }
    }
    return ans;
}

int main() {
    f[0] = 0;
    hs[0] = 1;
    for (int i = 1; i <= 300000; ++i) {
        hs[i] = hs[i - 1] * 37;
        f[i] = f[i - 1] ^ hs[i];
    }
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) {
            scanf("%d", a + i);
        }
        sum[0] = 0;
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i - 1] ^ hs[a[i]];
        }
        int ans = 0;
        for (int i = 1; i <= n; ++i) {
            if (a[i] == 1) {
                ans += calc(i) + 1;
            }
        }
        reverse(a + 1, a + 1 + n);
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i - 1] ^ hs[a[i]];
        }
        for (int i = 1; i <= n; ++i) {
            if (a[i] == 1) {
                ans += calc(i);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
