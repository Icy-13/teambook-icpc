const int INF = 2e18;
struct edge {
    int idx;
    int to;
    int flow;
    int max_flow;
    int rev_index;
    int cost;

    edge(int idx, int to, int flow, int max_flow, int rev_index, int cost)
        : idx(idx), to(to), flow(flow), max_flow(max_flow), rev_index(rev_index), cost(cost) {}
};

bool levit(vector<vector<edge>>& g, int s, int t, vector<int>& prev, vector<int>& prev_edge, int& path_flow) {
    int n = g.size();
    vector<int> dist(n, INF);
    vector<int> id(n, 2);
    dist[s] = 0;
    deque<int> q;
    q.push_back(s);
    while (!q.empty()) {
        int cur = q.front();
        q.pop_front();
        id[cur] = 2;
        for (int i = 0; i < g[cur].size(); i++) {
            edge& e = g[cur][i];
            if (e.flow >= e.max_flow) continue;
            int to = e.to;
            if (dist[to] > dist[cur] + e.cost) {
                dist[to] = dist[cur] + e.cost;
                prev[to] = cur;
                prev_edge[to] = i;
                if (id[to] == 2) {
                    q.push_front(to);
                    id[to] = 0;
                }
            }
        }
    }
    if (dist[t] == INF) return false;
    path_flow = INF;
    int cur = t;
    while (cur != s) {
        edge& e = g[prev[cur]][prev_edge[cur]];
        path_flow = min(path_flow, e.max_flow - e.flow);
        cur = prev[cur];
    }
    return true;
}

pii min_cost_max_flow(vector<vector<edge>>& g, int s, int t) {
    int flow = 0, cost = 0;
    int n = g.size();
    vector<int> prev(n), prev_edge(n);
    while (true) {
        int path_flow;
        if (!levit(g, s, t, prev, prev_edge, path_flow)) break;
        flow += path_flow;
        int cur = t;
        while (cur != s) {
            edge& e = g[prev[cur]][prev_edge[cur]];
            e.flow += path_flow;
            g[e.to][e.rev_index].flow -= path_flow;
            cost += e.cost * path_flow;
            cur = prev[cur];
        }
    }
    return {flow, cost};
}

void solve() {
    int n, m;
    cin >> n >> m;
    int s = 0, t = n - 1;
    vector<vector<edge>> g(n);
    int index = 1;
    for (int i = 0; i < m; i++) {
        int x, y, f, c;
        cin >> x >> y >> f >> c;
        x--;
        y--;
        g[x].pb(edge(index, y, 0, f, g[y].size(), c));
        g[y].pb(edge(-index, x, 0, 0, g[x].size() - 1, -c));
        index++;
    }
    auto [flow, cost] = min_cost_max_flow(g, s, t);
    cout << cost << "\n";
}
