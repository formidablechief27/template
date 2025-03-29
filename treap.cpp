struct Treap {
    struct Node {
        int key, priority, size;
        int value, lazy, sum, max;
        bool reverse;
        bool flip;
        Node *left, *right;
 
        Node(int k, int v) 
            : key(k), priority(rand()), size(1), value(v), lazy(0), sum(v), max(v),
              reverse(false), flip(false), left(nullptr), right(nullptr) {}
    };
 
    Node* root = nullptr;
 
    int size(Node* t) {
        return t ? t->size : 0;
    }
 
    void update(Node* t) {
        if (!t) return;
        t->size = size(t->left) + size(t->right) + 1;
        t->sum = t->value + (t->left ? t->left->sum : 0) + (t->right ? t->right->sum : 0);
        t->max = t->value;
        if(t->left)
            t->max = max(t->max, t->left->max);
        if(t->right)
            t->max = max(t->max, t->right->max);
    }
 
    void push(Node* t) {
        if (!t) return;
 
        if (t->lazy) {
            t->value += t->lazy;
            t->sum += t->lazy * size(t);
            t->max += t->lazy;
            if (t->left)  t->left->lazy += t->lazy;
            if (t->right) t->right->lazy += t->lazy;
            t->lazy = 0;
        }
 
        if (t->flip) {
            t->value = 1 - t->value;
            t->sum = size(t) - t->sum;
            t->max = (t->sum > 0 ? 1 : 0);
            if (t->left)  t->left->flip ^= true;
            if (t->right) t->right->flip ^= true;
            t->flip = false;
        }
 
        if (t->reverse) {
            swap(t->left, t->right);
            if (t->left)  t->left->reverse ^= true;
            if (t->right) t->right->reverse ^= true;
            t->reverse = false;
        }
    }
 
    void split(Node* t, int key, Node*& left, Node*& right, int add = 0) {
        if (!t) {
            left = right = nullptr;
            return;
        }
        push(t);
        int curr_key = add + size(t->left);
        if (key <= curr_key) {
            split(t->left, key, left, t->left, add);
            right = t;
        } else {
            split(t->right, key, t->right, right, curr_key + 1);
            left = t;
        }
        update(t);
    }
 
    Node* merge(Node* left, Node* right) {
        push(left);
        push(right);
        if (!left || !right) return left ? left : right;
 
        if (left->priority > right->priority) {
            left->right = merge(left->right, right);
            update(left);
            return left;
        } else {
            right->left = merge(left, right->left);
            update(right);
            return right;
        }
    }
    
    void inorder(Node* t) {
        if (!t) return;
        push(t);
        inorder(t->left);
        cout << t->value << " ";
        inorder(t->right);
    }
 
    void print() {
        inorder(root);
        cout << endl;
    }
    
    void print(Node *n) {
        inorder(n);
        cout << "\n";
    }
 
    void insert(int index, int value) {
        Node *t1, *t2;
        split(root, index, t1, t2);
        root = merge(merge(t1, new Node(index, value)), t2);
    }
    
    void shift_right(int l, int r) {
        Node *t1, *t2, *t3, *t4, *t5, *t6;
        split(root, r, t1, t2);
        split(t1, l, t3, t4);
        split(t2, 1, t5, t6);
        root = merge(merge(t3, t5), merge(t4, t6));
    }
 
    void erase(int index) {
        Node *t1, *t2, *t3;
        split(root, index, t1, t2);
        split(t2, 1, t2, t3);
        delete t2;
        root = merge(t1, t3);
    }
 
    int range_query(int l, int r) {
        Node *t1, *t2, *t3;
        split(root, l, t1, t2);
        split(t2, r - l + 1, t2, t3);
        int result = t2 ? t2->sum : 0;
        root = merge(merge(t1, t2), t3);
        return result;
    }
    
    int range_max(int l, int r) {
        Node *t1, *t2, *t3;
        split(root, l, t1, t2);
        split(t2, r - l + 1, t2, t3);
        int result = t2 ? t2->max : INT_MIN;
        root = merge(t1, merge(t2, t3));
        return result;
    }
 
    void range_update(int l, int r, int value) {
        Node *t1, *t2, *t3;
        split(root, l, t1, t2);
        split(t2, r - l + 1, t2, t3);
        if (t2) t2->lazy += value;
        root = merge(merge(t1, t2), t3);
    }
 
    void range_reverse(int l, int r) {
        Node *t1, *t2, *t3;
        split(root, l, t1, t2);
        split(t2, r - l + 1, t2, t3);
        if (t2) t2->reverse ^= true;
        root = merge(merge(t1, t2), t3);
    }
 
    void range_flip(int l, int r) {
        Node *t1, *t2, *t3;
        split(root, l, t1, t2);
        split(t2, r - l + 1, t2, t3);
        if (t2) t2->flip ^= true; 
        root = merge(merge(t1, t2), t3);
    }
};