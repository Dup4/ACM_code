#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 1000010
int n;
ll l[N], r[N];
char s[N];

int main() {
    while (scanf("%s", s + 1) != EOF) {
        n = strlen(s + 1);
        l[0] = 0;
        for (int i = 1; i <= n; ++i) {
            l[i] = l[i - 1];
            if (i > 1 && s[i] == 'v' && s[i - 1] == 'v') {
                ++l[i];
            }
        }
        r[n + 1] = 0;
        for (int i = n; i >= 1; --i) {
            r[i] = r[i + 1];
            if (i < n && s[i] == 'v' && s[i + 1] == 'v') {
                ++r[i];
            }
        }
        ll res = 0;
        for (int i = 1; i <= n; ++i) {
            if (s[i] == 'o') {
                res += 1ll * l[i - 1] * r[i + 1];
            }
        }
        printf("%lld\n", res);
    }
    return 0;
}
