#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 Project 4
 */

#include <iostream>
#include <iterator> //std::bidirectional_iterator_tag
#include <cassert>  //assert

template <typename T>
class List {

private:
    //a private type
    struct Node 
    {
        Node* prev;
        Node* next;
        T datum;
    };

    //OVERVIEW: a doubly-linked, double-ended list with Iterator interface

public:

    //Constructors and destructors list
    List() : first(nullptr), last(nullptr) {}
    ~List() { clear(); }
    List(const List<T>& other) : first(nullptr), last(nullptr) { copy_all(other); }
    List<T>& operator=(const List<T>& rhs)
    {
        if (this != &rhs)
        {
            clear();
            copy_all(rhs);
        }
        return *this;
    }

    //EFFECTS:  returns true if the list is empty
    bool empty() const
    { 
        return first == nullptr;
    }
    
    //EFFECTS: returns the number of elements in this List
    //HINT:    Traversing a list is really slow. Instead, keep track of the size
    //         with a private member variable. That's how std::list does it.
    int size() const
    {
        int count = 0;

        for (Node* current = first; current != nullptr; current = current->next)
        {
            ++count;
        }
        return count;
    }

    //REQUIRES: list is not empty
    //EFFECTS: Returns the first element in the list by reference
    T & front()
    {
        assert(first != nullptr);
        return first->datum;
    }

    //REQUIRES: list is not empty
    //EFFECTS: Returns the last element in the list by reference
    T & back()
    {
        assert(last != nullptr);
        return last->datum;
    }

    //EFFECTS:  inserts datum into the front of the list
    void push_front(const T& datum) 
    {
        Node* newNode = new Node{nullptr, first, datum};
        if (first != nullptr) {
            first->prev = newNode;
        }
        first = newNode;
        if (last == nullptr) {
            last = first;
        }
    }

    //EFFECTS:  inserts datum into the back of the list
    void push_back(const T& datum)
    {
        Node* newNode = new Node{last, nullptr, datum};
        if (last != nullptr) {
            last->next = newNode;
        }
        last = newNode;
        if (first == nullptr) {
            first = last;
        }
    }

    //REQUIRES: list is not empty
    //MODIFIES: may invalidate list iterators
    //EFFECTS:  removes the item at the front of the list
    void pop_front()
    {
        assert(first != nullptr);
        Node* oldFirst = first;
        first = first->next;
        if (first != nullptr)
        {
            first->prev = nullptr;
        } 
        else
        {
            last = nullptr;
        }
        delete oldFirst;
    }

    //REQUIRES: list is not empty
    //MODIFIES: may invalidate list iterators
    //EFFECTS:  removes the item at the back of the list
    void pop_back()
    {
        assert(last != nullptr);
        Node* oldLast = last;
        last = last->prev;
        
        if (last != nullptr) 
        {
            last->next = nullptr;
        }
        else
        {
            first = nullptr;
        }
        delete oldLast;
    }

    //MODIFIES: may invalidate list iterators
    //EFFECTS:  removes all items from the list
    void clear()
    {
        while (!empty())
        {
            pop_front();
        }
    }

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you should omit them. A user
    // of the class must be able to create, copy, assign, and destroy Lists.


    class Iterator
    {
        public:
            Iterator() : list_ptr(nullptr), node_ptr(nullptr) {}
            Iterator(const List* lp, Node* np) : list_ptr(lp), node_ptr(np) {}

            using iterator_category = std::bidirectional_iterator_tag;
            using value_type = T;
            using difference_type = std::ptrdiff_t;
            using pointer = T*;
            using reference = T&;

        // This operator will be used to test your code. Do not modify it.
        // REQUIRES: Iterator is decrementable. All iterators associated with a
        //           list are decrementable, including end iterators, except for
        //           begin iterators (those equal to begin() on the list)
        // EFFECTS:  moves this Iterator to point to the previous element
        //           and returns a reference to this Iterator

        Iterator& operator--()
        { // prefix -- (e.g. --it)
            assert(list_ptr);
            assert(*this != list_ptr->begin());
            if (node_ptr)
            {
                node_ptr = node_ptr->prev;
            }
            else
            { // decrementing an end Iterator moves it to the last element
                node_ptr = list_ptr->last;
            }
            return *this;
        }

        // This operator will be used to test your code. Do not modify it.
        // REQUIRES: Iterator is decrementable. All iterators associated with a
        //           list are decrementable, including end iterators, except for
        //           begin iterators (those equal to begin() on the list)
        // EFFECTS:  moves this Iterator to point to the previous element
        //           and returns a copy of the original Iterator
    
        Iterator operator--(int) 
        { // postfix -- (e.g. it--)
            Iterator copy = *this;
            operator--();
            return copy;
        }

        Iterator& operator++()
        {
            assert(list_ptr);
            assert(node_ptr != nullptr); // Ensure the iterator is valid

            if (node_ptr->next)
            {
                node_ptr = node_ptr->next;
            }
            else 
            { // Incrementing end Iterator moves it past the end
                node_ptr = nullptr;
            }
            return *this;
        }

        Iterator operator++(int)
        {
            Iterator copy = *this;
            if (node_ptr->next)
            {
                node_ptr = node_ptr->next;
            } 
            else
            { // Incrementing end Iterator moves it past the end
                node_ptr = nullptr;
            }
            return copy; // Return the copy of the iterator before incrementing
        }

        T &operator*() const
        {
            assert(node_ptr != nullptr);
            return node_ptr->datum;
        }

        T* operator->() const
        {
            assert(node_ptr != nullptr);
            return &(node_ptr->datum);
        }

        bool operator==(const Iterator& other) const
        {
            return list_ptr == other.list_ptr && node_ptr == other.node_ptr;
        }

        bool operator!=(const Iterator& other) const
        {
            return !(*this == other);
        }

        Iterator& operator=(const Iterator& other)
        {
            list_ptr = other.list_ptr;
            node_ptr = other.node_ptr;
            return *this;
        }

        private:
            const List* list_ptr;
            Node* node_ptr;

        friend class List<T>;
    };

    // return an Iterator pointing to the first element

    Iterator begin() const
    {
        return Iterator(this, first);
    }

    // return an Iterator pointing to "past the end"

    Iterator end() const
    {
        return Iterator(this, nullptr);
    }

    //REQUIRES: i is a valid, dereferenceable iterator associated with this list
    //MODIFIES: may invalidate other list iterators
    //EFFECTS: Removes a single element from the list container.
    //         Returns An iterator pointing to the element that followed the
    //         element erased by the function call

    Iterator erase(Iterator i)
    {
        assert(i != end());
        Node* current = i.node_ptr;
        ++i;
        if (current->prev != nullptr)
        {
            current->prev->next = current->next;
        }
        else
        {
            first = current->next;
        }
        if (current->next != nullptr)
        {
            current->next->prev = current->prev;
        }
        else
        {
            last = current->prev;
        }
        delete current;
        return i;
    }

    //REQUIRES: i is a valid iterator associated with this list
    //EFFECTS: Inserts datum before the element at the specified position.
    //         Returns an iterator to the the newly inserted element.

    Iterator insert(Iterator i, const T& datum)
    {
        Node* newNode = new Node{i.node_ptr->prev, i.node_ptr, datum};
        if (i.node_ptr->prev != nullptr)
        {
            i.node_ptr->prev->next = newNode;
        }
        else
        {
            first = newNode;
        }
        i.node_ptr->prev = newNode;
        return Iterator(this, newNode);
    }

    private:
        Node *first;   // points to first Node in list, or nullptr if list is empty
        Node *last;    // points to last Node in list, or nullptr if list is empty

    //REQUIRES: list is empty
    //EFFECTS:  copies all nodes from other to this

        void copy_all(const List<T>& other) 
        {
            for (Node* current = other.first; current != nullptr; current = current->next)
            {
                push_back(current->datum);
            }
        }

}; //List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.
