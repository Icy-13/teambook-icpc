// Find min (1, n) cut in undirected graph

#include <bits/stdc++.h>
// #pragma comment(linker, "/STACK:16777216")
//#pragma GCC optimize("O3")
//#pragma GCC target("avx2,sse4,fma,bmi,bmi2,popcnt,lzcnt,abm")

using namespace std;

using ll = long long;
using ull = unsigned long long;
using dbl = double;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdd = pair<dbl, dbl>;
using pld = pair<ld, ld>;

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// typedef tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

#define ft first
#define sc second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

struct Dinic {
    struct edge {
        int a, b;
        ll c, f{0};
        edge() = default;
        edge(int a, int b, int c) : a(a), b(b), c(c) {}
    };
    const ll INF = LLONG_MAX / 2;
    const int MAX_DIST = INT_MAX / 2;
    vector<edge> edges;
    vector<vector<int> > g;
    int n, m, s, t;
    int timer = 0;
    vector<int> ptr;
    vector<int> dist;
    vector<int> seen;
    Dinic() = default;
    Dinic(int n) : n(n) {
        m = 0;
        g.resize(n);
        ptr.resize(n);
        dist.resize(n, MAX_DIST);
        seen.resize(n, -1);
    }
    void add_undirected_edge(int a, int b, int c) {
        edges.emplace_back(a, b, c);
        edges.emplace_back(b, a, c);
        g[a].push_back(m);
        g[b].push_back(m + 1);
        m += 2;
    }
    void add_edge(int a, int b, int c) {
        edges.emplace_back(a, b, c);
        edges.emplace_back(b, a, 0);
        g[a].push_back(m);
        g[b].push_back(m + 1);
        m += 2;
    }
    bool bfs(int start) {
        queue<int> q;
        seen[start] = timer;
        dist[start] = 0;
        q.push(start);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (const auto id: g[v]) {
                if (edges[id].c == edges[id].f) continue;
                if (seen[edges[id].b] < timer) {
                    dist[edges[id].b] = dist[v] + 1;
                    seen[edges[id].b] = timer;
                    q.push(edges[id].b);
                }
            }
        }
        return seen[t] == timer;
    }
    ll dfs(int v, ll push) {
        if (!push || v == t) return push;
        for (int &to = ptr[v]; to < g[v].size(); to++) {
            int id = g[v][to];
            if (dist[v] + 1 != dist[edges[id].b]) continue;
            ll added = dfs(edges[id].b, min(push, edges[id].c - edges[id].f));
            if (added != 0) {
                edges[id].f += added;
                edges[id ^ 1].f -= added;
                return added;
            }
        }
        return 0;
    }
    ll flow(int s, int t) {
        this->s = s;
        this->t = t;
        ll f = 0;
        while (true) {
            if (!bfs(s)) break;
            timer++;
            std::fill(all(ptr), 0);
            while (ll add = dfs(s, INF)) {
                f += add;
            }
        }
        return f;
    }
};

void solve() {
    int n;
    int m;
    cin >> n >> m;
    Dinic dinic(n);
    for (int i = 0; i < m; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        dinic.add_undirected_edge(--a, --b, c);
    }
    int flow = dinic.flow(0, n - 1);
    vector<bool> used(n);
    vector<int> scut;
    auto collectS = [&](this auto &&self, const int v) -> void {
        used[v] = true;
        for (const auto id: dinic.g[v]) {
            if (auto &edge = dinic.edges[id];
                edge.c - edge.f > 0 && !used[edge.b]) {
                self(edge.b);
            }
        }
        scut.push_back(v);
    };

    collectS(0);
    vector<int> ans;
    for (auto v: scut) {
        for (const auto id: dinic.g[v]) {
            if (auto &edge = dinic.edges[id]; !used[edge.b]) {
                ans.push_back(id / 2);
            }
        }
    }
    cout << ans.size() << " " << flow << "\n";
    for (auto x: ans) cout << x + 1 << " ";
    cout << "\n";
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

#ifdef LOCAL
    freopen("c.in", "r", stdin);
    freopen("c.out", "w", stdout);
#endif

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}