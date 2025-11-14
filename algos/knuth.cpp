///dp[i][j] = min(dp[i][k] + dp[k + 1][j]) forall i <= k < j
///opt[i][j - 1] <= opt[i][j] <= opt[i + 1][j]
///order-preserving prefix code problem
void solve(){
    int n;
    cin >> n;
    vector <int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector <int> pref(n + 1);
    for (int i = 0; i < n; i++) {
        pref[i + 1] = pref[i] + a[i];
    }
    vector <vector <int> > dp(n, vector <int> (n, INF));
    vector <vector <int> > opt(n, vector <int> (n));
    for (int i = 0; i < n; i++) {
        dp[i][i] = 0;
        opt[i][i] = i;
    }
    for (int i = n - 2; i >= 0; i--) {
        for (int j = i + 1; j < n; j++) {
            for (int k = opt[i][j - 1]; k <= min(opt[i + 1][j], j - 1); k++) {
                int value = dp[i][k] + dp[k + 1][j] + pref[j + 1] - pref[i];
                if (value < dp[i][j]) {
                    dp[i][j] = value;
                    opt[i][j] = k;
                }
            }
        }
    }
}
