/**************************************************************
* Author:
*  Weston Dransfield
* Summary:
*  This file contains the definition and implementation of a 
*  set class.
***************************************************************/
#include <iostream>
#include <cassert>
#include <cstring>
#include <new>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <iomanip>

using namespace std;

#define MIN_SET_SIZE 16

/***************************************************************
* Set class
* This class is the abstraction of a set. The set contains an 
* array to store data as well as methods to operate on that data
* Set class has no order or duplicate entries.
***************************************************************/
class Set
{
public:
  //Constructors and Destructor
  Set() : capacity(0), numElements(0) {}; 
  Set(int size);              //constructor
  Set(const Set & object);    //copy constructor
  ~Set();                     //set destructor frees memory

  //Public Member Fucntions
  void insert(const int newEntry);              //add new entry to the set
  int size()const        {return numElements;}  //get the size of the set
  int getCapacity()const {return capacity;   }  //get the capacity of set
  bool isPresent(const int intToCheck)const;    //check if integer is in set
  void display();                         //display the set
  void sort();                                  //sort the array

  //Overloaded operators
  Set & operator&&(Set & rhs);       //Intersection
  Set & operator||(Set & rhs);       //Union
  Set & operator -(Set & rhs);       //Difference
  Set & operator =(const Set & rhs); //assignment
private:
  //private variables
  int *pArray;     //pointer to dynamically allocated array of ints
  int numElements; //variable to hold number of elements in set
  int capacity;    //variable to keep track of capacity of set
};

/**************************************************************
 *******************Operator Overloading***********************
 *************************************************************/

 /************************************************************
 * operator &&
 * Intersection
 * This function returns a new set which contains the data
 * entries of two combined sets. The new set contains no 
 * duplicates
 ************************************************************/
Set & Set::operator&&(Set & rhs)
{
   //create the new set
  Set *intersection = new Set;

  //loop through the array and insert entries found in both
  for(int i = 0; i < numElements; i++)
    if(rhs.isPresent(pArray[i]))
      intersection->insert(pArray[i]);

   //return the new set
  return *intersection;
}

/************************************************************
 * operator ||
 * Union
 * This function returns a new set which contains the data
 * entries found in both sets. The new set contains no 
 * duplicates
 ************************************************************/
Set & Set::operator||(Set & rhs)
{
   //create new set
  Set *pSet = new Set;

  //add data from the LHS set
  for(int i = 0; i < numElements; i++)
    pSet->insert(pArray[i]);

  //add data from the RHS set
  for(int i = 0; i < rhs.size(); i++)
    pSet->insert(rhs.pArray[i]);

  //return the new set
  return *pSet;
}

/************************************************************
 * operator -
 * difference
 * This function returns a new set which contains the data
 * entries that were only found in one or the other set.
 ************************************************************/
Set & Set::operator -(Set & rhs)
{
   //create the new set
  Set *difference = new Set;

  //check first set
  for(int i = 0; i < numElements; i++)
    {
      if(!rhs.isPresent(pArray[i]))
        difference->insert(pArray[i]);
    }

  return *difference;
}

/************************************************************
 * operator =
 * Assignment
 * This function correctly assigns one set to another.
 ************************************************************/
Set & Set::operator =(const Set & rhs)
{
  //if they are the same, don't do anything
  if(this == &rhs)
    return *this;

  //copy data of object being coppied
  int *newArray = new int[rhs.capacity];
  for(int i = 0; i < rhs.numElements; i++)
    newArray[i] = rhs.pArray[i];

  //delete the old array
  if(numElements > 0)
    delete [] pArray;

  //copy the size and capacity
  numElements = rhs.numElements;
  capacity = rhs.capacity;

  //adjust the pointer
  pArray = newArray;
  return *this;
}

/************************************************************
 * operator <<
 * Extraction
 * This function simply calls the Set's display() memthod
 ************************************************************/
ostream & operator << (ostream & out, Set & set)
{
   //display the set
  set.display();
  return out;
}

/***************************************************************
 ************************Constructors***************************
 **************************************************************/

/***************************************************************
 * Set non-default constructor
 * This constructor is used when the user specifies a size for
 * the new set
 **************************************************************/
Set::Set(int size) : numElements(0), capacity(size * 2)
{
  //create the new array for the set
  pArray = new int[size * 2];
}

/***************************************************************
 * Copy Constructor
 * This function correctly 
 * makes a copy of the set
 * class
 **************************************************************/
Set::Set(const Set & object)
{
  *this = object;
}

/***************************************************************
 * Destructor
 * This function frees the
 * data used in the Set class
 **************************************************************/
Set::~Set()
{
  delete [] pArray;
}

/***************************************************************
 **********************Member Fucntions*************************
 ***************************************************************/

/***************************************************************
 * sort
 * This function sorts the set into ascending order
 * using a simple bubble sort algorithm
 **************************************************************/
void Set::sort()
{
  int indexOfMin;
  int pass;
  int j;

  //loop through array, swap elements if larger
    for (pass = 0; pass < numElements - 1; pass++)
    {
            indexOfMin = pass;

            for (j = pass + 1; j < numElements; j++)
                if (pArray[j] < pArray[indexOfMin])
                    indexOfMin = j;
            //swap 
            int temp;
            temp = pArray[pass];
            pArray[pass] = pArray[indexOfMin];
            pArray[indexOfMin] = temp;
    }
}


/**************************************************************
 * Set display
 * This function displays the contents of the set class in 
 * ascending order. 
 **************************************************************/
void Set::display()
{
   //sort the set
   sort();

   //loop through the array 
   for(int i = 0; i < numElements; i++)
   {
      //start a new line every 10 items
      if(!(i % 10) && i != 0)
         cout << endl;
      cout << setw(4) << pArray[i];
   }
}

/***************************************************************
 * insert
 * This function adds an entry to the set without duplicates.
 * It also alocates a new array if the current set is too
 * small to fit more data
 **************************************************************/
void Set::insert(const int newEntry)
{
  //if the set is empty
  if(numElements == 0)
    {
      try
        {
          //allocate a new array
          pArray = new int[MIN_SET_SIZE];
        }
      catch (bad_alloc error)
        {
          cout << "Error: " << error.what();
        }
      //insert the new entry
      pArray[0] = newEntry;

      //update the capacity
      capacity = MIN_SET_SIZE;
    }
  else if(isPresent(newEntry)) //don't add duplicates
    {
      return;
    }
  else if(numElements < capacity) //if we have room
    {
      //add the entry
      pArray[numElements] = newEntry;
    }
  else if(numElements + 1 > capacity) //if not enought room
    {
      //create a new array
      int *newArray = new int[capacity * 2];
            
      //copy old array to the new
      memcpy(newArray, pArray, capacity * sizeof(int));
      newArray[numElements] = newEntry;
      
      //delete old array and adjust the poiner
      delete [] pArray;
      pArray = newArray;
    
      //adjust the capacity
      capacity *= 2;
    }

  //increment numElments and update capacity
  numElements++;
}

/***************************************************************
 * isPresent
 * This function tests if an entry is
 * already present in the set
 **************************************************************/
bool Set::isPresent(const int intToCheck)const
{
   //loop through all elements and see if present
   for(int i = 0; i < numElements; i++)
      if(pArray[i] == intToCheck)
         return true;     //element is present
   return false;          //element is not present 
}

/***************************************************************
 * readFile
 * This function reads the contents of a file into two seperate
 * sets.
 **************************************************************/
void readFile(string fileName, Set & setOne, Set & setTwo)
{
   //create the input file stream
  ifstream fin(fileName.c_str());
    if(fin.fail())
      {
         //display error message if there are problems
        cout << "Error: could not read \"" 
             << fileName << "\"\n";
        exit(1);
      }

   int numElements; //Number of entries in new set
   int temp;        //temporary variable for reading file

   //read in the first set
   fin >> numElements;
   for(int i = 0; i < numElements;i++)
   {
      fin >> temp;
      setOne.insert(temp);
   }
 
   //read in the second set
   fin >> numElements;
   for(int i = 0; i < numElements;i++)
   {
      fin >> temp;
      setTwo.insert(temp);
   }

  fin.close();
}
/***************************************************************
 * Main
 * Main prompts the user for a file name and then exercises the
 * set class
 ***************************************************************/
int main(int argc, char **argv)
{
  string fileName; //for the file name
  Set setOne;
  Set setTwo;

  switch(argc)
    {
    case 1:
      cout << "Enter a file: ";
      cin >> fileName;
      readFile(fileName,setOne,setTwo);
      break;
    case 2:
      readFile(argv[1],setOne,setTwo);
      break;
    default:
      cout << "Too many Arguments\n"
           << "Usage is: a.out <file name>\n";
    }
  
   //dispaly the sets
   cout << "Set A:\n" << setOne << endl << endl
        << "Set B:\n" << setTwo << endl << endl;

   //exercise the operators!
    Set setThree;
    setThree = setOne && setTwo;
    cout << "Intersection of A and B:\n" 
         << setThree << endl << endl;

   //union
   setThree = setOne || setTwo;
   cout << "Union of A and B:\n" 
         << setThree << endl << endl;

   //difference
   setThree = setOne - setTwo;
   cout << "Difference of A and B:\n" 
         << setThree << endl << endl;

         //difference
   setThree = setTwo - setOne;
   cout << "Difference of B and A:\n" 
         << setThree << endl << endl;
  
   return 0;
}
