#include <bits/stdc++.h>
using namespace std;

#define N 10010
char s[N];
int n;
void solve() {
    string t = "aeiou";
    for (int i = 1; i <= n; ++i)
        if (n % i == 0) {
            int a = i, b = n / i;
            if (a >= 5 && b >= 5) {
                int now = 0;
                int idi = 0;
                for (int i = 1; i <= a; ++i) {
                    int id = idi;
                    idi = (idi + 1) % 5;
                    for (int j = 1; j <= b; ++j) {
                        s[++now] = t[id];
                        id = (id + 1) % 5;
                    }
                }
                printf("%s\n", s + 1);
                return;
            }
        }
    puts("-1");
}

int main() {
    while (scanf("%d", &n) != EOF) {
        solve();
    }
    return 0;
}
