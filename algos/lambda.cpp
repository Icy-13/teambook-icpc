ll subsolve(vector<int>& a, vector<int>& b, int p, int k, int from, int to) {
    ll ans = 0;
    k -= (p - from) + (to - from - 1) + (to - p - 1);
    if (k <= 0) {
        return 0;
    }
    int l = 0, r = 1e9 + 1;
    while (r - l > 1) {
        ll total = 0;
        int m = (l + r) / 2;
        for (int i = from; i < to; ++i) {
            if (a[i] - m < 0) {
                continue;
            }
            total += (a[i] - m) / b[i] + 1;
        }

        if (total >= k) {
            l = m;
        } else {
            r = m;
        }
    }
    ll total = 0;
    for (int i = from; i < to; ++i) {
        if (a[i] - l < 0) {
            continue;
        }
        total += (a[i] - l) / b[i] + 1;
    }
    for (int i = from ; i < to; ++i) {
        if (a[i] - l < 0) {
            continue;
        }
        ll n = (a[i] - l) / b[i];
        ans += (2 * a[i] - n * b[i]) * (n + 1) / 2;
    }
    return ans - (total - k) * l;
}

void solve() {
    int n, p, k;
    cin >> n >> p >> k;
    --p;
    vector<int> a(n), b(n);
    for (int& i : a) cin >> i;
    for (int& i : b) cin >> i;

    ll ans = 0;
    for (int i = 0; i <= p; ++i) {
        for (int j = p + 1; j <= n; ++j) {
            ans = max(ans, subsolve(a, b, p, k, i, j));
        }
    }

    cout << ans << endl;
}
