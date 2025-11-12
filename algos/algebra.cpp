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
