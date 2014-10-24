/***********************************************************************
* Author:
*  Weston Dransfield
* Summary:
*  Uses a stack to convert infix to postfix and output assembly
***********************************************************************/
#include <iostream>
#include <string>
#include <map>
#include <stdio.h>
#include <fstream>
#include <iomanip>

using namespace std;

/*********************************************************************
 * process File
 * This function places all words in the given file into a map and
 * counts their occurences. all puncuation is removed except for
 * '-'.
 ********************************************************************/
int processFile(map<string,int> &words, string fileName)
{
  string word;          //holds words as they are added
  int count = 0;        //number of words processed
  
  //open the file
  ifstream fin(fileName.c_str());
  if (fin.fail())
    {
      cout << "Error: cannot open \"" << fileName << "\"\n";
      return 0;
    }
  
  while (fin >> word)
    {
      string processedWord = ""; //holds words with all punctuation removed

      //make the word lowercase and remove punctution
      for (int i = 0; i < word.size(); i++)
	     {
	        //make all chars lowercase
	        if (isalpha(word[i]) || word[i] == '-')
	           processedWord += tolower(word[i]);
	     }
      //add the work to the map and/or increment count
      words[processedWord]++;
      count++;
    }

  fin.close();
  return count;
}

/*********************************************************************
* displayTop
* This function takes a map by reference and displays the top 100
* entries
********************************************************************/
void displayTop(map<string,int> & words)
{
   //loop 100 times
   for (int i = 0; i < 100; i++)
   {
      int largestValue = 0;                 //largest value 
      map<string,int>::iterator largestEntry; //for largest key

      //loop through and find the largest
      for (map<string,int>::iterator it = words.begin();
            it != words.end();
            it++)
         {
            //if current entry is larger 
            if (it->second > largestValue)
            {
               largestEntry = it;
               largestValue = it->second;
            }
         }
      //display, then remove
      cout << setw(23) << largestEntry->first << " - " << largestEntry->second << endl;
      words.erase(largestEntry);
   }
}

/*********************************************************************
 * main
 * main calls all other functions in there correct order.
 ********************************************************************/
int main(int argc, char **argv)
{ 
   string fileName;       //string for filename
   map<string, int> words; //map for words and word count
   int count;             //number of words processed

   //process the file
   switch(argc)
   {
    case 1:
      cout << "Enter a file: ";
      cin >> fileName;
      count = processFile(words, fileName);
      break;
    case 2:
      count = processFile(words, argv[1]);
      break;
    default:
      cout << "Too many Arguments\n"
           << "Usage is: a.out <file name>\n";
   }
   
   //display the top 100 entries
   cout << "\nNumber of words processed: " << count << endl
        << "100 most common words found and their frequencies:\n";
   displayTop(words);     
}
