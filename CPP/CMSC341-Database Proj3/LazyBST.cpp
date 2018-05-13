// LazyBST.cpp
// Nathaniel Fuller

#include <iostream>
#include <string>
#include <assert.h>
using namespace std;

#include "LazyBST.h"

LazyBST::LazyBST(){
  nptr = NULL;
}

LazyBST::LazyBST(const LazyBST& other){
  if (other.empty()){
    nptr = NULL;
  }
  else{
    nptr = new LazyBSTNode(*(other.nptr));
  }
}

LazyBST::~LazyBST(){
  delete nptr;
}

void LazyBST::insert(DTYPE key){
  if (empty()){
    nptr = new LazyBSTNode(key);
  }
  else if (nptr->data == key){
    // do nothing, duplicates not allowed, return to main func
    // nothing changed, no updating needed
    return;
  }
  else if (nptr->data < key){
    if (checkBalance()){
      rebalance();
      // if it rebalances need to recheck key/data
      if (nptr->data < key){
	nptr->right.insert(key);
      }
      else{
	nptr->left.insert(key);
      }
    }
    else{
      nptr->right.insert(key);
    }
  }
  else{
    if (checkBalance()){
      rebalance();
      // if it rebalances need to recheck key/data
      if (nptr->data < key){
	nptr->right.insert(key);
      }
      else{
	nptr->left.insert(key);
      }
    }
    else{
      nptr->left.insert(key);
    }
  }
  update();
}

void LazyBST::inorder(){
  if (empty())
    return;
  cout << "(";
  nptr->left.inorder();
  cout << nptr->data << ":" << nptr->height << ":" << nptr->size;

  nptr->right.inorder();
  cout << ")";

  return;
}

LazyBSTNode::LazyBSTNode(){
  size = 1;
  height = 0;
}

LazyBSTNode::LazyBSTNode(DTYPE key)
  : data(key){
  size = 1;
  height = 0;
}

LazyBSTNode::~LazyBSTNode(){
  //nothing
}

const LazyBST& LazyBST::operator=(const LazyBST& rhs) {

  if (this == &rhs) return *this ;
   
  delete nptr ;

  if ( rhs.empty() ) {
    nptr = NULL ;
  } else {
    nptr = new LazyBSTNode( *(rhs.nptr) ) ;
  }

  return *this ;
}

ostream& operator<< (ostream& os, const LazyBST& T) {
  os << T.nptr ; 
  return os ;
}

void LazyBST::update(){
  // update size and height for all nodes needed
  // both null
  if (nptr->left.empty() && nptr->right.empty()){
    nptr->height = 0;
    nptr->size = 1;
  }
  // left null
  else if (nptr->left.empty() && !nptr->right.empty()){
    nptr->height = nptr->right.nptr->height + 1;
    nptr->size = nptr->right.nptr->size + 1;
  }
  // right null
  else if (nptr->right.empty() && !nptr->left.empty()){
    nptr->height = nptr->left.nptr->height + 1;
    nptr->size = nptr->left.nptr->size + 1;
  }
  // both contain values
  else{
    if (nptr->left.nptr->height > nptr->right.nptr->height){
      nptr->height = nptr->left.nptr->height + 1;
    }
    else{
      nptr->height = nptr->right.nptr->height + 1;
    }
    nptr->size = nptr->left.nptr->size + nptr->right.nptr->size + 1;
  }
}

// returns true if rebalancing needed, otherwise false
bool LazyBST::checkBalance(){
  // if curr node height is 3 or less subtree heights will be 2 or less
  // and will not need any rebalancing
  if (nptr->height <= 3){
    return false;
  }

  if (!nptr->left.empty() && !nptr->right.empty()){
    //find the smaller subtree
    if (nptr->left.nptr->size < nptr->right.nptr->size){
      // if left*2 is smaller/equal to right, rebalancing needed
      if (nptr->left.nptr->size*2 <= nptr->right.nptr->size){
        return true;
      }
      else{
        // if left*2 is > right, rebalancing not needed
        return false;
      }
    }
    else{
      // if right*2 is smaller/equal to left, rebalancing needed
      if (nptr->right.nptr->size*2 <= nptr->left.nptr->size){
        return true;
      }
      else{
        // if right*2 is > left, rebalancing not needed
        return false;
      }
    }
  }
  // case where one subtree is null and other has height > 3
  else{
    // rebalancing needed
    return true;
  }
}

void LazyBST::rebalance(){
  // convert whole subtree into an ordered array
  int size = nptr->size;
  DTYPE array[size];
  int trash = inorder2(0, array);
  
  // delete subtree
  delTree();

  // use middle value (left-middle in case of even # of values) as root node
  // for other subtrees
  arrayToTree(array, 0, size-1);
}

// recursive function that rebuilds tree from array
void LazyBST::arrayToTree(DTYPE array[], int start, int end){
  // base case
  if (start > end)
    return;
  
  // get middle value
  int middle = (start + end)/2;
  // insert into tree
  rebalanceInsert(array[middle]);

  // make left subtree
  arrayToTree(array, start, middle-1);

  // make right subtree
  arrayToTree(array, middle+1, end);
}

// copies values in order in to array
int LazyBST::inorder2(int count, DTYPE array[]){
  if (empty())
    return count;
  count = nptr->left.inorder2(count, array);
  array[count] = nptr->data;
  count++;
  count = nptr->right.inorder2(count, array);

  return count;
}

void LazyBST::delTree(){
  if (!empty()){
    nptr->left.delTree();
    nptr->right.delTree();
    delete nptr;
    nptr = NULL;
  }
}

bool LazyBST::remove(DTYPE key){
  bool answer = remove(key, 0);
  update(key);
  return answer;
}

bool LazyBST::remove(DTYPE key, int trash){
  if (empty())
    return false;
  if (nptr->data < key){
    if (checkBalance()){
      rebalance();
      if (nptr->data < key){
	nptr->right.remove(key, 0);
      }
      else{
	nptr->left.remove(key, 0);
      }
    }
    return nptr->right.remove(key, 0);
  }
  if (nptr->data > key){
    if (checkBalance()){
      rebalance();
      if (nptr->data < key){
	nptr->right.remove(key, 0);
      }
      else{
	nptr->left.remove(key, 0);
      }
    }
    return nptr->left.remove(key, 0);
  }
  
  // two children
  if (!nptr->left.empty() && !nptr->right.empty()){
    // get lowest value to right
    nptr->data = nptr->right.findMin();
    // remove node used to replace from tree
    nptr->right.remove(nptr->data, 0);
  }
  // one child on either side
  else if ((nptr->left.empty() && !nptr->right.empty()) || 
	   (!nptr->left.empty() && nptr->right.empty())){
    if (nptr->right.empty()){
      LazyBSTNode *temp = nptr;
      nptr = nptr->left.nptr;
      temp->left.nptr = NULL;
      delete temp;

      //      nptr->data = nptr->left.findMax();
      //nptr->left.remove(nptr->data, 0);
    }
    else{
      nptr->data = nptr->right.findMin();
      nptr->right.remove(nptr->data, 0);
    }
  }
  // no children
  else{
    delTree();
  }
  return true;
}

DTYPE LazyBST::findMin(){
  if (empty()){
    return NULL;
  }
  
  if (nptr->left.empty()){
    return nptr->data;
  }
  else{
    return nptr->left.findMin();
  }
}

DTYPE LazyBST::findMax(){
  if (empty()){
    return NULL;
  }

  if (nptr->right.empty()){
    return nptr->data;
  }
  else{
    return nptr->right.findMin();
  }
}

void LazyBST::update(int key){
  if (empty()){
    return;
  }
  if (nptr->data < key){
    nptr->right.update(key);
  }
  else{
    nptr->left.update(key);
  }

  update();
}

bool LazyBST::find(DTYPE key){
  if (empty())
    return false;
  if (nptr->data == key)
    return true;
  if (nptr->data < key)
    return nptr->right.find(key);
  return nptr->left.find(key);
}

bool LazyBST::locate(const char *position, DTYPE& key){
  int temp = 0;
  LazyBSTNode *tptr;
  tptr = nptr;
  while (tptr != NULL){
    if (position[temp] == 'L'){
      tptr = tptr->left.nptr;
      temp++;
    }
    else if (position[temp] == 'R'){
      tptr = tptr->right.nptr;
      temp++;
    }
    else{
      key = tptr->data;
      return true;
    }
  }
  return false;
}

void LazyBST::rebalanceInsert(DTYPE key){
  if (empty()){
    nptr = new LazyBSTNode(key);
  }
  else if (nptr->data == key){
    return;
  }
  else if (nptr->data < key){
    nptr->right.rebalanceInsert(key);
  }
  else{
    nptr->left.rebalanceInsert(key);
  }
  update();
}
