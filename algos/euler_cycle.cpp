struct edge {
    int vertex_to;
    int edge_num;
};

//returns sequence of vertices representing euler path
vector <int> euler_cycle(int start, int finish, vector <vector <edge> > &g, int edges_num, int n) {
    vector <bool> used(edges_num);
    vector <int> path, vec;
    vector <int> it(n);
    vec.push_back(start);
    while (!vec.empty()) {
        int cur = vec.back();
        while (it[cur] < g[cur].size()) {
            edge to = g[cur][it[cur]];
            if (!used[to.edge_num]) break;
            else it[cur]++;
        }
        if (it[cur] >= g[cur].size()) {
            path.push_back(cur);
            vec.pop_back();
        } else {
            edge to = g[cur][it[cur]];
            vec.push_back(to.vertex_to);
            used[to.edge_num] = 1;
        }
    }
    reverse(path.begin(), path.end());
    return path;
}