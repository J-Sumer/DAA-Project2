/*
This data structure is created by the team.
It's operations and behaviour is similar to the C++ STL priority_queue.
*/

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <functional>
#include <map>
using namespace std;

template <class Key, class Comp = greater<Key>>
class Heap
{
public:
    typedef Key key_type;

private:
    /*
    current size of the heap
    */
    int size;

    /*
    Used to keep track of keys. The map is updated
    everytime any operation is performed on the node
    */
    map<key_type, int> key_map;

    /*
    Node : Defines a structure that is a node in the heap.
    It keeps track of the information that is needed to perform heap
    operations.
    */
    typedef struct Node
    {
        key_type val;
        int lchild;
        int rchild;
        int parent;
        int pos;
        void set_Node(Heap *, key_type);

    } Node;

    /*
    Vec: Vector is used to maintain the heap.
    */
    vector<Node> vec;

    /*
    Comparison operator in order to compare nodes
    and perform heap operations. By default takes
    the greater comparator object. It can be
    overriden by custom comparator.
    */
    Comp cmp;

    /*
    helper function  in order to swap values of nodes
    Used in heapify and min_heap functions to maintain
    the min heap property. Swap key1 and key2.
    */
    void swap(int key1, int key2);

    /*
    Performs the heapify operation and maintains the heap
    property. Used when a key is popped from the heap and
    the minimum key after deletion should be placed at the
    top of the heap
    */
    void heapify(int);

    /*
    Another operation to maintain the heap property. Unlike
    heapify min_heap is used when keys are added to the heap
    and also when keys are updated.
    */
    void min_heap(int);

    /*
    Updates the heap when one of it's key is updated
    Note: It handles the situation only when the new value
    is less than the old value
    */
    void decrease_key(key_type old_key, key_type new_key);

public:
    /*
    Default constructor.
    Note: It takes the greater<> comparator object
     */
    explicit Heap();

    /*
    Call this constructor when the default comparator
    is overriden by custom comparator.
    */
    explicit Heap(const Comp &c);

    /*
    Destructor for heap.
    */
    ~Heap();

    /*
    push new key to the heap
    */
    void push(key_type new_key);

    /*
    returns the element at the top of the heap
    */
    key_type top();

    /*
    checks if the heap is empty
    */
    bool empty();

    /*
    pops the key at the top of the heap
    */
    void pop();

    /*
    update value of old_key with new_key
    Note: Value of new_key should be less
    than old_key.
    */
    void update_key(key_type old_key, key_type new_key);
    // void display();
};

template <class Key, class Comp>
Heap<Key, Comp>::Heap() : cmp(greater<key_type>())
{
    size = 0;
}

template <class Key, class Comp>
Heap<Key, Comp>::Heap(const Comp &c) : cmp(c)
{
    size = 0;
}

template <class Key, class Comp>
Heap<Key, Comp>::~Heap()
{
    // delete [] Node;
}

template <class Key, class Comp>
void Heap<Key, Comp>::heapify(int index)
{
    if (index < 0)
        return;
    int r = vec[index].rchild;
    int l = vec[index].lchild;

    if (r != -1 && l == -1 && cmp(vec[index].val, vec[r].val))
    {
        swap(index, r);
        heapify(r);
    }
    else if (l != -1 && r == -1 && cmp(vec[index].val, vec[l].val))
    {
        swap(index, l);
        heapify(l);
    }
    else if (l != -1 && r != -1)
    {
        if (cmp(vec[r].val, vec[l].val) && cmp(vec[index].val, vec[l].val))
        {
            swap(index, l);
            heapify(l);
        }
        else if (cmp(vec[index].val, vec[r].val))
        {
            swap(index, r);
            heapify(r);
        }
        else
            return;
    }
}

template <class Key, class Comp>
void Heap<Key, Comp>::min_heap(int index)
{
    if (index < 0)
        return;
    int r = vec[index].rchild;
    int l = vec[index].lchild;

    if (r != -1 && cmp(vec[index].val, vec[r].val))
    {
        swap(index, r);
        min_heap(vec[index].parent);
    }
    else if (l != -1 && cmp(vec[index].val, vec[l].val))
    {
        swap(index, l);
        min_heap(vec[index].parent);
    }
}

template <class Key, class Comp>
void Heap<Key, Comp>::decrease_key(key_type old_key, key_type new_key)
{
    int pos = key_map[old_key];
    vec[pos].val = new_key;
    key_map[new_key] = pos;
    min_heap(vec[pos].parent);
}

template <class Key, class Comp>
void Heap<Key, Comp>::push(key_type new_key)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    vec.push_back(*new_node);
    size++;
    vec.back().set_Node(this, new_key);
    min_heap(vec.back().parent);
}

template <class Key, class Comp>
Key Heap<Key, Comp>::top()
{
    return vec.front().val;
}

template <class Key, class Comp>
void Heap<Key, Comp>::swap(int key1, int key2)
{
    key_type tmp;
    tmp = vec[key1].val;
    vec[key1].val = vec[key2].val;
    vec[key2].val = tmp;
    key_map[vec[key1].val] = vec[key1].pos;
    key_map[vec[key2].val] = vec[key2].pos;
}

template <class Key, class Comp>
void Heap<Key, Comp>::pop()
{

    key_type tmp = vec.front().val;
    vec.front().val = vec.back().val;
    vec.back().val = tmp;
    int p = vec.back().parent;

    if (vec[p].rchild == vec.back().pos)
        vec[p].rchild = -1;
    else
        vec[p].lchild = -1;

    vec.pop_back();
    size--;
    heapify(0);
}

template <class Key, class Comp>
void Heap<Key, Comp>::update_key(key_type old_key, key_type new_key)
{
    decrease_key(old_key, new_key);
}

template <class Key, class Comp>
bool Heap<Key, Comp>::empty()
{
    return size == 0;
}

template <class Key, class Comp>
void Heap<Key, Comp>::Node::set_Node(Heap *hp, key_type _val)
{
    val = _val;
    lchild = -1;
    rchild = -1;
    pos = hp->size - 1;
    if (pos % 2 == 0)
    {
        parent = pos / 2 - 1;
        if (parent >= 0)
            hp->vec[parent].rchild = pos;
    }
    else
    {
        parent = pos / 2;
        hp->vec[parent].lchild = pos;
    }
}
