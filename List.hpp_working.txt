#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include <iterator>
#include <cassert>

template <typename T>
class List {
private:
    struct Node {
        Node* prev;
        Node* next;
        T datum;
    };

public:
    // Constructors and Destructor
    List() : first(nullptr), last(nullptr) {}
    ~List() { clear(); }
    List(const List<T>& other) : first(nullptr), last(nullptr) { copy_all(other); }
    List<T>& operator=(const List<T>& rhs) {
        if (this != &rhs) {
            clear();
            copy_all(rhs);
        }
        return *this;
    }

    // Required functions
    bool empty() const { return first == nullptr; }
    int size() const {
        int count = 0;
        for (Node* current = first; current != nullptr; current = current->next) {
            ++count;
        }
        return count;
    }

    T& front() {
        assert(first != nullptr);
        return first->datum;
    }

    T& back() {
        assert(last != nullptr);
        return last->datum;
    }

    void push_front(const T& datum) {
        Node* newNode = new Node{nullptr, first, datum};
        if (first != nullptr) {
            first->prev = newNode;
        }
        first = newNode;
        if (last == nullptr) {
            last = first;
        }
    }

    void push_back(const T& datum) {
        Node* newNode = new Node{last, nullptr, datum};
        if (last != nullptr) {
            last->next = newNode;
        }
        last = newNode;
        if (first == nullptr) {
            first = last;
        }
    }

    void pop_front() {
        assert(first != nullptr);
        Node* oldFirst = first;
        first = first->next;
        if (first != nullptr) {
            first->prev = nullptr;
        } else {
            last = nullptr;
        }
        delete oldFirst;
    }

    void pop_back() {
        assert(last != nullptr);
        Node* oldLast = last;
        last = last->prev;
        if (last != nullptr) {
            last->next = nullptr;
        } else {
            first = nullptr;
        }
        delete oldLast;
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    class Iterator {
    public:
        Iterator() : list_ptr(nullptr), node_ptr(nullptr) {}
        Iterator(const List* lp, Node* np) : list_ptr(lp), node_ptr(np) {}

        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        Iterator& operator++() {
            assert(node_ptr != nullptr);
            node_ptr = node_ptr->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }

        Iterator& operator--() {
            assert(node_ptr != nullptr);
            node_ptr = node_ptr->prev;
            return *this;
        }

        Iterator operator--(int) {
            Iterator temp = *this;
            --(*this);
            return temp;
        }

        T& operator*() const {
            assert(node_ptr != nullptr);
            return node_ptr->datum;
        }

        T* operator->() const {
            assert(node_ptr != nullptr);
            return &(node_ptr->datum);
        }

        bool operator==(const Iterator& other) const {
            return list_ptr == other.list_ptr && node_ptr == other.node_ptr;
        }

        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }

        Iterator& operator=(const Iterator& other) {
            list_ptr = other.list_ptr;
            node_ptr = other.node_ptr;
            return *this;
        }

    private:
        const List* list_ptr;
        Node* node_ptr;

        friend class List<T>;
    };

    Iterator begin() const {
        return Iterator(this, first);
    }

    Iterator end() const {
        return Iterator(this, nullptr);
    }

    Iterator erase(Iterator i) {
        assert(i != end());
        Node* current = i.node_ptr;
        ++i;
        if (current->prev != nullptr) {
            current->prev->next = current->next;
        } else {
            first = current->next;
        }
        if (current->next != nullptr) {
            current->next->prev = current->prev;
        } else {
            last = current->prev;
        }
        delete current;
        return i;
    }

    Iterator insert(Iterator i, const T& datum) {
        Node* newNode = new Node{i.node_ptr->prev, i.node_ptr, datum};
        if (i.node_ptr->prev != nullptr) {
            i.node_ptr->prev->next = newNode;
        } else {
            first = newNode;
        }
        i.node_ptr->prev = newNode;
        return Iterator(this, newNode);
    }

private:
    void copy_all(const List<T>& other) {
        for (Node* current = other.first; current != nullptr; current = current->next) {
            push_back(current->datum);
        }
    }

    Node* first;
    Node* last;
};

#endif // LIST_HPP
