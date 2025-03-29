class DSU {
public:
    int components;
    vector<int> parent, rank, sizes;

    DSU(int n) {
        parent.resize(n + 1);
        rank.resize(n + 1, 1);
        sizes.resize(n + 1, 1);
        for (int i = 0; i <= n; i++) {
            parent[i] = i;
        }
        components = n;
    }

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                parent[rootX] = rootY;
                sizes[rootY] += sizes[rootX];
            } else if (rank[rootX] > rank[rootY]) {
                parent[rootY] = rootX;
                sizes[rootX] += sizes[rootY];
            } else {
                parent[rootY] = rootX;
                rank[rootX]++;
                sizes[rootX] += sizes[rootY];
            }
            components--;
        }
    }
    
    int size(int x) {
        return sizes[find(x)];
    }

    bool same(int x, int y) {
        return find(x) == find(y);
    }
};