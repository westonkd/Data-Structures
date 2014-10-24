/***********************************************************************
* Author:
*  Weston Dransfield
* Summary: 
*  This program uses a doubly linked list to compute the nth 
*  Number in the Fibonacci sequence
***********************************************************************/

#include <iostream>
#include <cassert>
#include <stdlib.h>  
#include <math.h>

#define MAX_DIGITS 1000000000

using namespace std;


/*****************************************************************************
* Node class definition for building a single linked list of integers.
*****************************************************************************/
class Node
{
   private:
      int data;                 // --- data in each node
      Node* next;               // --- pointer to next node
      Node* prev;               // --- pointer to previous node

   public:
      Node();                   // --- Creates empty node
      Node* getNext();          // --- returns next pointer of a node
      Node* getPrev();          // --- returns the previous pointer
      int getData();            // --- returns data of a node
      void setData(int item);   // --- stores item in data member of current node
      void setNext(Node* node); // --- sets next to point to node
      void setPrev(Node* node); // --- sets previous to point to node
};

/**********************************************************************************
* This class provides a dynamically allocated linked list implementation of a
* general list. It includes functions for creating, copying, and destroying a
* linked list data structure. It includes functions for inserting, removing,
* and retrieving data anywhere in the linked list data structure.
**********************************************************************************/
class List
{
   private:
      int numItems;
      Node* firstNode;
      Node* getNode(int pos);

   public:
      List();
      ~List();                       // destructor - free the entire linked list 
      List(const List &listToCopy);  // copy constructor
      List& operator = (const List &rightSide);
      void insert(int item, int pos); // insert item at the specified position
      void remove(int pos);          // remove item at the specified position
      int lookup(int item) const;    // returns position of item (zero relative)
      int getData(int pos) const;    // returns data located at the position
      int empty(void) const;         // check for empty list(0=empty 1=not empty)
      int getNumItems(void) const;   // return # of items in the linked list
      void add(List & toAdd);  // adds two lists together
      void display() const;
};

/*********************************************************************
 * Node::getNext
 * This function returns the next opinter of a node in a linked list
 ********************************************************************/
Node::Node()
{
   //create an empty node
   data = 0;
   next = NULL;
   prev = NULL;
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
 * Node::getPrev
 * This function returns the previous opinter of a node in a linked list
 ********************************************************************/
 Node* Node::getPrev()
 {
   if (this == NULL)
      return this;
   //return the next pointer
   return prev;
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

/*********************************************************************
 * Node::setNext
 * Sets the next pointer
 ********************************************************************/
void Node::setNext(Node* node)
{
   next = node;
}

/*********************************************************************
 * Node::setPrev
 * Sets the previous pointer
 ********************************************************************/
void Node::setPrev(Node* node)
{
   prev = node;
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

      //Old head's previous points to new node
      if (firstNode)
         firstNode->setPrev(newNode);

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
      
      //set newNode's previous pointer
      newNode->setPrev(pNode);

      //set new nodes next node
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

      //adjust the firstnode pointer
      firstNode = firstNode->getNext();

      //adjust the following node's previous pointer
      if (firstNode->getNext())
         firstNode->getNext()->setPrev(firstNode);

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

      //adjust the previous pointer
      if (tempNode->getNext())
         tempNode->setPrev(pNode);

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

/*********************************************************************
* List::add
* This function takes one list by reference and adds it to the 
* calling list
********************************************************************/
void List::add(List & toAdd)
{
   //get to the end of the list
   Node *pNode = firstNode;
   while (pNode->getNext())
      pNode = pNode->getNext();

   Node *pNodeToAdd = toAdd.firstNode;
   while (pNodeToAdd->getNext())
      pNodeToAdd = pNodeToAdd->getNext();

   for (pNode; pNode; pNode = pNode->getPrev(), pNodeToAdd = pNodeToAdd->getPrev())
   {
      //add and mod
      int newValue = (pNode->getData() + pNodeToAdd->getData());

      //record new value
      pNode->setData(newValue % MAX_DIGITS);

      //if we need to carry 
      if (newValue % MAX_DIGITS != newValue)
      {
         int nextData = 0;
         if (pNode->getNext())
            nextData = pNode->getNext()->getData();

         //if we don't need to insert
         if (pNode->getNext() && ((nextData + newValue / MAX_DIGITS) % MAX_DIGITS) != (nextData + newValue))
         {
            pNode->getNext()->setData(nextData + newValue / MAX_DIGITS);
         }
         else
         {
            //insert a new node to both lists
            insert(newValue / MAX_DIGITS, numItems);
            toAdd.insert(0, numItems);
         }
      }
   }
}

/*********************************************************************
* List::getNode
* Private function to access a node at point pos
********************************************************************/
Node* List::getNode(int pos)
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
   return pNode;
}

/*********************************************************************
* displayFib
* This function displays a list as one number 
********************************************************************/
void List::display() const
{
   //get to the end of the list
   Node *pNode = firstNode;
   while (pNode->getNext())
      pNode = pNode->getNext();

   //iterate backwards through the list
   for (pNode; pNode; pNode = pNode->getPrev())
   {
      int num = pNode->getData();

      //if we are not on the first node to print
      if (pNode->getNext())
      {
         //check the lenght of the int to pring
         int len = num > 0 ? (int) log10((double) num) + 1 : 1;

         //fill in spaces with '0'
         for (int i = 0; i < 9 - len; i++)
            cout << 0;
      }
      cout << num;
   }
}

/*********************************************************************
* computeFib
* This function takes a number as a paramater. It then
* computes the fibbonaci number specified.
********************************************************************/
void computeFib(string n)
{
   //convert number to int
   int number = atoi(n.c_str());
   
   //Lists to compute number with
   List *listOne = new List();
   List *listTwo = new List();

   //set the value of one and two to one
   listOne->insert(1,0);
   listTwo->insert(1,0);

   for (int i = 2; i < number; i++)
   {
      //create a temp pointer
      List *pTemp = listOne;

      //switch the lists
      listOne = listTwo;
      listTwo = pTemp;

      listOne->add(*listTwo);
   }

   //display the number
   listOne->display();
   cout << endl << endl;

   //delete the lists
   delete listOne;
   delete listTwo;
}

/*********************************************************************
* Main
* Main takes a number off the command line or promts the user
* for one if none is given. The number is then passed to a function
* to compute a Fibbonaci number.
********************************************************************/
int main(int argc, char **argv)
{ 
   string number;    //holds the number

   //read the file
   switch(argc)
    {
    case 1:
      cout << "Enter a number: ";
      cin >> number;
      computeFib(number);
      break;
    case 2:
      computeFib(argv[1]);
      break;
    default:
      cout << "Error: usage is " << argv[0] << " <number>\n";
    }

   return 0;
}
