class SparseTable {
public:
    vector<vector<int>> table;
    vector<int> logTable;
    vector<int> arr;

    SparseTable(const vector<int>& arr) : arr(arr) {
        int n = arr.size();
        int logN = (int) (log2(n)) + 1;
        table.resize(n, vector<int>(logN));
        logTable.resize(n + 1);
        buildSparseTable();
    }

    void buildSparseTable() {
        int n = arr.size();
        for (int i = 2; i <= n; i++) {
            logTable[i] = logTable[i / 2] + 1;
        }

        for (int i = 0; i < n; i++) {
            table[i][0] = arr[i];
        }

        for (int j = 1; (1 << j) <= n; j++) {
            for (int i = 0; i + (1 << j) <= n; i++) {
                int leftVal = table[i][j - 1];
                int rightVal = table[i + (1 << (j - 1))][j - 1];
                table[i][j] = max(leftVal, rightVal);
            }
        }
    }

    int query(int l, int r) {
        int k = logTable[r - l + 1];
        int leftVal = table[l][k];
        int rightVal = table[r - (1 << k) + 1][k];
        return max(leftVal, rightVal);
    }
};