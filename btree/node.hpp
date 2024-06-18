#ifndef NODE_H
#define NODE_H
#include <vector>

template<typename T>
class Node {
public:
    Node() {

    }
    ~Node() {

    }
    void del();
private:
    std::vector<Node<T>&> children;
};

#endif /* NODE_H */
