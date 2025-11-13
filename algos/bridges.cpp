void dfs(int v, int p_edge, int d) {
    used[v] = true;
    depth[v] = up[v] = d;
    int children = 0;
    for (auto [to, id] : g[v]) {
        if (id == p_edge) continue; // for multi-edge case
        if (used[to]) {
            up[v] = min(up[v], depth[to]);
        } else {
            dfs(to, id, d + 1);
            up[v] = min(up[v], up[to]);
            if (depth[v] < up[to]) {
                bridges.emplace(id);
            }
            if (depth[v] <= up[to] && p_edge != -1) {
                cutpoints.emplace(v);
            }
            children++;
        }
    }
    if (p_edge == -1 && children > 1) {
        cutpoints.emplace(v);
    }
}