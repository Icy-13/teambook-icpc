// Transition can be rewritten as min/max on lines or as scalar product
// and k (as in y=kx+b) is monotonic
// in that problem: dp[i] = min(dp[j] + b[j] * a[i]), bx+dp is a line, a is a coef

ll calc_line(const pll& a, ll x) {
    return a.first * x + a.second;
}
 
ll calc_sect(const pll& a, const pll& b) {
    ll x = (b.second - a.second) / (a.first - b.first);
    return x;
}
 
void add(const pll& p, vector<pll>& hull, vector<ll>& sect) {
    while (!sect.empty()) {
        if (calc_sect(p, hull.back()) < sect.back() ) {
            hull.pop_back();
            sect.pop_back();
            continue;
        }
        break;
    }
    sect.push_back(calc_sect(p, hull.back()));
    hull.push_back(p);
}
 
ll get_min(ll x, vector<pll>& hull, vector<ll>& sect) {
    int id = lower_bound(all(sect), x) - sect.begin();
    return calc_line(hull[id], x);
}
 
void solve() {
    int n;
    cin >> n;
    vector<int> a(n), b(n);
    for (auto& i : a) cin >> i;
    for (auto& i : b) cin >> i;
    vector<ll> dp(n, 0);
    vector<pll> hull;
    vector<ll> sect;
    hull.emplace_back(b[0], dp[0]);
    for (int i = 1; i < n; i++) {
        dp[i] = get_min(a[i], hull, sect);
        add({b[i], dp[i]}, hull, sect);
    }
    dp.back() = get_min(a.back(), hull, sect);
    cout << dp.back() << "\n";
}