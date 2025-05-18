class SegmentTree {
private:
    vector<int> tree;
    int n;

    void build(int index, int low, int high, const vector<int>& arr) {
        if (low == high) {
            tree[index] = arr[low];
            return;
        }
        int mid = (low + high) / 2;
        build(2 * index + 1, low, mid, arr);
        build(2 * index + 2, mid + 1, high, arr);
        tree[index] = min(tree[2 * index + 1], tree[2 * index + 2]);
    }

    int query(int index, int low, int high, int left, int right) const {
        // No overlap 
        if (right < low || high < left) return INT_MAX;

        // Complete overlap
        if (left <= low && high <= right) return tree[index];

        int mid = (low + high) / 2;
        int lQuery = query(2 * index + 1, low, mid, left, right);
        int rQuery = query(2 * index + 2, mid + 1, high, left, right);
        return min(lQuery, rQuery);
    }

    void update(int index, int low, int high, int pos, int value) {
        if (low == high) {
            tree[index] = value;
            return;
        }
        int mid = (low + high) / 2;
        if (pos <= mid)
            update(2 * index + 1, low, mid, pos, value);
        else
            update(2 * index + 2, mid + 1, high, pos, value);

        tree[index] = min(tree[2 * index + 1], tree[2 * index + 2]);
    }

public:
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        tree.resize(4 * n + 2);
        build(0, 0, n - 1, arr);
    }

    int query(int left, int right) const {
        return query(0, 0, n - 1, left, right);
    }

    void update(int pos, int value) {
        update(0, 0, n - 1, pos, value);
    }
};
