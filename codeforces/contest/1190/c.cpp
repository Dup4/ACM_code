#include <bits/stdc++.h>
using namespace std;

#define N 100010
int n, k;
char s[N];
int sum[N];

bool ok1() {
    if (n == k)
        return 1;
    for (int i = 1; i + k - 1 <= n; ++i) {
        int l = i, r = i + k - 1;
        int lenL = l - 1, lenR = n - r;
        int L = sum[l - 1];
        int R = sum[n] - sum[r];
        if (l == 1 && (R == 0 || R == lenR))
            return 1;
        if (r == n && (L == 0 || L == lenL))
            return 1;
        if ((lenL == L && lenR == R) || (L == 0 && R == 0))
            return 1;
    }
    return 0;
}

bool ok2() {
    if (k < (n + 1) / 2)
        return 1;
    for (int i = 2; i + k - 1 < n; ++i) {
        int l = i, r = i + k - 1;
        int lenL = l - 1, lenR = n - r;
        int L = sum[l - 1];
        int R = sum[n] - sum[r];
        if ((L && L != lenL) || (R && R != lenR))
            return 1;
    }
    return 0;
}

int main() {
    char *fi = "tokitsukaze";
    char *se = "quailty";
    char *draw = "once again";
    while (scanf("%d%d", &n, &k) != EOF) {
        scanf("%s", s + 1);
        sum[0] = 0;
        for (int i = 1; i <= n; ++i) {
            sum[i] = sum[i - 1] - '0' + s[i];
        }
        if (ok1()) {
            puts(fi);
        } else if (ok2()) {
            puts(draw);
        } else {
            puts(se);
        }
    }
    return 0;
}
