/**************************************************************
* Author:
*  Weston Dransfield
* Summary:
*  This file contains the definition and implementation of a 
*  stack class.
***************************************************************/
#include "stack.h"
#include <stdlib.h>

using namespace std;

/**************************************************************
* Stack constructor
* initializes member vars in Stack class
**************************************************************/
Stack::Stack(int size) : maxSize(size), myTop(-1)
{
	stackItems = new int[size];
}   

/*************************************************************
* Stack copy constructor
* Correctly makes a copy ofthe stack class
*************************************************************/
Stack::Stack(const Stack &aStack)
{
	//copy simple variables
	maxSize = aStack.maxSize;
	myTop = aStack.myTop;

	//copy the data
	int *newData = new int[maxSize];
	for(int i = 0; i <= myTop; i++)
		newData[i] = aStack.stackItems[i];

	//adjust the pointer
	stackItems = newData;
} 

/*************************************************************
* Stack top
* returns the value at the top of the stack 
* but does not pop it off the stack.
**************************************************************/
int Stack::top(void)
{
   //if array is empty display an error message
	if(myTop < 0)
   {
      cout << "ERROR: Stack Empty\n";
      exit(1);
   }
   //return the desired values
   return stackItems[myTop];
}  

/*************************************************************
* Stack push
* puts a value onto the top of the stack. Program will exit 
* if it tries to push a value onto a full stack
**************************************************************/
void Stack::push(int item)
{
   //Is there room?
   if(myTop >= maxSize - 1)
   {
      cout << "ERROR: Stack Overflow\n";
      exit(1);
   }

   //push new value onto the stack
   stackItems[myTop + 1] = item;

   //increment the head
   ++myTop;
}  

/*************************************************************
* Stack Pop
* pops off the top element of the stack but does not
* return the value. Program will exit if it tries to pop 
* off a value from an empty stack
**************************************************************/
void Stack::pop(void)
{
   //check if the stack is empty
   if(myTop < 0)
   {
      cout << "ERROR: Stack Underflow\n";
      exit(1);
   }
   //move the top of the stack.
   --myTop;
}  

/*************************************************************
* Stack empty
* function that checks if the stack is empty. Function 
* should return true if the stack is empty, false otherwise.
**************************************************************/
bool Stack::empty(void)
{
  	//if the stack is empty?
   return (myTop < 0) ? true : false;
}  

/*************************************************************
* Stack full
* a function that checks if the stack is full. Function should
* return true if the stack is full, false otherwise.
**************************************************************/
bool Stack::full(void)
{
   //check if the stack is full
   return (myTop + 1 >= maxSize) ? true : false;
}

/*************************************************************
* Stack destructor
* frees memory taken by stackItems
**************************************************************/
Stack::~Stack()
{
   //free the memory
   delete [] stackItems;
}  

/*************************************************************
* Stack assignment operator
* assigns one stack to another
**************************************************************/
Stack& Stack::operator = (const Stack &rtSide)
{
   //copy simple variables
   maxSize = rtSide.maxSize;
   myTop = rtSide.myTop;

   //copy the data
   int *newData = new int[maxSize];
   for(int i = 0; i <= myTop; i++)
      newData[i] = rtSide.stackItems[i];

   //adjust the pointer
   delete [] stackItems;
   stackItems = newData;
	return *this;
} 