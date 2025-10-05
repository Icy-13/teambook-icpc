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

namespace utils {
template <typename T>
concept Iterable = requires(T t) {
    std::begin(t);
    std::end(t);
};
}  // namespace utils

namespace printer {

template <typename T>
concept Printable = requires(ostream& os, T t) {
    { os << t };
};

template <typename T>
constexpr bool is_iterable_v = utils::Iterable<T> && !std::same_as<T, std::string>;

template <typename T>
struct container_traits {
    using Elem = std::remove_cvref_t<decltype(*std::begin(std::declval<T>()))>;
};

template <Printable T>
void print_impl(const T& elem, bool newline);

template <utils::Iterable T>
    requires(!Printable<T>)
void print_impl(const T& vec, bool newline);

template <typename T, typename U>
void print_impl(const std::pair<T, U>& pair, bool newline);

template <typename... Ts>
void print_all_impl(bool newline, const Ts&... args);

template <typename... Ts>
void print_all_impl(bool newline, const Ts&... args) {
    (print_impl(args, newline), ...);
    if (!newline) {
        cout << "\n";
    }
}

template <Printable T>
void print_impl(const T& elem, bool newline) {
    cout << elem << " \n"[newline];
}

template <utils::Iterable T>
    requires(!Printable<T>)
void print_impl(const T& container, bool newline) {
    using Elem = typename container_traits<T>::Elem;
    constexpr bool inner_is_container = is_iterable_v<Elem>;
    for (const auto& x : container) {
        // additional_newline &= !container<x>
        print_impl(x, newline);
    }
    if (!newline && !inner_is_container) {
        cout << "\n";
    }
}

template <typename T, typename U>
void print_impl(const std::pair<T, U>& pair, bool newline) {
    print_impl(pair.first, newline);
    print_impl(pair.second, newline);
    if (!newline) {
        cout << "\n";
    }
}

template <typename T>
void print(const T& x, bool newline = false) {
    printer::print_impl(x, newline);
}

template <typename... Ts>
void print(const Ts&... args) {
    printer::print_all_impl(false, args...);
}

}  // namespace printer

using printer::print;

namespace reader {
template <typename T>
concept Readable = requires(istream& is, T t) {
    { is >> t };
};

template <Readable T>
void read(T& elem);

template <utils::Iterable T>
    requires(!Readable<T>)
void read(T& container);

template <Readable T>
void read(T& elem) {
    cin >> elem;
}

template <utils::Iterable T>
    requires(!Readable<T>)
void read(T& container) {
    for (auto& i : container) {
        read(i);
    }
}

template <typename... T>
void read(T&... elems) {
    (read(elems), ...);
}

}  // namespace reader
using reader::read;

void solve() {

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
