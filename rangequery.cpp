class RangeQueries {
  public :
    int *BITTree1, *BITTree2;  int n;
    
    RangeQueries(int n) {
        this->n = n;
        BITTree1 = constructBITree(n);
        BITTree2 = constructBITree(n);
    }
    
    int getSum(int BITree[], int index) {
        int sum = 0;
        index = index + 1;
        while (index > 0) {
            sum += BITree[index];
            index -= index & (-index);
        }
        return sum;
    }

    void updateBIT(int BITree[], int n, int index, int val) {
        index = index + 1;
        while (index <= n) {
            BITree[index] += val;
            index += index & (-index);
        }
    }

    int sum(int x, int BITTree1[], int BITTree2[]) {
        return (getSum(BITTree1, x) * x) - getSum(BITTree2, x);
    }
    
    void update(int l, int r, int val) {
        updateRange(BITTree1, BITTree2, n, val, l, r);
    }
    
    int query(int l, int r) {
        return rangeSum(l, r, BITTree1, BITTree2);
    }

    void updateRange(int BITTree1[], int BITTree2[], int n, int val, int l, int r) {
        updateBIT(BITTree1, n, l, val);
        updateBIT(BITTree1, n, r + 1, -val);
        updateBIT(BITTree2, n, l, val * (l - 1));
        updateBIT(BITTree2, n, r + 1, -val * r);
    }
    int rangeSum(int l, int r, int BITTree1[], int BITTree2[]) {
        return sum(r, BITTree1, BITTree2) - sum(l - 1, BITTree1, BITTree2);
    }
    int* constructBITree(int n) {
        int* BITree = new int[n + 1];
        for (int i = 1; i <= n; i++) BITree[i] = 0;
        return BITree;
    }
};

class FenwickTree2D {
public:
    vector<vector<int>> bit;
    int n, m;

    FenwickTree2D(int n, int m) {
        this->n = n;
        this->m = m;
        bit.assign(n + 1, vector<int>(m + 1, 0));
    }

    void update(int x, int y, int val) {
        for (; x <= n; x += (x & (-x))) {
            for (int i = y; i <= m; i += (i & (-i))) {
                bit[x][i] += val;
            }
        }
    }

    int query(int x1, int y1, int x2, int y2) {
        return query(x2, y2) - query(x2, y1 - 1) - query(x1 - 1, y2) + query(x1 - 1, y1 - 1);
    }

    int query(int x, int y) {
        int ans = 0;
        for (int i = x; i > 0; i -= (i & (-i))) {
            for (int j = y; j > 0; j -= (j & (-j))) {
                ans += bit[i][j];
            }
        }
        return ans;
    }
};

class Data {
public:
    int l;
    int r;
    int val;
    Data() {
        l = INT_MAX;
        r = -1;
        val = 0;
    }
};
 
class SegmentTree {
public:
    int n;
    vector<Data> tree;
    SegmentTree(const vector<int>& nums) {
        n = nums.size();
        tree.resize(2 * n);
        for (int i = 0; i < n; ++i) {
            tree[n + i].l = i + 1;
            tree[n + i].r = i + 1;
            tree[n + i].val = nums[i];
        }
        for (int i = n - 1; i > 0; --i) tree[i] = merge(tree[i << 1], tree[i << 1 | 1]);
    }
 
    Data merge(const Data &left, const Data &right) {
        Data res;
        res.l = min(left.l, right.l);
        res.r = max(left.r, right.r);
        res.val = left.val + right.val;
        return res;
    }
 
    Data query(int l, int r) {
        int L = (l - 1) + n;
        int R = r + n;
        Data resLeft, resRight;
        while (L < R) {
            if (L & 1) {
                resLeft = merge(resLeft, tree[L]);
                ++L;
            }
            if (R & 1) {
                --R;
                resRight = merge(tree[R], resRight);
            }
            L >>= 1;
            R >>= 1;
        }
        return merge(resLeft, resRight);
    }
 
    void update(int pos, int newVal) {
        int idx = (pos - 1) + n;
        tree[idx].val = newVal;
        for (idx /= 2; idx >= 1; idx /= 2)
            tree[idx] = merge(tree[idx << 1], tree[idx << 1 | 1]);
    }
};

class SegmentTree {
public:
    int n;
    vector<vector<int>> tree;

    void build(vector<int>& a, int x, int l, int r) {
        if (l + 1 == r) {
            tree[x] = {a[l]};
            return;
        }

        int m = (l + r) / 2;
        build(a, 2 * x + 1, l, m);
        build(a, 2 * x + 2, m, r);
        merge(tree[2 * x + 1].begin(), tree[2 * x + 1].end(),
              tree[2 * x + 2].begin(), tree[2 * x + 2].end(),
              back_inserter(tree[x]));
    }

    SegmentTree(vector<int>& a) : n(a.size()) {
        int SIZE = 1 << (__lg(n) + bool(__builtin_popcount(n) - 1));
        tree.resize(2 * SIZE - 1);
        build(a, 0, 0, n);
    }

    int query(int lq, int rq, int mn, int mx, int x, int l, int r) {
        if (rq <= l || r <= lq) return 0;
        if (lq <= l && r <= rq) 
            return lower_bound(tree[x].begin(), tree[x].end(), mx) -
                   lower_bound(tree[x].begin(), tree[x].end(), mn);

        int m = (l + r) / 2;
        int a = query(lq, rq, mn, mx, 2 * x + 1, l, m);
        int b = query(lq, rq, mn, mx, 2 * x + 2, m, r);
        return a + b;
    }

    int query(int lq, int rq, int mn, int mx) {
        rq++;
        return query(lq, rq, mn, mx, 0, 0, n);
    }

    void update(int index, int new_val, int x, int l, int r) {
        if (l + 1 == r) {
            tree[x] = {new_val};
            return;
        }

        int m = (l + r) / 2;
        if (index < m) {
            update(index, new_val, 2 * x + 1, l, m);
        } else {
            update(index, new_val, 2 * x + 2, m, r);
        }

        tree[x].clear();
        merge(tree[2 * x + 1].begin(), tree[2 * x + 1].end(),
              tree[2 * x + 2].begin(), tree[2 * x + 2].end(),
              back_inserter(tree[x]));
    }

    void update(int index, int new_val) {
        update(index, new_val, 0, 0, n);
    }
};
struct Data {
    int sum;
    int set;
    int increment;
    bool setAllValid;
    Data() {
       sum = 0;
       setAllValid = 0;
       increment = 0;
    }
    void Reset() {
       setAllValid = increment = 0;
    }
};
 
class SegmentTree {
    int range;
    vector<Data> tree;
public:
    SegmentTree(vector<int>& v) {
        range = v.size();
        tree.assign(4*range, Data());
        build_recur(v, 0, range-1, 0);
    }
    void build_recur(vector<int>& v, int l, int r, int node_no) {
        if(l == r){
            if(l < v.size()) tree[node_no].sum = v[l];
            else tree[node_no].sum = 0;
            return;
        }
        int mid = (l+r)/2;
        build_recur(v, l, mid, 2*node_no + 1);
        build_recur(v, mid + 1, r, 2*node_no + 2);
        tree[node_no].sum = tree[2*node_no + 1].sum + tree[2*node_no + 2].sum;
    }
    
    int query(int L, int R) {
        L--;
        R--;
        return range_query_recur(0, 0, range - 1, L, R);
    }
 
    void incUpdate_recur(int node, int l, int r, int& L, int& R, int& X) {
        if(r < L || R < l || l >= range)
            return;
        if(L <= l && R >= r) {
            tree[node].increment += X;
            return;
        }
        applyAggr(node,l,r);
        int mid = (l+r)/2;
        incUpdate_recur(2*node+1,l,mid,L,R,X);
        incUpdate_recur(2*node+2,mid+1,r,L,R,X);
        applyAggr(2*node+1, l, mid);
        applyAggr(2*node+2, mid+1, r);
        tree[node].sum = tree[2*node+1].sum + tree[2*node+2].sum;
    }
 
    void increment(int L, int R, int X) {
        L--;
        R--;
        incUpdate_recur(0,0,range-1,L,R,X);
    }
 
    void setUpdate_recur(int node, int l, int r, int& L, int& R, int& X) {
        if(r < L || R < l || l >= range)
            return;
        if(L <= l && R >= r) {
            tree[node].setAllValid = 1;
            tree[node].set = X;
            tree[node].increment = 0;
            return;
        }
        applyAggr(node,l,r);
        int mid = (l+r)/2;
        setUpdate_recur(2*node+1,l,mid,L,R,X);
        setUpdate_recur(2*node+2,mid+1,r,L,R,X);
        applyAggr(2*node+1, l, mid);
        applyAggr(2*node+2, mid+1, r);
        tree[node].sum = tree[2*node+1].sum + tree[2*node+2].sum;
    }
 
    void update(int L, int R, int X) {
        L--; R--;
        setUpdate_recur(0,0,range-1,L,R,X);
    }
 
    void compose(int par, int child) {
        if(tree[par].setAllValid){
            tree[child].setAllValid = 1;
            tree[child].set = tree[par].set;
            tree[child].increment = tree[par].increment;
        }
        else tree[child].increment += tree[par].increment;
    }
 
    void applyAggr(int node, int l, int r) {
        if(tree[node].setAllValid) tree[node].sum = (r-l+1)*tree[node].set;
 
        tree[node].sum += (r-l+1)*tree[node].increment;
 
        if(l != r){
            compose(node, 2*node + 1);
            compose(node, 2*node + 2);
        }
 
        tree[node].Reset();
    }
 
    int range_query_recur(int node, int l, int r, int& L, int& R) {
        if(r < L || R < l || l >= range)
            return 0;
        applyAggr(node, l, r);
        if(L <= l && R >= r)
            return tree[node].sum;
        int mid = (l+r)/2;
        return range_query_recur(2*node + 1, l, mid, L, R) + range_query_recur(2*node + 2, mid+1, r, L, R);
    }
};