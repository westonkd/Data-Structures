/***********************************************************************
* Author:
*  Weston Dransfield
* Summary: 
*  Class implementing a BST using BTree node class
***********************************************************************/

#include <iostream>
#include <cassert>
#include "bst.h"

using namespace std;

/*********************************************************************
**************************BTree Node Class****************************
*********************************************************************/

/*********************************************************************
* BTree Constructor
* Creates a BTree node with specified data
********************************************************************/
BTree::BTree(int data)
{
   //set the data
   this->data = data;

   //set nodes to Null
   left = NULL;
   right = NULL;
   parent = NULL;
}

/*********************************************************************
* BTree Destructor
* empty for now
********************************************************************/
BTree::~BTree(void)
{
   //empty
}
 
/*********************************************************************
* BTree insertLeft
* inserts a new node to the left of this with "item" as its data
********************************************************************/     
void BTree::insertLeft(int item)
{
   //create the new node
   left = new BTree(item);

   //set the parent
   left->parent = this;
}  

/*********************************************************************
* BTree Constructor
* inserts a new node to the right of this with "item" as its data
********************************************************************/   
void BTree::insertRight(int item)
{
   //create the new node
   right = new BTree(item);

   //set the parent
   right->parent = this;
}

/*********************************************************************
* BTree getLeftChild
* returns a pointer to the left child of current node
********************************************************************/      
BTree* BTree::getLeftChild(void)
{
   //return left child
   return left;
}     

/*********************************************************************
* BTree getRightChild
* returns a pointer to the right child of current node
********************************************************************/
BTree* BTree::getRightChild(void)
{
   //return right child
   return right;
}  

/*********************************************************************
* BTree getParent
* returns a pointer to the parent of current node
********************************************************************/
BTree* BTree::getParent(void)
{
   //return parent
   return parent;
}  

/*********************************************************************
* BTree getData
* returns the data in the current node
********************************************************************/
int BTree::getData(void)
{
   //return the data in the node
   return data;
}

/*********************************************************************
* BTree setData
* sets the data of current node
********************************************************************/     
void BTree::setData(int item)
{
   data = item;
}

/*********************************************************************
* BTree setLeft
* sets the left child of current node
********************************************************************/ 
void BTree::setLeft(BTree* tree)
{
   //set the child
   left = tree;

   //if not null, set parent
   if (tree)
      left->parent = this;
}     

/*********************************************************************
* BTree setRight
* sets the right child of current node
********************************************************************/
void BTree::setRight(BTree* tree)
{
   //set the child
   right = tree;

   //set the parent if not null
   if (tree)
      right->parent = this;
}

/*********************************************************************
* BTree infix
* performs an infix visit of nodes and dispays each (LVR)
********************************************************************/
void BTree::infix(void)
{
   if (left != NULL) 
      left->infix();
   cout << data << " ";
   if (right != NULL) 
      right->infix();
}  

/*********************************************************************
* BTree prefix
* performs a prefix visit of nodes and dispays each (VLR)
********************************************************************/
void BTree::prefix(void)
{
   cout << data << " ";
   if (left != NULL) 
      left->prefix();
   if (right != NULL) 
      right->prefix();
}   

/*********************************************************************
* BTree postfix
* performs a postfix visit of nodes and dispays each (LRV)
********************************************************************/   
void BTree::postfix(void)
{
   if (left != NULL) 
      left->postfix();
   if (right != NULL) 
      right->postfix();
   cout << data << " ";
}           

/*********************************************************************
* BTree Constructor
* Visits each node in the tree by level and prints each out
********************************************************************/
void BTree::level(void)
{
   const int MAX = 50;
   BTree *queue[MAX];
   BTree *temp;
   int front = 0;
   int back = 0;

   queue[back++] = this;

   while (front != back)
   {
      temp = queue[front];
      front = (front + 1) % MAX;
      if (temp != NULL)
      {
         // visit
         cout.width(4);
         cout << temp->data << " ";
         if (temp->parent == NULL)
            cout << " Parent = NULL! " << endl;
         else
            cout << " Parent = " << temp->parent->data << "   " << endl;
         // end Visit        
         queue[back] = temp->left;
         back = (back + 1) % MAX;
         queue[back] = temp->right;
         back = (back + 1) % MAX;
    }
  }
}

/*********************************************************************
****************************BST Class*********************************
*********************************************************************/

/*********************************************************************
* BST constructor
* creates the root node with a value of '0'
********************************************************************/
BST::BST()
{
	root = new BTree(0);
}
 
/*********************************************************************
* BST empty
* tests if the tree is empty. returns 0 if empty 
********************************************************************/   
int BST::empty(void)
{
	return (root) ? 1 : 0;
}

/*********************************************************************
* BST search
* search the tree for a given value and return a pointer to  that 
* node
********************************************************************/   
BTree* BST::search(int item)
{
	//pointer to root node
	BTree *pNode = root;

	while (pNode)
	{
		//if the node contains the value, return that node
		if (pNode->getData() == item)
			return pNode;
		
		//if the node's data is less than item, go right
		if (pNode->getData() < item)
			pNode = pNode->getRightChild();

		//if the node's data is greater than item, go left
		else
			pNode = pNode->getLeftChild();
	}

	//item not found
	return NULL;
}

/*********************************************************************
* BST insert
* insert a node with given value into the tree maintaing the
* properties of a binary search tree
********************************************************************/         
void BST::insert(int item)
{
	//if the root is empty, insert item to it
	if (!root->getData())
	{
		root->setData(item);
		return;
	}

	//pointer to root node
	BTree *pNode = root;

	while (pNode)
	{	
		//if the node's data is less than item, go right
		if (pNode->getData() <= item)
		{
			if (!pNode->getRightChild())
				break;
			pNode = pNode->getRightChild();
		}

		//if the node's data is greater than item, go left
		else
		{
			if (!pNode->getLeftChild())
				break;
			pNode = pNode->getLeftChild();
		}
	}

	//insert new item into tree
	if (pNode->getData() <= item)
		pNode->insertRight(item);
	else
		pNode->insertLeft(item);
}

/*********************************************************************
* BST remove
* removes the specified node from the tree while still maintaining
* the properties of a BST. Three cases are covered
* 1. deleting a leaf node
* 2. deleting a node with one child
* 3. deleting a node with two children
********************************************************************/ 
void BST::remove(int item)
{
	//node to remove
	BTree *pNode = search(item);

	//if item to delete does not exist, return
	if (!pNode)
	{
		cout << "Item " << item << " is not found, cannot delete it!\n";
		return;
	}

	//if a leaf node
	if (pNode->getLeftChild() == NULL && pNode->getRightChild() == NULL)
	{
		//if we are deleting left child
		if (pNode->getParent()->getLeftChild() == pNode)
			pNode->getParent()->setLeft(NULL);
		else
			pNode->getParent()->setRight(NULL);

		//delete the node
		delete pNode;
	}

	//if a node with two children
	else if (pNode->getLeftChild() && pNode->getRightChild())
	{
		//temp traversal pointer
		BTree *pTemp = pNode->getLeftChild();

		//find the largest value in the left subtree
		while (pTemp->getRightChild())
			pTemp = pTemp->getRightChild();

		//replace pNode's value
		pNode->setData(pTemp->getData());

		//adjust child
		//if pTemp was a left child
		if (pTemp->getParent()->getLeftChild() == pTemp)
			pTemp->getParent()->setLeft(NULL);
		else
			pTemp->getParent()->setRight(NULL);

		//delete node
		delete pTemp;
	}

	//if a node with one child
	else
	{
		if (pNode->getLeftChild())
			cout << "deleting left\n";
		else
		{
			//if pNode was a left child
			if (pNode->getParent()->getLeftChild() == pNode)
				pNode->getParent()->setLeft(pNode->getRightChild());
			else
				pNode->getParent()->setRight(pNode->getRightChild());
		}
	}

	
}

void BST::BSTInfix(void)
{
	root->infix();
}