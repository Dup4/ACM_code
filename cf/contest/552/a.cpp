#include <bits/stdc++.h>
using namespace std;

#define ll long long

int main() {
    ll x[4];
    while (scanf("%lld", x) != EOF) {
        for (int i = 1; i < 4; ++i) {
            scanf("%lld", x + i);
        }
        sort(x, x + 4);
        printf("%lld %lld %lld\n", x[3] - x[0], x[3] - x[1], x[3] - x[2]);
    }
    return 0;
}
