#include <bits/stdc++.h>
#define fi first
#define se second
#define SZ(x) ((int)x.size())
#define endl "\n" 
using namespace std;
using db = double;
using ll = long long;
using ull = unsigned long long; 
using pII = pair <int, int>;
using pLL = pair <ll, ll>;
constexpr int mod = 1e9 + 7;
template <class T1, class T2> inline void chadd(T1 &x, T2 y, int Mod = mod) { x += y; while (x >= Mod) x -= Mod; while (x < 0) x += Mod; } 
template <class T1, class T2> inline void chmax(T1 &x, T2 y) { if (x < y) x = y; }
template <class T1, class T2> inline void chmin(T1 &x, T2 y) { if (x > y) x = y; }
inline int rd() { int x; cin >> x; return x; }
template <class T> inline void rd(T &x) { cin >> x; }
template <class T> inline void rd(vector <T> &vec) { for (auto &it : vec) cin >> it; }  
#define dbg(x...) do { cout << "\033[32;1m" << #x << " -> "; err(x); } while (0) 
void err() { cout << "\033[39;0m" << endl; } 
template <class T, class... Ts> void err(const T& arg, const Ts&... args) { cout << arg << ' '; err(args...); }
template <template<typename...> class T, typename t, typename... A> 
void err(const T <t> &arg, const A&... args) { for (auto &v : arg) cout << v << ' '; err(args...); }
void ptt() { cout << endl; }
template <class T, class... Ts> void ptt(const T& arg, const Ts&... args) { cout << ' ' << arg; ptt(args...); }
template <class T, class... Ts> void pt(const T& arg, const Ts&... args) { cout << arg; ptt(args...); }
void pt() {}
template <template<typename...> class T, typename t, typename... A>
void pt(const T <t> &arg, const A&... args) { for (int i = 0, sze = arg.size(); i < sze; ++i) cout << arg[i] << " \n"[i == sze - 1]; pt(args...); }
inline ll qpow(ll base, ll n) { assert(n >= 0); ll res = 1; while (n) { if (n & 1) res = res * base % mod; base = base * base % mod; n >>= 1; } return res; }
//head
constexpr int N = 1e3 + 10, M = 1e6 + 60, INF = 0x3f3f3f3f;
int n, m, K, q, a[N][N]; 
int Move[][2] = {
	-1, 0,
	1, 0,
	0,-1,
	0, 1,
};

struct Graph {
	struct E { int to, nx; }e[M * 10]; int h[M], cnt;
	void init(int n) { for (int i = 1; i <= n; ++i) h[i] = -1; cnt = -1; }
	void addedge(int u, int v) { e[++cnt] = { v, h[u]}; h[u] = cnt; } 
}G;

inline int id(int x, int y) { return (x - 1) * m + y; }

inline bool ok(int x, int y) {
	if (x < 1 || x > n || y < 1 || y > m)
		return false;
	return true;
}

inline int getw(int v) {
	if (v > n * m) return 0;
	return 1;
}
struct Deque {
	int que[M * 5], l, r;
	void init() { l = M * 2, r = l - 1; }
	void push_front(int x) { que[--l] = x; }
	void push_back(int x) { que[++r] = x; }
	void pop_front() { ++l; }
	int front() { return que[l]; }
	bool empty() { return l > r; }
}deq;
short dis[41][M]; 
void bfs(int st, short *dis) { 
	for (int i = 1; i <= n * m + K; ++i)
		dis[i] = 1000;  
	deq.init();
	dis[st] = 0;
	deq.push_front(st);
	while (!deq.empty()) {
		int u = deq.front(); deq.pop_front();
		for (int i = G.h[u]; ~i; i = G.e[i].nx) {
			int v = G.e[i].to, w = getw(u);
			if (dis[v] > dis[u] + w) {
				dis[v] = dis[u] + w;
				if (w) deq.push_back(v);
				else deq.push_front(v);
			}
		}
	}
}

bool bfs1(int st, int ed, short *dis) {
	deq.init();
	deq.push_back(st);
	while (!deq.empty()) {
		int u = deq.front(); deq.pop_front();
		if (u == ed) return true;
		for (int i = G.h[u]; ~i; i = G.e[i].nx) {
			int v = G.e[i].to, w = getw(v);
			if (dis[v] == dis[u] - w) {
				deq.push_back(v);
			}
		}
	}
	return false;
}

int gao(int x[2], int y[2]) {
	if (x[0] == x[1] && y[0] == y[1]) return 0;
	if (a[x[0]][y[0]] == a[x[1]][y[1]] || abs(x[0] - x[1]) + abs(y[0] - y[1]) == 1) return 1;
	int u = id(x[0], y[0]), v = id(x[1], y[1]);
	int res = 1 + min(dis[a[x[0]][y[0]]][v], dis[a[x[1]][y[1]]][u]);
	if (dis[a[x[0]][y[0]]][v] < res && bfs1(v, u, dis[a[x[0]][y[0]]])) res = dis[a[x[0]][y[0]]][v];
	if (dis[a[x[1]][y[1]]][u] < res && bfs1(u, v, dis[a[x[1]][y[1]]])) res = dis[a[x[1]][y[1]]][u];
	return res;
}

void run() {
	G.init(n * m + K);
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) {
			cin >> a[i][j]; 
			int u = id(i, j);
			G.addedge(u, n * m + a[i][j]);
			G.addedge(n * m + a[i][j], u);
			for (int k = 0; k < 4; ++k) {
				int nx = i + Move[k][0];
				int ny = j + Move[k][1];
				if (ok(nx, ny)) {
					int v = id(nx, ny);
					G.addedge(u, v);
					G.addedge(v, u);
				}
			}
		}	
	}
	for (int i = 1; i <= K; ++i) bfs(n * m + i, dis[i]);
	cin >> q;
	for (int i = 1, x[2], y[2]; i <= q; ++i) {
		cin >> x[0] >> y[0] >> x[1] >> y[1];
		pt(gao(x, y));
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr); cout.tie(nullptr);
	cout << fixed << setprecision(20);
	while (cin >> n >> m >> K) run();
	return 0;
}
