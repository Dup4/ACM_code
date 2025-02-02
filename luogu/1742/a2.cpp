#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

typedef double db;
const int N = 1e5 + 10;
struct Point {
    db x, y;
    Point() {}
    Point(db x, db y) : x(x), y(y) {}
    void scan() {
        scanf("%lf%lf", &x, &y);
    }
    db dis(const Point &p) const {
        return hypot(x - p.x, y - p.y);
    }
} arr[N];
int n;

void gao() {
    db t = 100, pd = 0.98, eps = 1e-11;
    db res = 0x3f3f3f3f3f3f3f3f * 1.0;
    Point now = arr[1];
    int tmp = 1;
    while (t > eps) {
        for (int i = 1; i <= n; ++i)
            if (now.dis(arr[tmp]) < now.dis(arr[i]))
                tmp = i;
        db dis = now.dis(arr[tmp]);
        res = min(res, dis);
        now.x += (arr[tmp].x - now.x) / dis * t;
        now.y += (arr[tmp].y - now.y) / dis * t;
        t *= pd;
    }
    printf("%.10f\n%.10f %.10f\n", res, now.x, now.y);
}

int main() {
    while (scanf("%d", &n) != EOF) {
        for (int i = 1; i <= n; ++i) arr[i].scan();
        gao();
    }
    return 0;
}
