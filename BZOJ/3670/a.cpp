#include <bits/stdc++.h>
using namespace std;

#define N 1000010
const int p = 1e9 + 7;
char s[N];

struct ExKMP {
    int Next[N];
    int extend[N];
    //下标从1开始
    void get_Next(char *s) {
        int lens = strlen(s + 1), p = 1, pos;
        // Next[1]要特殊考虑
        Next[1] = lens;
        while (p + 1 <= lens && s[p] == s[p + 1]) ++p;
        // Next[2]初始化
        Next[pos = 2] = p - 1;
        for (int i = 3; i <= lens; ++i) {
            int len = Next[i - pos + 1];
            //第一种情况
            if (len + i < p + 1)
                Next[i] = len;
            //第二种情况
            else {
                //找到对于子串最靠后已经匹配的位置
                int j = max(p - i + 1, 0);
                //暴力匹配
                while (i + j <= lens && s[j + 1] == s[i + j]) ++j;
                p = i + (Next[pos = i] = j) - 1;
            }
        }
    }

    void work(char *s, char *t) {
        get_Next(t);
        int lens = strlen(s + 1), lent = strlen(t + 1), p = 1, pos;
        while (p <= lent && s[p] == t[p]) ++p;
        p = extend[pos = 1] = p - 1;
        for (int i = 2; i <= lens; ++i) {
            int len = Next[i - pos + 1];
            if (len + i < p + 1)
                extend[i] = len;
            else {
                int j = max(p - i + 1, 0);
                while (i + j <= lens && j <= lent && t[j + 1] == s[i + j]) ++j;
                p = i + (extend[pos = i] = j) - 1;
            }
        }
    }
} exkmp;
int num[N];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", s + 1);
        int len = strlen(s + 1);
        exkmp.get_Next(s);
        for (int i = 1; i <= len; ++i) num[i] = 0;
        for (int i = 1; i <= len; ++i) {
            if (exkmp.Next[i]) {
                int l = i, r = min(2 * (i - 1), i + exkmp.Next[i] - 1);
                ++num[l];
                --num[r + 1];
            }
        }
        for (int i = 1; i <= len; ++i) num[i] += num[i - 1];
        int res = 1;
        for (int i = 1; i <= len; ++i) res = 1ll * res * (num[i] + 1) % p;
        printf("%d\n", res);
    }
    return 0;
}
