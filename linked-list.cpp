/***********************************************************************
* Author:
*  Weston Dransfield
* Summary: 
*  Implementation file for the list class
***********************************************************************/

#include "list.h"
#include <iostream>
#include <cassert>

using namespace std;

/*********************************************************************
 * Node::getNext
 * This function returns the next opinter of a node in a linked list
 ********************************************************************/
Node::Node()
{
   //create an empty node
   data = 0;
   next = NULL;
}

/*********************************************************************
 * Node::getNext
 * This function returns the next opinter of a node in a linked list
 ********************************************************************/
 Node* Node::getNext()
 {
   if (this == NULL)
      return this;
   //return the next pointer
   return next;
 }

/*********************************************************************
 * Node::getData
 * This function returns the actual data in the node
 * This function returns the actual data in the node
 ********************************************************************/
int Node::getData()
{
   //return the data item in the node
   return data;
}

/*********************************************************************
 * Node::setData
 * Sets the value of the data a node holds
 ********************************************************************/
void Node::setData(int item)
{
   data = item;
}


void Node::setNext(Node* node)
{
   next = node;
}

/*********************************************************************
* List::List
* Default constructor for the list class
********************************************************************/
List::List()
{
   //set first node to null
   firstNode = NULL;

   //set the number of items to one
   numItems = 0;  
}

/*********************************************************************
* List::~List
* Destructor for the list class
********************************************************************/
List::~List()
{
   //loop through list and remove each node
   while (numItems > 0)
      remove(0);
}

/*********************************************************************
* List::List
* List copy constructor
********************************************************************/
List::List(const List &listToCopy)
{
  firstNode = NULL;
  numItems = 0;

   //get num items in list to copy
   int listItems = listToCopy.numItems;
   
   //copy the rhs list to the new list 
   for (int i = 0; i < listItems; i++)
      insert(listToCopy.getData(i),i);
}

/*********************************************************************
* List::operator=
* Assignment operator. The assignment operator copies the content
* of one list class to another.
********************************************************************/
List& List::operator= (const List &rightSide)
{
   //delete the lhs list
   int listItems = this->numItems;
   for (int i = 0; i < listItems; i++)
   {
      this->remove(0);
   }
   
   //copy the rhs list to the new list 
   for (int i = 0; i < rightSide.numItems; i++)
   {
      this->insert(rightSide.getData(i),i); 
   }
}
/*********************************************************************
* List::Insert
* insert inserts an integer into the specified position
********************************************************************/
void List::insert(int item, int pos)
{
   //create the new node
   Node *newNode = new Node;
   newNode->setData(item);

   //if we are inserting to first position
   if (!pos)
   {
      //New node's next points to old head
      newNode->setNext(firstNode);

      //point to the new head
      firstNode = newNode;
   }
   
   else //if not the first position.
   {
      Node *pNode = firstNode; //new nodes prev node
      int count = 1; 

      //while the next node is not null and we have not reached pos
      while (pNode->getNext() && count < pos)
      {
         //increment pNode and the count
         pNode = pNode->getNext();
         count++;
      }
      
      //set new nodess next node
      newNode->setNext(pNode->getNext());

      //set the new node's previous node to point ot it
      pNode->setNext(newNode);
   }
   numItems++;
}

/*********************************************************************
* List::remove
* remove removes a node from the list at the specified position
********************************************************************/
void List::remove(int pos)
{
   //if we are deleting head node
   if (!pos)
   {
      //make a temp pointer to first node
      Node *tempNode = firstNode;

      ///adjust the firstnode pointer
      firstNode = firstNode->getNext();

      //delete the old first node
      delete tempNode;
   }
   else //if not the first position.
   {
      //get to the node right before the one to delete
      Node *pNode = firstNode;
      for (int i = 0; i < pos - 1; i++)
      {
         if (pNode->getNext()->getNext() == NULL)
            break;
         pNode = pNode->getNext();
      }

      //create temp node
      Node *tempNode = pNode->getNext();

      //set the node of the next pointer
      pNode->setNext(tempNode->getNext());

      //delete the specified node
      delete tempNode;
   }
   numItems--;
}

/*********************************************************************
* List::lookup
* gien an integer, lookup finds the index of that integer in the list
********************************************************************/
int List::lookup(int item) const
{
   int position = 0; //index of item

   //loop through list
   for (Node *pNode = firstNode; pNode; pNode = pNode->getNext())
   {
      //if current node's data is the item
      if (pNode->getData() == item)
         break;
      position++;
   }

   //return position
   if (position >= numItems)
      return -1;
   return position;
}

/*********************************************************************
* List::getData
* This function gets the integer value at the specified node in the 
* list
********************************************************************/
int List::getData(int pos) const
{
   Node *pNode = firstNode; //new nodes prev node
   int count = 0; 

   //while the next node is not null and we have not reached pos
   while (pNode->getNext() && count < pos)
   {
      //increment pNode and the count
      pNode = pNode->getNext();
      count++;
   }

   //return the data of the node at index
   return pNode->getData();
}

/*********************************************************************
* List::empty
* This function tests if the list is empty
********************************************************************/
int List::empty(void) const
{
   return numItems != 0;
}

/*********************************************************************
* List::getNumItems
* This function returns the number of items in a list
********************************************************************/
int List::getNumItems(void) const
{
   return numItems;
}
