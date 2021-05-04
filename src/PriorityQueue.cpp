#include "PriorityQueue.h"

#include <vector>

template <typename item>
MinPQ<item>::MinPQ() : content(std::vector<item>()) {}

template <typename item>
MinPQ<item>::MinPQ(std::vector<item> &c) : content(std::vector<item>()) 
{

    for(unsigned int i=0; i<c.size(); i++){

        this->insert(c[i]);
    }
}

template <typename item>
MinPQ<item>::MinPQ(item c[], int n) : content(std::vector<item>()) 
{
    for(unsigned int i=0; i<n; i++){

        this->insert(c[i]);
    }
}

template <typename item>
void MinPQ<item>::insert(item it){

    content.push_back(it);      // insert item at the back
    swim(size()-1);             // move it to its position in the heap order
}

template <typename item>
item MinPQ<item>::delMin(){

    item min = content[0];
    exchange(0, size()-1);         // exchange first and last item
    content.pop_back();
    sink(0);                       // move the item currently in min pos to its position in heap order
    return min; 
}

template <typename item>
item MinPQ<item>::getMin(){

    return content[0];
}

template <typename item>
void MinPQ<item>::swim(int k){

    // if parent's value is less than the item 
    // exchange an item (k) with its parent (k/2)
    // (root item does not have a parent)

    while(k>0 && less(k/2, k)){

        exchange(k, k/2);
        k = k/2;
    }
}

template <typename item>
void MinPQ<item>::sink(int k){

    // if child's value is greater than the item 
    // exchange an item (k) with its greatest child (2k or 2k+1)
    // (a leaf does not have any childs)
    int j;

    while( 2*k <= this->size()-1){

        // assumes that first child is the largest
        j = 2*k;    
        
        // compare both childs at 2k and 2k+1
        // select largest       
        if( j < this->size() - 1 && less(j, j+1) ){
            j+=1;
        }

        // check if child node is larger than current item
        if(!less(k , j)) break;

        exchange(k, j);
        k = j;
    }
}

template <typename item>
bool MinPQ<item>::less(int n1, int n2){

    return !(content[n1] < content[n2]);
}

template <typename item>
void MinPQ<item>::exchange(int n1, int n2){

    item temp = content[n1];
    content[n1] = content[n2];
    content[n2] = temp;
}

template <typename item>
int MinPQ<item>::size(){

    return content.size();
}

template <typename item>
bool MinPQ<item>::isEmpty(){

    return content.size() == 0;
}