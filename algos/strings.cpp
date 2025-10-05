template<typename T>
vector<int> pref_func(const T& s) {
    int n = s.size();
    vector<int> p(n, 0);
    p[0] = 0;
    for (int i = 1; i < n; i++) {
        int k = p[i - 1];
        while (k != 0 && s[k] != s[i]) {
            k = p[k - 1];
        }
        if (s[k] == s[i]) {
            k++;
        }
        p[i] = k;
    }
    return p;
}

template<typename T>
vector<int> z_func(const T& s) {
    int n = s.size();
    vector<int> z(n, 0);
    int l = 0, r = 0;
    for (int i = 1; i < n; i++) {
        z[i] = max(0, min(r - i + 1, z[i - l]));
        while (z[i] + i < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (z[i] + i - 1 > r) {
            r = z[i] + i - 1;
            l = i;
        }
    }
    return z;
}

template <typename T>
struct Hash {
    ull mod;
    ull base;
    vector<ull> power;
    vector<ull> hash;

    Hash(int mod, int base, int n) : mod(mod), base(base) {
        power.resize(n, 1);
        for (int i = 1; i < n; i++) {
            power[i] = (power[i - 1] * base) % mod;
        }
    }

    Hash(int mod, int base, const T& s) : Hash(mod, base, s.size() + 1) {
        hash.resize(s.size() + 1);
        for (int i = 0; i < s.size(); i++) {
            hash[i + 1] = (hash[i] * base + s[i]) % mod;
        }
    }

    Hash(const T& s) : Hash(1e9 + 7, 199, s) {}

    ull get_substr(int l, int r) {
        return (hash[r + 1] - hash[l] * power[r - l + 1] % mod + mod) % mod;
    }

    bool compare(int l1, int r1, int l2, int r2) {
        return get_substr(l1, r1) == get_substr(l2, r2);
    }
};

template<typename T>
struct BigHash {
    Hash<T> h1, h2;

    BigHash(const T& s) {
        h1 = {(int)1e9 + 7, 37, s};
        h2 = {998'353'244, 61, s};
    }

    pair<ull, ull> get_substr(int l, int r) {
        return std::make_pair(
            h1.get_substr(l, r),
            h2.get_substr(l, r));
    }

    bool compare(int l1, int r1, int l2, int r2) {
        return h1.compare(l1, r1, l2, r2) &&
               h2.compare(l1, r1, l2, r2);
    }
};

vector<int> manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 0, r = 1;
    for (int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while (s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if (i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<int> manacher(string s) {
    string t;
    for (auto c : s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    return vector<int>(begin(res) + 1, end(res) - 1);
}

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