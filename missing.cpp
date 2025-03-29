class MissingSet {
public:
    map<int, int> interval;
    unordered_map<int, int, chash> fmap;
    
    void insert(int value) {
        fmap[value]++;
        if(fmap[value] > 1) return;
        int l = floor(interval, value);
        if(l != -1 && interval[l] >= value - 1) interval[l] = max(interval[l], value);
        else {
            l = value;
            interval[l] = l;
        }
        if(interval.count(interval[l] + 1)) {
            int val = interval[l] + 1;
            interval[l] = interval[interval[l] + 1];
            interval.erase(val);
        }
    }
    
    void erase(int value) {
        fmap[value]--;
        if(fmap[value] > 0) return;
        int l = floor(interval, value);
        if(l == value) {
            interval[value + 1] = interval[l];
            interval.erase(value);
        }
        else {
            interval[value + 1] = interval[l];
            interval[l] = value - 1;
        }
    }
    
    int ceiling(int value) {
        int f = floor(interval, value);
        if(f == -1) return value;
        return max(interval[f] + 1, value);
    }
    
    int less(int value) {
        int f = floor(interval, value);
        if(f == -1 || interval[f] + 1 <= value) return value;
        return f - 1;
    }
   
    void print() {
        for(pair<int, int> p : interval) cout << p.first << " " << p.second << endl;
        cout << endl;
    }
};