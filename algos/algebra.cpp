int gcd(int a, int b, int& x, int& y) {
    x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}
const int N = 10000000;
vector<int> lp(N + 1), pr;

void linear_sieve() {
    for (int i = 2; i <= N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int j = 0; i * pr[j] <= N; ++j) {
            lp[i * pr[j]] = pr[j];
            if (pr[j] == lp[i]) break;
        }
    }
}

vector<int> phi(N + 1);
void phi_precalc() {
    for (int i = 0; i <= N; i++) phi[i] = i;
    for (int i = 2; i <= N; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= N; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}

// Miller-Rabin primality test, O((log n) * bases)
bool check_composite(uint64_t n, uint64_t a, uint64_t d, int s) {
    uint64_t x = binpower(a, d, n);  // int128 required
    if (x == 1 || x == n - 1) return false;
    for (int r = 1; r < s; r++) {
        x = (__uint128_t)x * x % n;
        if (x == n - 1) return false;
    }
    return true;
};

bool MillerRabin(uint64_t n) {  // returns true if n is prime, else returns false.
    if (n < 2) return false;
    int r = 0;
    uint64_t d = n - 1;
    while ((d & 1) == 0) {
        d >>= 1;
        r++;
    }
    for (int a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {  // only 2,3,5,7 for 32-bit
        if (n == a) return true;
        // a = 2 + rand() % (n-3)
        if (check_composite(n, a, d, r)) return false;
    }
    return true;
}

// NTT
const int mod = 998244353;     // mod = c*2^k + 1, mod is prime
const int root = 31;           // => g^c - 2^k root of unity, g is a primitive root
const int root_1 = 128805723;  // inverse of root modulo mod
const int root_pw = 1 << 23;   // 2^k from (mod = c*2^k + 1)

int inverse(int n, int mod) {
    long long result = 1;
    long long base = n % mod;
    int p = mod - 2;
    while (p) {
        if (p & 1) result = result * base % mod;
        base = base * base % mod;
        p >>= 1;
    }
    return (int)result;
}

void ntt(vector<int>& a, bool invert) {
    int n = a.size();
    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;  // mask can be precomputed
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        int wlen = invert ? root_1 : root;
        for (int i = len; i < root_pw; i <<= 1) wlen = (int)(1LL * wlen * wlen % mod);
        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; j++) {
                int u = a[i + j], v = (int)(1LL * a[i + j + len / 2] * w % mod);
                a[i + j] = u + v < mod ? u + v : u + v - mod;
                a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + mod;
                w = (int)(1LL * w * wlen % mod);
            }
        }
    }
    if (invert) {
        int n_1 = inverse(n, mod);  // modulo inverse of n, can be precomputed
        for (int& x : a) x = (int)(1LL * x * n_1 % mod);
    }
}

vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);
    ntt(fa, false);
    ntt(fb, false);
    for (int i = 0; i < n; i++) fa[i] = fa[i] * 1LL * fb[i] % mod;
    ntt(fa, true);
    return fa;
}

// CRT
struct Congruence {
    long long a, m; // x = a (mod m)
};

long long chinese_remainder_theorem(vector<Congruence> const& congruences) {
    // mods are coprime. Otherwise we either have one solution modulo lcm, or we don't have any
    // transofrm (a, m) congruence to (a, p1^n1) .. (a, pm^nm) congr, where p's are prime
    // if we have a contradiction, i.e. (1, 4) and (1, 2), then there's no sol, otherwise use default algo
    long long M = 1;
    for (auto const& congruence : congruences) {
        M *= congruence.m;
    }

    long long solution = 0;
    for (auto const& congruence : congruences) {
        long long a_i = congruence.a;
        long long M_i = M / congruence.m;
        long long N_i = mod_inv(M_i, congruence.m);
        solution = (solution + a_i * M_i % M * N_i) % M;
    }
    return solution;
}
