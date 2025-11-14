bool kuhn(int v, vector<vector<int>>& g, vector<int>& mt, vector<int>& used, int timer) {
    if (used[v] == timer) return false;
    used[v] = timer;
    for (auto to : g[v]) {
        if (mt[to] == -1) {
            mt[to] = v;
            return true;
        }
    }
    for (auto to : g[v]) {
        if (used[mt[to]] < timer && kuhn(mt[to], g, mt, used, timer)) {
            mt[to] = v;
            return true;
        }
    }
    return false;
}

void solve() {
    int l, r, m;
    cin >> l >> r >> m;
    vector<vector<int>> g(l);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
    }
    vector<int> mt(r, -1), used(l, -1);
    int timer = 0;
    for (int i = 0; i < l; i++) {
        if (used[i] < timer) {
            if (kuhn(i, g, mt, used, timer)) {
                timer++;
            }
        }
    }
    cout << timer << "\n";
    for (int v = 0; v < r; v++) {
        if (mt[v] != -1) {
            cout << mt[v] << " " << v << "\n";
        }
    }
}