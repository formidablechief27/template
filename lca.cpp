int n;
int m = 21;
int dep[200005] = {0};
int par[200005][21];
int dist[200005] = {0};
vector<vector<int>> tree(200005);
map<pair<int, int>, int> mp;

void dfs(int source, int parent) {
    dep[source] = dep[parent] + 1;
    par[source][0] = parent;
    for(int j=1;j < m;j++) par[source][j] = par[par[source][j - 1]][j - 1];
    for(int ele : tree[source]) {
        if(ele != parent) {
            dist[ele] = dist[source] + mp[{source, ele}];
            dfs(ele, source);
        }
    }
}

int LCA(int u, int v) {
    if (u == v) return u;
    if (dep[u] < dep[v]) swap(u, v);
    int diff = dep[u] - dep[v];
    for (int j = m - 1; j >= 0; j--) {
        if ((diff >> j) & 1) u = par[u][j];
    }
    for (int j = m - 1; j >= 0; j--) {
        if (par[u][j] != par[v][j]) {
            u = par[u][j];
            v = par[v][j];
        }
    }
    return (u != v ? par[u][0] : u);
}

int kthParent(int x, int k) {
    for (int j = 0; j < m; j++) {
        if ((k >> j) & 1) { 
            x = par[x][j];   
            if (x == -1) break;
        }
    }
    return x;
}

void solve() {
    dfs(1, 0);
    int u, v;
    cin >> u >> v;
    int lca = LCA(u, v);
    cout << dist[u] + dist[v] - 2 * dist[lca] << "\n";
    int a, b, c;
    cin >> a >> b >> c;
    cout << kthParent(b, c) << "\n";
    int lca = LCA(a, b);
}

vector<int> tree[N];
int n, q;
SegmentTree* root[N];
vector<int> chain[N];
int sz[N], H[N], P[N], chainIdx[N], pos[N];
 
void dfs(int source, int parent, int depth) {
    P[source] = parent;
    H[source] = depth;
    sz[source] = 1;
    for (int ele : tree[source]) {
        if (ele != parent) {
            dfs(ele, source, depth + 1);
            sz[source] += sz[ele];
        }
    }
}
 
void init(int n) {
    chain[n].push_back(n);
    for (int i = 0; i < chain[n].size(); i++) {
        int v = chain[n][i];
        chainIdx[v] = n;
        pos[v] = i;
        for (int j : tree[v]) {
            if (j != P[v]) 2 * sz[j] >= sz[v] ? chain[n].push_back(j) : init(j);
        }
    }
    vector<int> values(chain[n].size(), 0);
    root[n] = new SegmentTree(values);
}
 
int query(int u, int v) {
    int ans = 0;
    while (chainIdx[u] != chainIdx[v]) {
        if (H[chainIdx[u]] > H[chainIdx[v]]) swap(u, v);
        ans = max(ans, root[chainIdx[v]]->query(1, pos[v] + 1));
        v = P[chainIdx[v]];
    }
 
    if (pos[u] > pos[v]) swap(u, v);
    ans = max(ans, root[chainIdx[u]]->query(1 + pos[u], 1 + pos[v]));
    return ans;
}
 
void update(int u, int x) {root[chainIdx[u]]->update(1 + pos[u], x);}
 
 
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n >> q;
 
    int val[n];
    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }
 
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
 
    dfs(0, 0, 0);
    init(0);
 
    for (int i = 0; i < n; i++) update(i, val[i]);
 
    for (int i = 0; i < q; i++) {
        int type;
        cin >> type;
        if (type == 1) {
            int u, x;
            cin >> u >> x;
            u--;
            update(u, x);
        } else {
            int u, v;
            cin >> u >> v;
            cout << query(u - 1, v - 1) << "\n";
        }
    }
}

#include <bits/stdc++.h>

const int N = 1e5 + 1;

// adj_t is the transpose of adj
std::vector<int> adj[N], adj_t[N];
std::vector<int> order;
std::vector<int> vis(N), id(N);

// calculates the order in which nodes are processed
void dfs1(int v) {
    vis[v] = true;
    for (int u : adj[v]) {
        if (!vis[u]) { dfs1(u); }
    }
    order.push_back(v);
}

/*
 * traverse one SCC at a time and
 * assign component ID to all nodes in one SCC
 */
void dfs2(int x, int comp) {
    vis[x] = true;

    for (int u : adj_t[x]) {
        if (!vis[u]) { dfs2(u, comp); }
    }
    id[x] = comp;
}

int main() {
    int n, m;
    std::cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        int u, v;
        std::cin >> u >> v;
        adj[u].push_back(v);
        adj_t[v].push_back(u);
    }

    vis.assign(N, false);

    for (int i = 1; i <= n; i++) {
        if (!vis[i]) { dfs1(i); }
    }

    vis.assign(N, false);
    std::reverse(begin(order), end(order));
    int comps = 0;
    for (int v : order) {
        if (!vis[v]) {
            comps++;  // counter for SCC
            dfs2(v, comps);
        }
    }

    std::cout << comps << '\n';

    for (int i = 1; i <= n; i++) { std::cout << id[i] << " \n"[i == n]; }
}
