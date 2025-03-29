class Node {
public:
    Node* links[10] = {nullptr};
    int val = 0;

    bool containsKey(char ch) {
        return links[ch - '0'] != nullptr;
    }

    Node* get(char ch) {
        return links[ch - '0'];
    }

    void put(char ch, Node* node) {
        links[ch - '0'] = node;
    }
};

class Trie {
private:
    Node* root;

public:
    Trie() {
        root = new Node();
    }

    void insert(string &s) {
        Node* node = root;
        for (char c : s) {
            if (!node->containsKey(c)) {
                node->put(c, new Node());
            }
            node = node->get(c);
            node->val++;
        }
    }

    int count(string &s) {
        vector<int> result;
        Node* node = root;
        for (char c : s) {
            if (!node->containsKey(c)) {
                return 0;
            }
            node = node->get(c);
        }
        return node->val;
    }
};