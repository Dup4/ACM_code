#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define N 200010
char s[N];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", s + 1);
        int n = strlen(s + 1);
        int nowx = 0, nowy = 0;
        int up = 0, down = 0, left = 0, right = 0;
        int gup = 0, gdown = 0, gleft = 0, gright = 0;
        for (int i = 1; i <= n; ++i) {
            if (s[i] == 'W')
                --nowx;
            if (s[i] == 'S')
                ++nowx;
            if (s[i] == 'A')
                --nowy;
            if (s[i] == 'D')
                ++nowy;
            up = min(up, nowx);
            down = max(down, nowx);
            left = min(left, nowy);
            right = max(right, nowy);
            gup = max(gup, nowx - up);
            gdown = max(gdown, down - nowx);
            gleft = max(gleft, nowy - left);
            gright = max(gright, right - nowy);
        }
        ll x[2], y[2];
        x[0] = max(gup, gdown);
        x[1] = max(1ll * (gup || gdown), x[0] - (gup != gdown));
        y[0] = max(gleft, gright);
        y[1] = max(1ll * (gleft || gright), y[0] - (gleft != gright));
        printf("%lld\n", min((x[0] + 1) * (y[1] + 1), (x[1] + 1) * (y[0] + 1)));
    }
    return 0;
}
