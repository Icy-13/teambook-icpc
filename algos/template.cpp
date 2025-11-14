#include <bits/stdc++.h>
// #pragma comment(linker, "/STACK:16777216")
// #pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx2,sse4.2,fma,bmi,bmi2,lzcnt,popcnt,tune=skylake")

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;
typedef tree<int, null_type, less_equal<>, rb_tree_tag, tree_order_statistics_node_update> ordered_multiset;
// in ordered_multiset lower and upper bounds are swapped and erase by value doesn't work