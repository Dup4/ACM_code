#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 300010
int n;
char s[N];
int nx[N], a[N];

int main() {
    while (scanf("%s", s + 1) != EOF) {
        n = strlen(s + 1);
        int nxx[2] = {n + 1, n + 1};
        for (int i = n; i >= 1; --i) {
            nx[i] = nxx[s[i] - '0'];
            nxx[s[i] - '0'] = i;
        }
        memset(a, 0, sizeof a);
        ll res = 0;
        for (int i = 1; i <= n; ++i) {
            int it = nx[i];
            while (it <= n) {
                int nnx = it + it - i;
                if (nnx > n) {
                    break;
                }
                if (s[nnx] == s[i]) {
                    a[i] = (n - nnx + 1);
                    break;
                }
                it = nx[it];
            }
        }
        for (int i = n; i >= 1; --i) {
            a[i] = max(a[i], a[i + 1]);
            res += a[i];
        }
        printf("%lld\n", res);
    }
    return 0;
}
