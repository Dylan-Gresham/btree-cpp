#ifndef TREE_OBJECT_HPP
#define TREE_OBJECT_HPP

template<typename T>
class TreeObject {
protected:
    T data;
    long long count;
public:
    TreeObject(T data) {
        this->data = data;
        this->count = 1;
    }

    T get_data() {
        return this->data;
    }

    static int get_disk_size() {
        return sizeof(long long) * 2;
    }

    void set_data(T new_data) {
        this->data = new_data;
    }

    void add_count() {
        this->count += 1;
    }

    void set_count(long long new_count) {
        this->count = new_count;
    }

    int compate_to(T data) {
        if(this->data < data) {
            return -1;
        } else if(this->data > data) {
            return 1;
        } else {
            return 0;
        }
    }
};

#endif /* TREE_OBJECT_HPP */
