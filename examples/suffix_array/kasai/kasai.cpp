#include <bits/stdc++.h>
// #pragma comment(linker, "/STACK:16777216")
// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,sse4,fma,bmi,bmi2,popcnt,lzcnt,abm")

using namespace std;

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using dbl = double;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using pdd = pair<dbl, dbl>;
using pld = pair<ld, ld>;

// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>
// using namespace __gnu_pbds;
// typedef tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;

#define ft first
#define sc second
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()

template<typename T>
vector<int> calc_lcp(const T& s, const vector<int>& suffar) {
    int n = s.size();
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        c[suffar[i]] = i;
    }
    vector<int> lcp(n - 1);
    int cur_lcp = 0;
    for (int i = 0; i < n; i++) {
        if (c[i] == n - 1) {
            cur_lcp = 0;
            continue;
        }
        int j = suffar[c[i] + 1];
        while (i + cur_lcp < n && j + cur_lcp < n && s[i + cur_lcp] == s[j + cur_lcp]) {
            cur_lcp++;
        }
        lcp[c[i]] = cur_lcp;
        cur_lcp = std::max(cur_lcp - 1, 0);
    }
    return lcp;
}

template<typename T>
void print(const vector<T>& vec, bool newline = false) {
    for (const auto& x : vec) {
        cout << x << " \n"[newline];
    }
    if (!newline) {
        cout << "\n";
    }
}

void solve() {
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<int> suffar(n);
    for (auto& i : suffar) {
        cin >> i; --i;
    }
    auto lcp = calc_lcp(s, suffar);
    print(lcp, true);
}

signed main() {
    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // std::freopen("", "r", stdin);
    // std::freopen("", "w", stdout);

    int t = 1;
    // cin >> t;
    while (t--) solve();
    return 0;
}
