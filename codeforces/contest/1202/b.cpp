#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;
const int N = 2e6 + 10;
char s[N];
int n, b[20];
void Min(int &x, int y) {
    if (x > y)
        x = y;
}

int main() {
    while (scanf("%s", s + 1) != EOF) {
        n = strlen(s + 1);
        for (int x = 0; x < 10; ++x) {
            for (int y = 0; y < 10; ++y) {
                for (int k = 0; k < 10; ++k) b[k] = INF;
                for (int p = 0; p < 10; ++p) {
                    for (int q = 0; q < 10; ++q)
                        if (p | q) {
                            Min(b[(p * x + q * y) % 10], p + q - 1);
                        }
                }
                int ans = 0;
                for (int i = 1; i < n; ++i) {
                    int t = (s[i + 1] - s[i] + 10) % 10;
                    if (b[t] == INF) {
                        ans = -1;
                        break;
                    }
                    ans += b[t];
                }
                printf("%d%c", ans, " \n"[y == 9]);
            }
        }
    }
    return 0;
}
