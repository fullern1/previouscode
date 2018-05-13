//Nathaniel Fuller
//CMSC 341 proj4
//MinMaxHeap.h

#ifndef _MINMAXHEAP_H_
#define _MINMAXHEAP_H_

#include <iostream>

template <typename T>
class Heap;

template <typename T> 
class MinMaxHeap{
 public:
  MinMaxHeap(int capacity)  ;

  MinMaxHeap(const MinMaxHeap<T>& other)  ;
  
  ~MinMaxHeap()  ;
  
  const MinMaxHeap<T>& operator=(const MinMaxHeap<T>& rhs)  ;

  int size() ;

  void insert(const T& data) ;

  T deleteMin();
  
  T deleteMax() ;
    
  void dump() ;

  void locateMin(int pos, T& data, int& index) ;

  void locateMax(int pos, T& data, int& index) ;

 private:
   Heap<T> *minHeap;
   Heap<T> *maxHeap;
};

// for bubbling up/trickling down to maintain heap
template <typename T>
class Heap{
  
  friend class MinMaxHeap<T>;

 public:
  Heap(int capacity);
  Heap(const Heap<T>& other)  ;
  ~Heap()  ;

  void updateMin(int location);
  void updateMax(int location);
  void swap(int parent, int child);

 private:
  T data[1500]; 
  // stores location of data in other heap parallel to data in this heap
  int otherHeapLoc[1500]; 
  int heapCapacity;
  int heapSize;
  Heap *otherPtr;
  int endHeap;
};

#include "MinMaxHeap.cpp"
#endif
