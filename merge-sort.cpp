/***********************************************************************
* Author:
*  Weston Dransfield
* Summary:
*  Uses a stack to convert infix to postfix and output assembly
***********************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <list>

using namespace std;

void display(list<int> & listToSort)
{
   for (list<int>::iterator it = listToSort.begin();
	it != listToSort.end();
	it++)
     cout << *it << " ";
}

/*********************************************************************
 * merge
 * performs the merge algorithm for natural mergesort
 ********************************************************************/
int merge(list<int> & listToSort, list<int> & listOne, list<int> & listTwo)
{
  int numSubFiles = 0;
  list<int> sortedList;

  //iterators for lists to be merged
  list<int>::iterator itOne = listOne.begin();
  list<int>::iterator itTwo = listTwo.begin();
  
  //iterators for next value in lists
  list<int>::iterator itNextOne = listOne.begin();
  list<int>::iterator itNextTwo = listTwo.begin();

  itNextOne++;
  itNextTwo++;
 
  while (itOne != listOne.end() && itTwo != listTwo.end())
    {
      //while we have not hit end of a subfile in L1 or L2
      do
	{
	  if (*itOne <= *itTwo)
	    sortedList.push_back(*itOne);
	  else
	    sortedList.push_back(*itTwo);

	  //increment iterators
	  itNextOne++;
	  itNextTwo++;
	  itOne++;
	  itTwo++;
	}
      while ((*itOne < *itNextOne) && (*itTwo < *itNextTwo));

      if (*itOne > *itNextOne)
	{
	  do
	    {
	      sortedList.push_back(*itOne);
	      itOne++;
	      itNextOne++;
	    }
	  while (*itOne < *itNextOne);
	}
      else
	{
	   do
	    {
	      sortedList.push_back(*itTwo);
	      itTwo++;
	      itNextTwo++;
	    }
	  while (*itTwo < *itNextTwo);
	}
	
      //increment subfile count
      numSubFiles++;
    }

  cout << *itOne << endl;

  //copy any remaining sublists

  display(sortedList);
  
  listToSort = sortedList;
  return numSubFiles;
}

/*********************************************************************
 * split
 * performs the split operation for the natural mergesort
 ********************************************************************/
void split(list<int> & listToSplit, list<int> & listOne, list<int> & listTwo)
{
  //iterate over the list to sort
  list<int>::iterator it = listToSplit.begin();
  
  bool isNewPass = true;

  while(it != listToSplit.end())
    {
      //copy sorted subfiles into list one
      while ((*it > listOne.back() || isNewPass) && it != listToSplit.end())
	{
	  listOne.push_back(*it);
	  it++;
	  isNewPass = false;
	}
      
      //set as new pass
      isNewPass = true;

      //copy subfiles into list two
      while ((*it > listTwo.back() || isNewPass) && it != listToSplit.end())
	{
	  listTwo.push_back(*it);
	  it++;
	  isNewPass = false;
	}
    
      //set as new pass
      isNewPass = true;
    }
}

/*********************************************************************
 * mergeSort
 * Sorts items in a list using a mergesort
 ********************************************************************/
void mergeSort(list<int> & listToSort)
{
  list<int> listOne; //used to store splited list
  list<int> listTwo; //used to store splited list
  int subFiles = 10;

  while (subFiles > 1)
    {
      split(listToSort, listOne, listTwo);
      subFiles =  merge(listToSort, listOne, listTwo);
    }
}


/*********************************************************************
 * readFile
 * reads file of integers into a linked list
 ********************************************************************/
bool readFile(string fileName, list<int> & listToSort)
{
  //open the file
  ifstream fin(fileName.c_str());
  if (fin.fail())
    return false;
  
  //read the data
  int temp;
  while (fin >> temp)
    listToSort.push_back(temp);

  //close the file
  fin.close();
  return true;
}

/*********************************************************************
 * main
 * main calls all other functions in there correct order.
 ********************************************************************/
int main(int argc, char **argv)
{ 
   string fileName;       //string for filename
   list<int> listToSort;   //the list of numbers to sort

   //process the file
   switch(argc)
   {
    case 1:
      cout << "Enter a file: ";
      cin >> fileName;
      readFile(fileName, listToSort);
      break;
    case 2:
      readFile(argv[1], listToSort);
      break;
    default:
      cout << "Too many Arguments\n"
           << "Usage is: a.out <file name>\n";
   }
   mergeSort(listToSort);
}
