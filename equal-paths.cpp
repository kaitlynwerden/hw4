#include "equal-paths.h"
using namespace std;

int equalPathLength(Node* node, int depth);
// You may add any prototypes of helper functions here

int equalPathLength(Node* node, int depth)
{
  // base case: if we're a leaf, return depth
  if (node->left == nullptr && node->right == nullptr)
  {
    return depth;
  }
  // if we have two children,
  if (node->left != nullptr && node->right != nullptr)
  {
    int leafDepthLeft = equalPathLength(node->left, depth+1);
    int leafDepthRight = equalPathLength(node->right, depth+1);
    if (leafDepthLeft == -1 || leafDepthRight == -1)
    {
      return -1;
    }
    
    if (leafDepthLeft != leafDepthRight)
    {
      return -1;
    }
    
    return leafDepthLeft;
  }
  
  
  if (node->left != nullptr && node->right == nullptr)
  {
    return equalPathLength(node->left, depth+1);
  }
  
  if (node->left == nullptr && node->right != nullptr)
  {
    return equalPathLength(node->right, depth+1);
  }
  
  // should never be reached
  return -1;
  
  //   let leafDepthLeft, leafDepthRight = call equalPathLength on our children with depth+1
  //   if leafDepthLeft == -1 or leafDepthRight is -1,
  //		 return -1
  //   if leafDepthLeft != leafDepthRight
  //     return -1
  //   return leafDepthLeft
    
  // if we have one child,
  //   return equalPathLength(that child, depth+1)
}

bool equalPaths(Node * root)
{
  if(root == nullptr)
    return true;
  
    // Add your code below
  if (equalPathLength(root, 0)==-1)
  {
    return false;
  }
  
  return true;
  

}