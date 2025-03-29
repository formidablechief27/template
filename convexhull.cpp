struct DP {
    struct Line {
        int slope, yIntercept;
        Line(int slope, int yIntercept) : slope(slope), yIntercept(yIntercept) {}
        int val(int x) {
            return slope * x + yIntercept;
        }
        int intersect(Line y) {
            if(slope == y.slope) return inf;
            return (y.yIntercept - yIntercept + slope - y.slope - 1) / (slope - y.slope);
        }
    };
 
    deque<pair<Line, int>> dq;
 
    void insert(int slope, int yIntercept) {
        Line newLine(slope, yIntercept);
        while (dq.size() > 1 && dq.back().second >= dq.back().first.intersect(newLine)) dq.pop_back();
        if (dq.empty()) {
            dq.emplace_back(newLine, 0);
            return;
        }
        dq.emplace_back(newLine, dq.back().first.intersect(newLine));
    }
 
    int query(int x) {
        while (dq.size() > 1) {
            if (dq[1].second <= x) dq.pop_front();
            else break;
        }
        return dq[0].first.val(x);
    }
 
    int query2(int x) {
        auto qry = *lower_bound(dq.rbegin(), dq.rend(),
                                make_pair(Line(0, 0), x),
                                [&](const pair<Line, int> &a, const pair<Line, int> &b) {
                                    return a.second > b.second;
                                });
        return qry.first.val(x);
    }
};


int dp[15][2][15];

int solve(string &num, int index, bool tight, int cnt) {
    if (index == num.size() || num == "0") return cnt;
    if(dp[index][tight][cnt] != -1) return dp[index][tight][cnt];
    char start = '0';
    char end = tight ? num[index] : '9';
    int ans = 0;
    for (char ch = start; ch <= end; ch++) {
        int new_cnt = cnt + (ch == '1' ? 1 : 0);
        bool new_tight = tight && (ch == end);
        ans += solve(num, index + 1, new_tight, new_cnt);
    }
    return dp[index][tight][cnt] = ans;
}

void solve(int test) {
    int l, r;
    cin >> l >> r;
    string num1 = to_string(l - 1), num2 = to_string(r);
    init(dp, -1);
    int ans1 = solve(num2, 0, true, 0);
    init(dp, -1);
    int ans2 = solve(num1, 0, true, 0);
    cout << ans1 - ans2 << endl;
}