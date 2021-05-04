#ifndef PRIORITY_QUEUE
#define PRIORITY_QUEUE

#include <vector>

template <typename item>
class MaxPQ {

public:

    MaxPQ();                                    // construct an empty queue
    MaxPQ(std::vector<item> &content);           // construct a queue from a vector
    MaxPQ(item content[], int nb_of_items);     // construct a queue from an array

    void insert(item it);                       // insert an item to the end of the queue
    item delMax();                              // remove the maximum item 
    int  size();
    bool isEmpty();

private:

    void swim(int k);                           // moves item upwards in the tree to maintain heap order
    void sink(int k);                           // moves item downwards in the tree to maintain heap order

    bool less(int n1, int n2);                  // check if n1 < n2
    void exchange(int n1, int n2);              // exchange items at index n1 and n2

    std::vector<item> content;                  // index of item represent its position in the binary heap 

};

#endif