#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace __gnu_pbds;
using namespace std;
template<class T>
using pbds = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

#define init(a, val) memset(a, val, sizeof(a))
int mod = (int)1e9 + 7;
inline int add(int a, int b) { return (((a + mod) % mod) + ((b + mod) % mod)) % mod; }
inline int sub(int a, int b) { return (((a + mod) % mod) + ((-b + mod) % mod)) % mod; }
inline int mul(int a, int b) { return ((a % mod) * (b % mod)) % mod; }
inline int binpow(int a, int b) {
    a %= mod;
    int res = 1;
    while (b > 0) {
        if (b & 1) 
            res = mul(res, a);
        a = mul(a, a);
        b /= 2;
    }
    return res;
}
inline int inv(int x) { return binpow(x, mod - 2); }
inline int divi(int x, int y) { return mul(x, inv(y)); }
inline int gcd(int a, int b) { return __gcd(a, b); }
inline int lcm(int a, int b) { return (a * b) / __gcd(a, b); }
inline int ceil(int a, int b) { return (a + b - 1) / b; }
inline bool isSet(int x, int bit) { return ((x >> bit) & 1LL) == 1LL; }

int a = sqrtl(num); double d = log2(num);

ios::sync_with_stdio(false);
cin.tie(nullptr);

cout << setprecision(10);

order_of_key (k) : Number of items strictly smaller than k .
find_by_order(k) : K-th element in a set (counting from zero).

int query(pbds<pair<int, int>> &st, int l, int r) {
    int ans = st.order_of_key({r, inf});
    ans -= st.order_of_key({l - 1, inf});
    return ans;
}