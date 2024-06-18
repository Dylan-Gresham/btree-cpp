#ifndef BTREE_H
#define BTREE_H
#include "node.hpp"
#include <vector>

template<typename T>
class BTree {
public:
    BTree() {
        this->root = new Node<T>;
    }
    ~BTree() {
        this->root.del();
    }
private:
    std::vector<Node<T>> root;
};

#endif /* BTREE_H */
