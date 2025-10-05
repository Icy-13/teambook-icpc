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
vector<int> suffix_array(const T& s) {
    // it's expected that s already has delimeter in the end
    int n = s.size();
    vector<int> cls(n), p(n);
    map<int, vector<int>> mp;
    for (int i = 0; i < n; i++) {
        mp[s[i]].push_back(i);
    }
    int cur_cls_counter = 0;
    int p_it = 0;
    for (const auto& [_, row] : mp) {
        for (const auto& v : row) {
            cls[v] = cur_cls_counter;
            p[p_it++] = v;
        }
        cur_cls_counter++;
    }

    vector<int> next_cls(n);
    vector<vector<int>> cnt(cur_cls_counter);
    cnt.reserve(n);
    for (int l = 1; cur_cls_counter < n; l++) {
        int d = (1 << l) >> 1;
        p_it = 0;
        int next_cls_counter = 0;

        for (int i = 0; i < n; i++) {
            int k = (p[i] - d + n) % n;
            cnt[cls[k]].push_back(k);
        }

        for (int i = 0; i < cur_cls_counter; i++) {
            for (int j = 0; j < cnt[i].size(); j++) {
                if (j == 0 || cls[(cnt[i][j] + d) % n] != cls[(cnt[i][j - 1] + d) % n]) {
                    next_cls_counter++;
                }
                next_cls[cnt[i][j]] = next_cls_counter - 1;
                p[p_it++] = cnt[i][j];
            }
        }
        cls.swap(next_cls);
        for (int i = 0; i < cur_cls_counter; i++) {
            cnt[i].clear();
        }
        cur_cls_counter = next_cls_counter;
        cnt.resize(cur_cls_counter);
    }
    p.erase(p.begin());
    return p;
}

template<typename T>
void print(const vector<T>& vec) {
    for (const auto& x : vec) {
        cout << x << " ";
    }
    cout << "\n";
}

void solve() {
    string s;
    cin >> s;
    s += '$';
    auto suffar = suffix_array(s);
    print(suffar);
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
