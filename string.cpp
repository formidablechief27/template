struct Hashing {
    string s;
    int n;
    int primes;
    vector<int> hashPrimes = {1000000009, 100000007};
    const int base = 31;
    vector<vector<int>> hashValues;
    vector<vector<int>> powersOfBase;
    vector<vector<int>> inversePowersOfBase;

    Hashing(string a) {
    reverse(a.begin(), a.end());
        primes = hashPrimes.size();
        hashValues.resize(primes);
        powersOfBase.resize(primes);
        inversePowersOfBase.resize(primes);
        s = a;
        n = s.length();

        for (int i = 0; i < primes; i++) {
            int mod = hashPrimes[i];
            powersOfBase[i].resize(n + 1);
            inversePowersOfBase[i].resize(n + 1);
            powersOfBase[i][0] = 1;
            for (int j = 1; j <= n; j++) {
                powersOfBase[i][j] = mul(base, powersOfBase[i][j - 1], mod);
            }
            inversePowersOfBase[i][n] = inv(powersOfBase[i][n], mod);
            for (int j = n - 1; j >= 0; j--) {
                inversePowersOfBase[i][j] = mul(inversePowersOfBase[i][j + 1], base, mod);
            }
        }

        for (int i = 0; i < primes; i++) {
            int mod = hashPrimes[i];
            hashValues[i].resize(n);
            for (int j = 0; j < n; j++) {
                int currentHash = mul((s[j] - 'a' + 1), powersOfBase[i][j], mod);
                hashValues[i][j] = add(currentHash, j > 0 ? hashValues[i][j - 1] : 0, mod);
            }
        }
    }

    vector<int> query(int l, int r) {
    int p1 = n - r - 1;
    int p2 = n - l - 1;
    l = p1;  r = p2;
        vector<int> hash(primes);
        for (int i = 0; i < primes; i++) {
            int mod = hashPrimes[i];
            int val1 = hashValues[i][r];
            int val2 = l > 0 ? hashValues[i][l - 1] : 0;
            hash[i] = mul(sub(val1, val2, mod), inversePowersOfBase[i][l], mod);
        }
        return hash;
    }
};

this->pows1.resize(n + 5);
pows1[0] = 1;
for(int i=1;i<=n;i++) pows1[i] = mul(31, pows1[i - 1]);
this->pows2.resize(n + 5);
mod = 1e9 + 9;
pows2[0] = 1;
for(int i=1;i<=n;i++) pows2[i] = mul(31, pows2[i - 1]);


    int find(int m, int a, int b, int c) {
        int p = mod;
        mod = m;
        return add(mul(a, b), c);
        mod = p;
    }
    
    Data merge(const Data &node1, const Data &node2) {
        Data data;
        data.l = min(node1.l, node2.l);
        data.r = max(node1.r, node2.r);
        bool valid1 = node1.r != -1;
        bool valid2 = node2.r != -1;
        if(valid1 && valid2) {
            int length = node2.r - node2.l + 1;
            data.val1 = find(1e9 + 7, node1.val1, pows1[length], node2.val1);
            data.val2 = find(1e9 + 9, node1.val2, pows2[length], node2.val2);
        }
        else if(valid1) {
            data.val1 = node1.val1;
            data.val2 = node1.val2;
        }
        else if(valid2) {
            data.val1 = node2.val1;
            data.val2 = node2.val2;
        }
        return data;
    }

void update(int index, char ch) {
        int value = (int)(ch - 'a') + 1;
        update(1, 0, n - 1, index - 1, value);
    }

vector<int> suffix_array(string S) {
    int N = S.size();
    vector<int> sa(N), classes(N);
    for (int i = 0; i < N; i++) {
        sa[i] = N - 1 - i;
        classes[i] = S[i];
    }
    stable_sort(sa.begin(), sa.end(), [&S](int i, int j) {
        return S[i] < S[j];
    });
    for (int len = 1; len < N; len *= 2) {
        vector<int> c(classes);
        for (int i = 0; i < N; i++) {
            bool same = i && sa[i - 1] + len < N
                          && c[sa[i]] == c[sa[i - 1]]
                          && c[sa[i] + len / 2] == c[sa[i - 1] + len / 2];
            classes[sa[i]] = same ? classes[sa[i - 1]] : i;
        }
        vector<int> cnt(N), s(sa);
        for (int i = 0; i < N; i++)
            cnt[i] = i;
        for (int i = 0; i < N; i++) {
            int s1 = s[i] - len;
            if (s1 >= 0) sa[cnt[classes[s1]]++] = s1;
        }
    }
    return sa;
}
vector<int> lcp_array(const vector<int>& sa, string S) {
    int N = S.size();
    vector<int> rank(N), lcp(N - 1);
    for (int i = 0; i < N; i++)
        rank[sa[i]] = i;

    int pre = 0;
    for (int i = 0; i < N; i++) {
        if (rank[i] < N - 1) {
            int j = sa[rank[i] + 1];
            while (max(i, j) + pre < S.size() && S[i + pre] == S[j + pre])
                ++pre;
            lcp[rank[i]] = pre;
            if (pre > 0)
                --pre;
        }
    }
    return lcp;
}

vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

vector<int> z_function(string &s) {
    int n = s.size();
    vector<int> z(n);
    int l = 0, r = 0;
    for(int i = 1; i < n; i++) {
        if(i < r) {
            z[i] = min(r - i, z[i - l]);
        }
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if(i + z[i] > r) {
            l = i;
            r = i + z[i];
        }
    }
    return z;
}

class Data {
public:
    int l;
    int r;
    int val1;
    int val2;
    Data() {
        l = INT_MAX;
        r = -1;
        val1 = 0;
        val2 = 0;
    }
};
 
class SegmentTree {
public:
    vector<Data> tree;
    vector<int> nums;
    int n;
    vector<int> pows1, pows2;
 
public:
    SegmentTree(string &s) {
        this->n = s.size();
        this->nums.resize(n);
        for(int i=0;i<n;i++) nums[i] = (int)(s[i] - 'a') + 1;
        this->tree.resize(4 * n);
        this->pows1.resize(n + 5);
        int p = mod;
        mod = 1e9 + 7;
        pows1[0] = 1;
        for(int i=1;i<=n;i++) pows1[i] = mul(31, pows1[i - 1]);
        this->pows2.resize(n + 5);
        mod = 1e9 + 9;
        pows2[0] = 1;
        for(int i=1;i<=n;i++) pows2[i] = mul(31, pows2[i - 1]);
        mod = p;
        buildTree(1, 0, n - 1);
    }
    
    int find(int m, int a, int b, int c) {
        int p = mod;
        mod = m;
        return add(mul(a, b), c);
        mod = p;
    }
    
    Data merge(const Data &node1, const Data &node2) {
        Data data;
        data.l = min(node1.l, node2.l);
        data.r = max(node1.r, node2.r);
        bool valid1 = node1.r != -1;
        bool valid2 = node2.r != -1;
        if(valid1 && valid2) {
            int length = node2.r - node2.l + 1;
            data.val1 = find(1e9 + 7, node1.val1, pows1[length], node2.val1);
            data.val2 = find(1e9 + 9, node1.val2, pows2[length], node2.val2);
        }
        else if(valid1) {
            data.val1 = node1.val1;
            data.val2 = node1.val2;
        }
        else if(valid2) {
            data.val1 = node2.val1;
            data.val2 = node2.val2;
        }
        return data;
    }
 
    void buildTree(int node, int start, int end) {
        if (start == end) {
            tree[node].l = start;
            tree[node].r = end;
            tree[node].val1 = nums[start];
            tree[node].val2 = nums[start];
        }
        else {
            int mid = (start + end) / 2;
            buildTree(2 * node, start, mid);
            buildTree(2 * node + 1, mid + 1, end);
            tree[node] = merge(tree[2 * node] , tree[2 * node + 1]);
        }
    }
 
    Data query(int left, int right) {
        return query(1, 0, n - 1, left - 1, right - 1);
    }
 
    Data query(int node, int start, int end, int left, int right) {
        if (right < start || left > end)
            return Data();
        else if (left <= start && right >= end)
            return tree[node];
        else
            return merge(query(2 * node, start, (start + end) / 2, left, right) ,
                   query(2 * node + 1, ((start + end) / 2) + 1, end, left, right));
    }
 
    void update(int index, char ch) {
        int value = (int)(ch - 'a') + 1;
        update(1, 0, n - 1, index - 1, value);
    }
 
    void update(int node, int start, int end, int index, int value) {
        if (start == end) {
            nums[index] = value;
            tree[node].val1 = value;
            tree[node].val2 = value;
        } else {
            int mid = (start + end) / 2;
            if (index >= start && index <= mid)
                update(2 * node, start, mid, index, value);
            else
                update(2 * node + 1, mid + 1, end, index, value);
            tree[node] = merge(tree[2 * node] , tree[2 * node + 1]);
        }
    }
};