vector<int> euler_cycle(int start, vector<vector<pii>> &g, int m) {
    vector<bool> used(m);
    vector<int> it(g.size()), path, vec = {start};
    while (!vec.empty()) {
        int cur = vec.back();
        while (it[cur] < g[cur].size()) {
            if (!used[g[cur][it[cur]].second]) break;
            it[cur]++;
        }
        if (it[cur] >= g[cur].size()) {
            path.push_back(cur);
            vec.pop_back();
        } else {
            vec.push_back(g[cur][it[cur]].first);
            used[g[cur][it[cur]].second] = 1;
        }
    }
    reverse(all(path));
    return path;
}