///Дан орграф, найти два непересекающихся по ребрам пути из s в t, вывести вершины найденных путей.

#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#define int long long
#define pii pair <int, int>
#define fi first
#define se second
#define pb push_back
#define mp make_pair

using namespace std;

const int INF = 2e14;

struct edge {
    int idx;
    int to;
    int flow;
    int max_flow;
    int rev_index;

    edge(int idx, int to, int flow, int max_flow, int rev_index)
        : idx(idx), to(to), flow(flow), max_flow(max_flow), rev_index(rev_index) {}
};

pair <vector <vector <edge> >, bool> bfs(vector <vector <edge> > &g, int s, int t) {
    int n = g.size();
    vector <int> dist(n, INF);
    vector <vector <edge> > new_graph(n);
    dist[s] = 0;
    queue <int> q;
    q.push(s);
    while (!q.empty()) {
        int to = q.front();
        q.pop();
        for (int i = 0; i < g[to].size(); i++) {
            if (g[to][i].max_flow == g[to][i].flow) continue;
            if (dist[g[to][i].to] >= dist[to] + 1) {
                new_graph[to].pb(g[to][i]);
            }
            if (dist[g[to][i].to] > dist[to] + 1) {
                dist[g[to][i].to] = dist[to] + 1;
                q.push(g[to][i].to);
            }
        }
    }
    bool res = 0;
    if (dist[t] < INF) res = 1;
    return mp(new_graph, res);
}

int dfs(int s, vector <vector <edge> > &g, int t, vector <int> &ptr, int flow) {
    if (flow == 0) {
        return 0;
    }
    if (s == t) {
        return flow;
    }
    for (; ptr[s] < g[s].size(); ptr[s]++) {
        int i = ptr[s];
        int pushed = dfs(g[s][i].to, g, t, ptr, min(flow, g[s][i].max_flow - g[s][i].flow));
        if (pushed > 0) {
            g[s][i].flow += pushed;
            return pushed;
        }
    };
    return 0;
}

void do_dfs(vector <vector <edge> > &g, int s, int t) {
    vector <int> ptr(g.size(), 0);
    int pushed = 0;
    do {
        pushed = dfs(s, g, t, ptr, INF);
    } while (pushed > 0);
}

vector <vector <edge> > dinic(vector <vector <edge> > &g, int s, int t) {
    int n = g.size();
    while (true) {
        pair<vector <vector <edge> >, bool> g2 = bfs(g, s, t);
        if (g2.se == 0) {
            return g;
        }
        do_dfs(g2.fi, s, t);
        vector <int> ptr(n, 0);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < g2.fi[i].size(); j++) {
                int from = i;
                edge to = g2.fi[i][j];
                while (g[from][ptr[from]].idx != to.idx) {
                    ptr[from]++;
                }
                edge cur = g[from][ptr[from]];
                int diff = to.flow - cur.flow;
                g[from][ptr[from]].flow += diff;
                g[cur.to][cur.rev_index].flow -= diff;
            }
        }
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(NULL);
    cout.tie(NULL);
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    s--; t--;
    vector <vector <edge> > g(n);
    int index = 1;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        x--; y--;
        g[x].pb(edge(index++, y, 0, 1, g[y].size()));
        g[y].pb(edge(-index, x, 0, 0, g[x].size() - 1));
    }

    vector <vector <edge> > f = dinic(g, s, t);

    int flow = 0;
    for (int j = 0; j < f[s].size(); j++) {
        if (f[s][j].idx > 0) {
            flow += f[s][j].flow;
        }
    }

    if (flow < 2) {
        cout << "NO";
        return 0;
    }

    cout << "YES\n";

    vector <vector<int> > path(2);
    for (int i = 0; i < 2; i++) {
        int v = s;
        while (v != t) {
            path[i].push_back(v);
            for (auto &e : f[v]) {
                if (e.flow == 1) {
                    e.flow = 0;
                    v = e.to;
                    break;
                }
            }
        }
        path[i].push_back(t);
    }

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < path[i].size(); j++) {
            cout << path[i][j] + 1 << ' ';
        }
        cout << "\n";
    }

    return 0;
}
