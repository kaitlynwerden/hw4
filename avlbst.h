//avlbst.h
#ifndef RBBST_H
#define RBBST_H
 
#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"
 
struct KeyError { };
 
/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
   // Constructor/destructor.
   AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
   virtual ~AVLNode();
 
   // Getter/setter for the node's height.
  
   //balance factor
   int8_t getBalance () const;
   void setBalance (int8_t balance);
   void updateBalance(int8_t diff);
 
   // Getters for parent, left, and right. These need to be redefined since they
   // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
   // for more information.
   virtual AVLNode<Key, Value>* getParent() const override;
   virtual AVLNode<Key, Value>* getLeft() const override;
   virtual AVLNode<Key, Value>* getRight() const override;
 
protected:
   int8_t balance_;    // effectively a signed char
};
 
/*
 -------------------------------------------------
 Begin implementations for the AVLNode class.
 -------------------------------------------------
*/
 
/**
* An explicit constructor to initialize the elements by calling the base class constructor and setting
* the color to red since every new node will be red when it is first inserted.
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
   Node<Key, Value>(key, value, parent), balance_(0)
{
 
}
 
/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{
 
}
 
/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
   return balance_;
}
 
/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
   balance_ = balance;
}
 
/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
   balance_ += diff;
}
 
/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
   return static_cast<AVLNode<Key, Value>*>(this->parent_);
}
 
/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
   return static_cast<AVLNode<Key, Value>*>(this->left_);
}
 
/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
   return static_cast<AVLNode<Key, Value>*>(this->right_);
}
 
 
/*
 -----------------------------------------------
 End implementations for the AVLNode class.
 -----------------------------------------------
*/
 
 
template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
   virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
   virtual void remove(const Key& key);  // TODO
protected:
   virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);
 
   // Add helper functions here
  
   //Rotate to make the tree balanced
   //takes in a child and parent
  
  
 
   virtual AVLNode<Key,Value>* insertFix(AVLNode<Key,Value>* node);
  
   //Rotate to make the tree balanced
   //takes in a node and a difference
   virtual void removeFix(AVLNode<Key,Value>* node, int difference);
   
   Node<Key, Value> * removeNode(Node<Key, Value> *currentNode, const Key& key);

  
   virtual AVLNode<Key,Value>* rotateLeft(AVLNode<Key,Value>* node);
   virtual AVLNode<Key,Value>* rotateRight(AVLNode<Key,Value>* node);
   virtual AVLNode<Key,Value>* rotateLeftRight(AVLNode<Key,Value>* node);
   virtual AVLNode<Key,Value>* rotateRightLeft(AVLNode<Key,Value>* node);
   virtual bool isLeftChild(AVLNode<Key,Value>* child, AVLNode<Key,Value>* parent);
   virtual bool isRightChild(AVLNode<Key,Value>* child, AVLNode<Key,Value>* parent);
  
 
 
};
 
 
template<class Key, class Value>
bool AVLTree<Key, Value>::isLeftChild(AVLNode<Key,Value>* child, AVLNode<Key,Value>* parent)
{
 //helper function TODO
 if (parent->getLeft()==child)
 {
   return true;
 }
 else
 {
   return false;
 }
 }
 
template<class Key, class Value>
bool AVLTree<Key, Value>::isRightChild(AVLNode<Key,Value>* child, AVLNode<Key,Value>* parent)
{
 //helper function TODO
 if (parent->getRight()==child)
 {
   return true;
 }
 else
 {
   return false;
 }
}
 
template<class Key, class Value>
AVLNode<Key,Value>* AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* node)
{
 //helper function TODO
  //take in the unbalanced node
 //n1 = unbalanced node
 //n2 = n1's right child
 //n3 = n2's left child
  //n2 replaces n1 as subtree root
 //n2->left = n1
 //n1->right = n3
  AVLNode<Key, Value> *n1 = node;
 AVLNode<Key, Value> *n2 = node->getRight();
 AVLNode<Key, Value> *n3 = n2->getLeft();
  n2->setLeft(n1);
 n1->setParent(n2);
 n1->setRight(n3);
 if(n3 != nullptr)
 {
   n3->setParent(n1);
 }
  n1->setBalance(BinarySearchTree<Key, Value>::getHeightHelper(n1->getRight()) - BinarySearchTree<Key, Value>::getHeightHelper(n1->getLeft()));
 n2->setBalance(BinarySearchTree<Key, Value>::getHeightHelper(n2->getRight()) - BinarySearchTree<Key, Value>::getHeightHelper(n2->getLeft()));
  return n2;
}
 
template<class Key, class Value>
AVLNode<Key,Value>* AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>* node)
{
 //helper function TODO
  //take in the unbalanced node
 //n1 = unbalanced node
 //n2 = n1's left child
 //n3 = n2's right child
  //n2 replaces n1 as subtree root
 //n2->right = n1
 //n1->left = n3
  AVLNode<Key, Value> *n1 = node;
 AVLNode<Key, Value> *n2 = node->getLeft();
 AVLNode<Key, Value> *n3 = n2->getRight();
  n2->setRight(n1);
 n1->setParent(n2);
 n1->setLeft(n3);
 if(n3 != nullptr)
 {
   n3->setParent(n1);
 }
  n1->setBalance(BinarySearchTree<Key, Value>::getHeightHelper(n1->getRight()) - BinarySearchTree<Key, Value>::getHeightHelper(n1->getLeft()));
 n2->setBalance(BinarySearchTree<Key, Value>::getHeightHelper(n2->getRight()) - BinarySearchTree<Key, Value>::getHeightHelper(n2->getLeft()));
  return n2;
}
 
template<class Key, class Value>
AVLNode<Key,Value>* AVLTree<Key, Value>::rotateLeftRight(AVLNode<Key,Value>* node)
{
 //helper function TODO
  // call left rotate on node's left child
 AVLNode<Key,Value>* newLeftChild = rotateLeft(node->getLeft());
 newLeftChild->setParent(node);
 node->setLeft(newLeftChild);
  node->setBalance(BinarySearchTree<Key, Value>::getHeightHelper(node->getRight()) - BinarySearchTree<Key, Value>::getHeightHelper(node->getLeft()));
  // right rotate node
 return rotateRight(node);
 }
 
template<class Key, class Value>
AVLNode<Key,Value>* AVLTree<Key, Value>::rotateRightLeft(AVLNode<Key,Value>* node)
{
 //helper function TODO
   // call right rotate on node's right child
 AVLNode<Key,Value>* newRightChild = rotateRight(node->getRight());
 newRightChild->setParent(node);
 node->setRight(newRightChild);
  node->setBalance(BinarySearchTree<Key, Value>::getHeightHelper(node->getRight()) - BinarySearchTree<Key, Value>::getHeightHelper(node->getLeft()));
  // left rotate node
 return rotateLeft(node);
}
 
// first, recurse onto the left and then right child of node
   // then, get the height of the node's two children
   // update the balance of the node based on that
   // use ifs and elses to perform a rotation if needed based on the node and the node's left and right children's balances
   // return the new subtree root
 
template<class Key, class Value>
AVLNode<Key,Value>* AVLTree<Key, Value>::insertFix(AVLNode<Key,Value>* node)
{
 if(node == nullptr)
   return nullptr;
  //helper function TODO
 AVLNode<Key,Value>* newLeftChild =  insertFix(node->getLeft());
 if(newLeftChild != node->getLeft())
 {
   newLeftChild->setParent(node);
   node->setLeft(newLeftChild);
 }
 AVLNode<Key,Value>* newRightChild =  insertFix(node->getRight());
   if(newRightChild != node->getRight())
  {
     newRightChild->setParent(node);
     node->setRight(newRightChild);
  }
  int leftChildHeight = BinarySearchTree<Key, Value>::getHeightHelper(newLeftChild);
 int rightChildHeight = BinarySearchTree<Key, Value>::getHeightHelper(newRightChild);
  int balanceFactor = rightChildHeight - leftChildHeight;
 node->setBalance(balanceFactor);
 //update balance of the node by getting node's balance factor
  int rightChildBalanceFactor = newRightChild ? newRightChild->getBalance() : 0;
 int leftChildBalanceFactor = newLeftChild ? newLeftChild->getBalance() : 0;
  if (balanceFactor > 1 && rightChildBalanceFactor >= 0)
 {
   //left rotation
   AVLNode<Key,Value> *newSubtreeRoot = rotateLeft(node);
   return newSubtreeRoot;
 }
   else if (balanceFactor > 1 && rightChildBalanceFactor < 0)
  {
    //right left rotation
     AVLNode<Key,Value> *newSubtreeRoot = rotateRightLeft(node);
     return newSubtreeRoot;
  }
   
  else if (balanceFactor < -1 && leftChildBalanceFactor <= 0)
  {
    //right rotation
    AVLNode<Key,Value> *newSubtreeRoot = rotateRight(node);
   return newSubtreeRoot;
  }
      
 else if (balanceFactor < -1 && leftChildBalanceFactor > 0)
 {
    //left right rotation     
   AVLNode<Key,Value> *newSubtreeRoot = rotateLeftRight(node);
   return newSubtreeRoot;
 }
  return node;
}
 
/*
* Recall: If key is already in the tree, you should
* overwrite the current value with the updated value.
*/
 
template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
 // TODO
 //same insertion as bst -> insert new item or overwrite current value if key is already in tree
 
   // TODO
AVLNode<Key, Value> *currentNode = dynamic_cast<AVLNode<Key,Value>*>(BinarySearchTree<Key,Value>::root_);
  
 //did we insert the node yet
 bool nodeSet = false;
  
 //if the tree is empty then create a new node for the root
 if (currentNode == NULL)
 {
  BinarySearchTree<Key,Value>::root_ = new AVLNode<Key, Value> (new_item.first, new_item.second, NULL);
 }
  
 else 
 {
   //while we haven't set the node
   while (nodeSet==false)
   {
     //if greater then we need to go to the right
     if (new_item.first > currentNode->getKey())
     {
       //if the right of the current node is already empty just set it to the node we inserted
       if (currentNode->getRight()==NULL)
       {
         currentNode->setRight(new AVLNode<Key, Value> (new_item.first, new_item.second, currentNode));
         nodeSet = true;
       }
       
       //else if it isn't empty we need to keep going until we find an empty space
       else if (currentNode->getRight()!=NULL)
       {
         currentNode = currentNode->getRight();
       }
     }
     
     //else if less we need to go to the left 
     else if (new_item.first < currentNode->getKey())
     {
       //if the left of the current node is already empty just set it to the node we inserted
       if (currentNode->getLeft()==NULL)
       {
         currentNode->setLeft(new AVLNode<Key, Value> (new_item.first, new_item.second, currentNode));
          nodeSet = true;
       }
       
       //else if it isn't empty we need to keep going until we find an empty space
       else if (currentNode->getLeft()!=NULL)
       {
         currentNode = currentNode->getLeft();
       }
     }
     
     //if the current node key is equal to the keyValuePair's
     else if (new_item.first == currentNode->getKey())
     {
       currentNode->setValue(new_item.second);
       nodeSet = true;
     }
   }
 }
 
 //
  AVLNode<Key, Value>* root = dynamic_cast<AVLNode<Key,Value>*>(BinarySearchTree<Key,Value>::root_);
  BinarySearchTree<Key,Value>::root_ = insertFix(root);
}
 
template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key,Value>* node, int difference)
{
    
}
 
 
/*
* Recall: The writeup specifies that if a node has 2 children you
* should swap with the predecessor and then remove.
*/

template<class Key, class Value>
Node<Key, Value> * AVLTree<Key, Value>::removeNode(Node<Key, Value> *currentNode, const Key& key)
{
 
  // base case
  if(currentNode == nullptr)
  {
  	return nullptr;
  }
  
  
  // go right or left if needed
  if(currentNode->getKey() > key) {
    currentNode->setLeft(removeNode(currentNode->getLeft(), key));
    if(currentNode->getLeft() != nullptr)
    {
    	currentNode->getLeft()->setParent(currentNode);
    }
  }
  else if(currentNode->getKey() < key) {
    currentNode->setRight(removeNode(currentNode->getRight(), key));
    if(currentNode->getRight() != nullptr)
    {
    	currentNode->getRight()->setParent(currentNode);
    }
  }
  else {
    // we've found the correct key
    
    // if there's no children, just delete the current node
    if(currentNode->getLeft() == nullptr && currentNode->getRight() == nullptr) 
    {
      delete currentNode;
      return nullptr;
		}
    else if(currentNode->getLeft() != nullptr && currentNode->getRight() == nullptr) 
    {
      // one child replaces this node
      Node<Key,Value>* temp = currentNode->getLeft();
      delete currentNode;
      return temp;
    }
    else if(currentNode->getLeft() == nullptr && currentNode->getRight() != nullptr) 
    {
      // one child replaces this node
      Node<Key,Value>* temp = currentNode->getRight();
      delete currentNode;
      return temp;
    }
    //two children
    else 
    {
      // find max of left subtree
      Node<Key,Value>* previousNode = currentNode->getLeft();
      while(previousNode->getRight() != nullptr)
      {
        previousNode = previousNode->getRight();
      }
      
      // swap them 
      nodeSwap(dynamic_cast<AVLNode<Key,Value>*>(currentNode), dynamic_cast<AVLNode<Key,Value>*>(previousNode));
      
      previousNode->setLeft(removeNode(previousNode->getLeft(), key));
      if(previousNode->getLeft() != nullptr)
      {
        previousNode->getLeft()->setParent(previousNode);
			}
      return previousNode;
    }
  }
     
  return currentNode;
}


template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
  //TODO
  BinarySearchTree<Key,Value>::root_ = removeNode(BinarySearchTree<Key,Value>::root_, key);
  BinarySearchTree<Key,Value>::root_ = insertFix(dynamic_cast<AVLNode<Key,Value>*>(BinarySearchTree<Key,Value>::root_));
}
 
template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
   BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
   int8_t tempB = n1->getBalance();
   n1->setBalance(n2->getBalance());
   n2->setBalance(tempB);
}
 
 
#endif
 


