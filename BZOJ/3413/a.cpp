#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 10;
const int ALP = 10;
int n, q;
char s[N], t[N];

struct SEG {
    struct node {
        int ls, rs, sum;
        node() {
            ls = rs = sum = 0;
        }
        node(int ls, int rs, int sum) : ls(ls), rs(rs), sum(sum) {}
    } t[N * 50];
    int tot;
    int newnode() {
        ++tot;
        t[tot] = node();
        return tot;
    }
    void Copy(int &x) {
        int tmp = newnode();
        t[tmp] = t[x];
        x = tmp;
    }
    void init() {
        tot = 0;
        newnode();
    }
    void up(int id) {
        int ls = t[id].ls, rs = t[id].rs, &sum = t[id].sum;
        sum = 0;
        if (ls)
            sum += t[ls].sum;
        if (rs)
            sum += t[rs].sum;
    }
    void update(int &now, int l, int r, int pos) {
        if (!now)
            now = newnode();
        if (l == r) {
            ++t[now].sum;
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(t[now].ls, l, mid, pos);
        else
            update(t[now].rs, mid + 1, r, pos);
        up(now);
    }
    void merge(int &x, int y, int l, int r) {
        if (!x || !y) {
            x |= y;
            return;
        }
        Copy(x);
        if (l == r) {
            t[x].sum = t[x].sum | t[y].sum;
            return;
        }
        int mid = (l + r) >> 1;
        merge(t[x].ls, t[y].ls, l, mid);
        merge(t[x].rs, t[y].rs, mid + 1, r);
        up(x);
    }
    int query(int id, int l, int r, int ql, int qr) {
        if (!id || ql > qr)
            return 0;
        if (l >= ql && r <= qr)
            return t[id].sum;
        int mid = (l + r) >> 1;
        int res = 0;
        if (ql <= mid)
            res += query(t[id].ls, l, mid, ql, qr);
        if (qr > mid)
            res += query(t[id].rs, mid + 1, r, ql, qr);
        return res;
    }
} seg;

struct SAM {
    //空间开两倍，节点个数是两倍字符串长度
    // maxlen 表示节点i表示的最大后缀长度, nx[j]表示节点i加一个字符j所表示的字符串对应的节点
    // minlen 表示节点i表示的最小后缀长度，其等于t[t[i].fa].maxlen + 1
    // fa 表示节点i的后缀链接 cnt 表示节点i的enspos集合大小
    // c[]表示拓扑排序辅助数组,　rk[]表示拓扑序，rk[i],i小的节点所表示的后缀长度也小
    struct node {
        int maxlen, pos, fa, rt, nx[ALP];
        node() {
            maxlen = pos = fa = rt = 0;
            memset(nx, 0, sizeof nx);
        }
    } t[N << 1];
    int tot, lst;
    struct Edge {
        int v, nx;
    } e[N << 1];
    int h[N << 1];
    inline void addedge(int u, int v) {
        e[++*h] = {v, h[u]};
        h[u] = *h;
    }
    inline int newnode() {
        ++tot;
        t[tot] = node();
        return tot;
    }
    inline void init() {
        tot = 0;
        lst = newnode();
    }
    inline void extend(int id, int _pos) {
        int cur = newnode(), p;
        t[cur].maxlen = t[lst].maxlen + 1;
        t[cur].pos = _pos;
        for (p = lst; p && !t[p].nx[id]; p = t[p].fa) t[p].nx[id] = cur;
        if (!p) {
            t[cur].fa = 1;
        } else {
            int q = t[p].nx[id];
            if (t[q].maxlen == t[p].maxlen + 1) {
                t[cur].fa = q;
            } else {
                int clone = newnode();
                t[clone] = t[q];
                t[clone].rt = 0;
                t[clone].maxlen = t[p].maxlen + 1;
                for (; p && t[p].nx[id] == q; p = t[p].fa) t[p].nx[id] = clone;
                t[cur].fa = t[q].fa = clone;
            }
        }
        lst = cur;
    }
    void DFS(int u) {
        for (int i = h[u]; i; i = e[i].nx) {
            int v = e[i].v;
            DFS(v);
            t[u].pos = min(t[u].pos, t[v].pos);
            seg.merge(t[u].rt, t[v].rt, 1, n);
        }
    }
    //字符串从0开始
    void build(char *s) {
        init();
        for (int i = 0; s[i]; ++i) {
            extend(s[i] - '0', i + 1);
            seg.update(t[lst].rt, 1, n, i + 1);
        }
        memset(h, 0, sizeof h);
        for (int i = 1; i <= tot; ++i)
            if (t[i].fa)
                addedge(t[i].fa, i);
        DFS(1);
    }
    int get(char *s) {
        int u = 1;
        for (int i = 1; s[i]; ++i) {
            if (!t[u].nx[s[i] - '0'])
                return -1;
            u = t[u].nx[s[i] - '0'];
        }
        return t[u].pos;
    }
    void gao(char *s) {
        int len = strlen(s + 1);
        ll ans = 0;
        int f = get(s);
        if (f == -1)
            ans += n;
        else
            ans += f - len + 1;
        for (int i = 1, u = 1; i < len; ++i) {
            if (!t[u].nx[s[i] - '0'])
                break;
            u = t[u].nx[s[i] - '0'];
            if (f == -1)
                ans += seg.query(t[u].rt, 1, n, 1, n);
            else
                ans += seg.query(t[u].rt, 1, n, 1, f - len + i);
        }
        printf("%lld\n", ans);
    }
} sam;

int main() {
    while (scanf("%d%s%d", &n, s, &q) != EOF) {
        sam.build(s);
        for (int _q = 1; _q <= q; ++_q) {
            scanf("%s", t + 1);
            sam.gao(t);
        }
    }
    return 0;
}
