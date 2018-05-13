//Nathaniel Fuller
//CMSC 341 proj 4
//Driver.cpp
#include <iostream>
#include "MinMaxHeap.h"
#include <string>

using namespace std;

template <typename T>
void sanityCheck(MinMaxHeap<T>& H) {
  int n = H.size() ;
  T minKey, maxKey, leftKey, rightKey ;
  int minPos, maxPos, pos ;
   
  bool passed=true ;

  cout << "Sanity Check minHeap...\n" ;

  for (int i=1 ; i<=n ; i++) {
    H.locateMin(i,minKey,maxPos) ; 
    H.locateMax(maxPos,maxKey,minPos) ; 
      
    if (minKey != maxKey) {
      passed = false ;
      cout << "Key mismatch at i = " << i << ": "
	   << "minKey = " << minKey << ", " 
	   << "minPos = " << minPos << ", " 
	   << "maxKey = " << maxKey << ", " 
	   << "maxPos = " << maxPos 
	   << endl ;
    }

    if (minPos != i) {
      passed = false ;
      cout << "Position mismatch at i = " << i << ": "
	   << "minKey = " << minKey << ", " 
	   << "minPos = " << minPos << ", " 
	   << "maxKey = " << maxKey << ", " 
	   << "maxPos = " << maxPos 
	   << endl ;
    }

    if (2*i <= n) {  // has left child
      H.locateMin(2*i,leftKey,pos) ;
      if (leftKey < minKey) {  // left child smaller than root 
	passed = false ;
	cout << "Bad heap condition at i = " << i << ": "
	     << "root key = " << minKey << ", " 
	     << "left key = " << leftKey 
	     << endl ;
      }
    }  

    if (2*i+1 <= n) {  // has right child
      H.locateMin(2*i+1,rightKey,pos) ;
      if (rightKey < minKey) {  // right child smaller than root 
	passed = false ;
	cout << "Bad heap condition at i = " << i << ": "
	     << "root key = " << minKey << ", " 
	     << "right key = " << rightKey 
	     << endl ;
      }
    }  

  }  // end of for (...)


  cout << "Sanity Check maxHeap...\n" ;

  for (int i=1 ; i<=n ; i++) {
    H.locateMax(i,maxKey,minPos) ; 
    H.locateMin(minPos,minKey,maxPos) ; 
      
    if (minKey != maxKey) {
      passed = false ;
      cout << "Key mismatch at i = " << i << ": "
	   << "minKey = " << minKey << ", " 
	   << "minPos = " << minPos << ", " 
	   << "maxKey = " << maxKey << ", " 
	   << "maxPos = " << maxPos 
	   << endl ;
    }

    if (maxPos != i) {
      passed = false ;
      cout << "Position mismatch at i = " << i << ": "
	   << "minKey = " << minKey << ", " 
	   << "minPos = " << minPos << ", " 
	   << "maxKey = " << maxKey << ", " 
	   << "maxPos = " << maxPos 
	   << endl ;
    }

    if (2*i <= n) {  // has left child
      H.locateMax(2*i,leftKey,pos) ;
      if (leftKey > maxKey) {  // left child bigger than root 
	passed = false ;
	cout << "Bad heap condition at i = " << i << ": "
	     << "root key = " << maxKey << ", " 
	     << "left key = " << leftKey 
	     << endl ;
      }
    }  

    if (2*i+1 <= n) {  // has right child
      H.locateMax(2*i+1,rightKey,pos) ;
      if (rightKey > maxKey) {  // right child bigger than root 
	passed = false ;
	cout << "Bad heap condition at i = " << i << ": "
	     << "root key = " << maxKey << ", " 
	     << "right key = " << rightKey 
	     << endl ;
      }
    }  
  }  // end of for (...)


  if (passed) {
    cout << "Passed sanityCheck().\n" ;
  } else {
    cout << "*** Failed sanityCheck().\n" ;
  }
}

int main(){
  MinMaxHeap<int> H(25);

  // deleting only node
  H.insert(5);
  H.dump();
  H.deleteMin();
  H.dump();
  
  H.insert(5) ;
  H.insert(10) ;
  H.insert(7) ;
  H.insert(9) ;
  H.insert(6) ;
  H.insert(2) ;
  H.insert(16) ;
  H.insert(12) ;
  H.insert(11) ;

  cout << "Initial MinMax Heap\n" ;
  H.dump() ;

  H.insert(8); 
  cout << "After inserting 8\n" ;
  H.dump() ;

  sanityCheck(H) ;

  int answer ;
  answer = H.deleteMin() ;
  cout << "\n\nMin item " << answer << " removed from MinMax Heap\n" ;

  H.dump() ;
  sanityCheck(H) ;

  answer = H.deleteMax() ;
  cout << "\n\nMax item " << answer << " removed from MinMax Heap\n" ;

  H.dump() ;
  sanityCheck(H) ;

  MinMaxHeap<string> G(25);
  G.insert("jkl") ;
  G.insert("yz_") ;
  G.insert("abc") ;
  G.insert("mno") ;
  G.insert("vwx") ;
  G.insert("pqr") ;
  G.insert("ghi") ;
  G.insert("def") ;
  G.insert("stu") ;

  G.dump() ;
  sanityCheck(G) ;

  string answer2 ;
  answer2 = G.deleteMin() ;
  cout << "Min item " << answer2 << " removed from MinMax Heap\n" ;

  answer2 = G.deleteMax() ;
  cout << "Max item " << answer2 << " removed from MinMax Heap\n" ;

  G.dump() ;
  sanityCheck(G) ;

  MinMaxHeap<int> F(300);
  for (int i = 0; i < 250; i++){
    F.insert(i);
  }
  F.dump();

  sanityCheck(F);

  cout << "initial MinMax heap\n";
  H.dump();
  
  // last spot in heap not copied correctly???????
  MinMaxHeap<int> *Gptr = new MinMaxHeap<int>(H);
  cout << "copied MinMax heap\n";
  Gptr->dump();
  
  H.deleteMax();
  Gptr->deleteMin();
  
  cout << "initial after delete max\n";
  H.dump();

  cout << "copy after delete min\n";
  Gptr->dump();

  delete Gptr;
}
