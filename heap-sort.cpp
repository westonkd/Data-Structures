/***********************************************************************
* Author:
*  Weston Dransfield
* Summary:
*  Uses a stack to convert infix to postfix and output assembly
***********************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

/*********************************************************************
* percolateDown
* function percolates down beginning at root and goint for numItems
*********************************************************************/
void percolateDown(vector<int> & data, int root, int numItems)
{
	//set the left child
	int leftChild = 2 * root;

	while (leftChild <= numItems)
	{
		//if root has two children and right child is larger
		if (leftChild < numItems && data[leftChild] < data[leftChild + 1])
			leftChild++; //increment leftChild

		//if parent filas heap-order condition
		if (data[root] < data[leftChild])
		{
			//swap root and leftchild
			int temp = data[root];
			data[root] = data[leftChild];
			data[leftChild] = temp;

			//set root to left child
			root = leftChild;

			leftChild = 2 * leftChild;
		}
		//else finished
		else
			return;
	}
}

/*********************************************************************
* Heapify
* function transforms given vector into a heap
*********************************************************************/
void heapify(vector<int> & data)
{
	//loop through vector beginning at last nonleaf
	for (int root = data.size() / 2; root > 0; root--)
	{
		percolateDown(data, root, data.size());
	}
}

/*********************************************************************
* heapSort
* uses a heap sort to sort data in the vector in ascenading order
*********************************************************************/
void heapSort(vector<int> & data)
{
	//make the vector a heap
	heapify(data);

	for (int i = data.size(); i > 1; i--)
	{
		//do a root-leaf exchange (swap data[1] and data[i])
		int temp = data[1];
		data[1] = data[i];
		data[i] = temp;

		//"prune" leaf and percolate down
		percolateDown(data, 1, i - 1);
	}	
}

/*********************************************************************
 * display
 * display the sorted list
 ********************************************************************/
void display(vector<int> & data)
{
	//loop through and display data items
	for (int i = 2; i <= data.size(); i++)
	{
		cout << data[i] << " ";
	}
	
	cout << endl;
}

/*********************************************************************
 * readFile
 * read the file
 ********************************************************************/
bool readFile(vector<int> & data, const string fileName)
{
	//open the file
   ifstream fin(fileName.c_str());
   if (fin.fail())
      return false;

   //fill first entry
   data.push_back(-1);

   //read the file into the heap
   int temp;
   while (fin >> temp)
   {
      data.push_back(temp);
   }

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
   vector<int> data;      //vector for data

   //process the file
   switch(argc)
   {
    case 1:
      cout << "Enter a file: ";
      cin >> fileName;
      break;
    case 2:
      fileName = argv[1];
      break;
    default:
      cout << "Too many Arguments\n"
           << "Usage is: a.out <file name>\n";
   }
   
   //read the file
   readFile(data, fileName);

   //sort the data
   heapSort(data);

   //display the file
   display(data);

   return 0;
}