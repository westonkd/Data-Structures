/***********************************************************************
* Author:
*  Weston Dransfield
* Summary:
*  This program creates a list of nodes linked together by pointers 
*  which contain data read from a file.
***********************************************************************/
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <list>

#define TABLE_SIZE 67

using namespace std;

/*********************************************************************
 * hash
 * This function reads the words of a file and inserts them into
 * the hash table
 ********************************************************************/
int hash(string word)
{
  int position = 0; //insertion point

  //add up the ascii values of all letters in word
  for (int i = 0; i < word.length(); i++)
    position += word[i];

  //return the position to insert
  return position % TABLE_SIZE;
}

/*********************************************************************
 * readFile
 * This function reads the words of a file and inserts them into
 * the hash table
 ********************************************************************/
bool readFile(string fileName,list<string> hashTable[])
{
  //open the file
  ifstream fin(fileName.c_str());
  if (fin.fail())
    return false;

  string temp; //temp string for words in file
  while (fin >> temp)
      hashTable[hash(temp)].push_back(temp); 

  //close the file
  fin.close();
  return true;
}

/*********************************************************************
 * readFile
 * This function recursivly displays the contents of each list in the
 * hash table
 ********************************************************************/
void display(list<string> hashTable[], int index)
{
   //base case
   if (index == TABLE_SIZE)
      return;

   //display the label
   cout << "table[" << index << "]"
        << (index < 10 ? " -> " : "-> ");

   //if the list is empty
   if (hashTable[index].empty())
      cout << "(empty)";
   //if the list has one entry
   else if (hashTable[index].size() == 1)
      cout << hashTable[index].front();
   //if the list has more than one entry
   else
   {
      list<string>::iterator it = hashTable[index].begin();
      for (it; it != hashTable[index].end();)
      {
         cout << *it;

         //if it is not the last entry, output a comma
         if (++it != hashTable[index].end())
            cout << ", ";
      }
   }

   cout << endl;

   display(hashTable, index + 1);
}
/*********************************************************************
 * main
 * main gets the file name from the user and reads in a file of
 * random numbers into a linked list.
 ********************************************************************/
int main(int argc, char **argv)
{ 
   string fileName;    //holds the file name
   list<string> hashTable[TABLE_SIZE]; //table of lists 

   //read the file
   switch(argc)
    {
    case 1:
      cout << "Enter a file: ";
      cin >> fileName;
      readFile(fileName, hashTable);
      break;
    case 2:
      readFile(argv[1], hashTable);
    default:
         ;
    }

    //display the hash table
    display(hashTable,0);
   return 0;
}
