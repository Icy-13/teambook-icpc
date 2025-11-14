///condition:
///dp[i][j] = min(dp[i - 1][k] forall k < j)
///if opt[i][j] <= opt[i][j + 1] then ok
struct Getter {
    vector <int> cnt;
    int l = 1, r = 1;
    ll ans = 0;
    Getter() : cnt(2e6) {}
};

ll get (int cl, int cr, Getter &getter) {
    while (getter.l > cl) {
        getter.l--;
        getter.ans += getter.cnt[pref[getter.l] ^ d];
        getter.cnt[pref[getter.l]]++;
    }
    while (getter.l < cl) {
        getter.cnt[pref[getter.l]]--;
        getter.ans -= getter.cnt[pref[getter.l] ^ d];
        getter.l++;
    }
    while (getter.r < cr) {
        getter.ans += getter.cnt[pref[getter.r] ^ d];
        getter.cnt[pref[getter.r]]++;
        getter.r++;
    }
    while (getter.r > cr) {
        getter.r--;
        getter.cnt[pref[getter.r]]--;
        getter.ans -= getter.cnt[pref[getter.r] ^ d];
    }
    return getter.ans;
}

void divide(int level, int L, int R, int cl, int cr, Getter &getter) {
    if (L >= R) {
        return;
    }
    int M = (L + R) / 2;
    int opt = cl;
    for (int i = cl; i < min(M, cr); i++) {
        int x = get(i, M + 1, getter);
        if (dp[level][M] > dp[level - 1][i] + x) {
            dp[level][M] = dp[level - 1][i] + x;
            opt = i;
        }
    }
    divide(level, L, M, cl, opt + 1, getter);
    divide(level, M + 1, R, opt, cr, getter);
}

void solve() {
    cin >> n >> m >> d;
    dp.resize(m + 1, vector <ll> (n + 1));
    a.resize(n + 1);
    pref.resize(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pref[i] = pref[i - 1] ^ a[i];
    }
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;
    for (int i = 1; i <= m; i++) {
        Getter getter;
        divide(i, 0, n + 1, 0, n + 1, getter);
    }
    cout << dp[m][n] << endl;
}
