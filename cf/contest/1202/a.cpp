#include <bits/stdc++.h>
using namespace std;

#define N 100010
char s[N], t[N];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s%s", s + 1, t + 1);
        int lens = strlen(s + 1);
        int lent = strlen(t + 1);
        int post = 0;
        for (int i = lent; i >= 1; --i) {
            if (t[i] == '1') {
                post = lent - i;
                break;
            }
        }
        int res = 0;
        for (int i = lens - post; i >= 1; --i) {
            if (s[i] == '1') {
                res = lens - post - i;
                break;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
