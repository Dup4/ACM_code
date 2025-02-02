#include <bits/stdc++.h>
using namespace std;

#define endl "\n"
string s[3];

int main() {
    while (cin >> s[0] >> s[1] >> s[2]) {
        vector<int> vec[3];
        for (int i = 0; i < 3; ++i) {
            switch (s[i][1]) {
                case 'm':
                    vec[0].push_back(s[i][0] - '0');
                    break;
                case 'p':
                    vec[1].push_back(s[i][0] - '0');
                    break;
                case 's':
                    vec[2].push_back(s[i][0] - '0');
                    break;
            }
        }
        int res = 2;
        for (int i = 0; i < 3; ++i) {
            sort(vec[i].begin(), vec[i].end());
            if (vec[i].size() == 2) {
                int a = vec[i][0], b = vec[i][1];
                if (a == b || a + 1 == b || a + 2 == b) {
                    res = min(res, 1);
                }
            } else if (vec[i].size() == 3) {
                int a = vec[i][0], b = vec[i][1], c = vec[i][2];
                if ((a == b && b == c) || (a + 1 == b && b + 1 == c)) {
                    res = 0;
                } else if (a == b || b == c || a + 1 == b || b + 1 == c || a + 2 == b || b + 2 == c) {
                    res = min(res, 1);
                }
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
