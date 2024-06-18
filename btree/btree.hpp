#ifndef BTREE_H
#define BTREE_H

// Standard library imports
#include <fstream>
#include <string>
#include <vector>

// Custom imports
#include "tree_object.hpp"

// Define offset between nodes
static const short OFFSET = sizeof(int) + sizeof(long long) + 1;

template<typename T>
class BTree {
private:
    // Define Node class
    class Node {
    public:
        long long node_id;

        Node() {
            this->node_id = next_id;
            this->data = new std::vector<TreeObject<T>>(max_degree - 1);
            this->children = new std::vector<long long>(max_degree);

            num_nodes++;
            next_id += node_width;

            for(int i = 0; i < max_degree - 1; i++) {
                data->push_back(NULL);
                children->push_back(NULL);
            }

            children->push_back(NULL);
        }

        ~Node() {
            delete this->data;
            delete this->children;
        }

         int not_null_data() {
            int ret = 0;
            for(TreeObject<T> t_obj : this->data) {
                if(t_obj) {
                    ret++;
                } else {
                    break;
                }
            }

            return ret;
        }

        Node split(int index);
        void insert_data(TreeObject<T> t_obj, long long new_child, long long old_child);
        int get_disk_size();
        int find_index(T data);
        int node_size();
        bool is_full();
        bool is_leaf();
        Node get_child(int index);
        long long get_count(long long id);
        std::string to_string();
        std::vector<std::string> to_string_vector();
        std::vector<std::vector<std::string>> get_data_array();
    private:
        std::vector<TreeObject<T>>* data;
        std::vector<long long>* children;

        Node get_node(long long node_id);
    };
public:
    BTree(int max_degree, std::string file_name) {
        this->max_degree = max_degree;
        this->file_name = file_name;

        this->next_id = OFFSET;
        this->node_width = sizeof(int) + (2 * sizeof(long long) * (max_degree - 1)) + (max_degree * sizeof(long long));
        this->num_nodes = 0;
        this->num_keys = 0;
        this->height = 0;
        this->reading = false;

        this->read_from_file(file_name);
    }

    ~BTree() {
        this->root.del();
    }

    Node search(T to_find);
    long long frequency_search(long long key);
    void insert(T element);
    void remove(T element);
    int get_height() {
        return this->height;
    }
    Node get_root() {
        return this->root;
    }
    int get_size() {
        return this->num_nodes;
    }
    long long get_num_keys() {
        return this->num_keys;
    }
    Node get(long long id);
    std::vector<std::string> to_string_vector();
    void print_tree();
    void close_tree();
    /*
     * virtual void insert_all_db(Database db);
     */
protected:
    static long long next_id, node_width, num_nodes;
    static int max_degree;
    bool reading;
    long long offset, num_keys;
    int height;
private:
    Node root;
    std::string file_name;

    void disk_read_metadata(std::ifstream file); // WARNING: Not sure if ifstream is proper type
    void disk_write_metadata(std::ofstream file);
    Node disk_read(long long id);
    void disk_write(Node node);
    void read_from_file(std::string file_name);
    long long recursive_search(Node node, long long key);
    void insert(Node node, T element);
    std::vector<std::string> to_string_vector(Node node);
    /*
     * virtual void insert_db(Database db, Node node);
     */
};

#endif /* BTREE_H */

