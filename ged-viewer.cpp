/***********************************************************************
* Author:
*  Weston Dransfield
* Summary:
*  displays a ged file
***********************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>
#include <stdlib.h>
#include <iomanip>

#define CURRENT_YEAR 2013

using namespace std;

/***********************************************************
***************************Date Class***********************
***********************************************************/
class Date
{
private:
	int day;
	int month;
	string monthName;
	int year;
public:
	Date();
	//getters
	int getDay() {return day;}     //get the day
	int getMonth() {return month;} //get the month
	int getYear() {return year;}   //get the year
	string getMonthName() {return monthName;}

	//setters
	int setDay(int day);
	int setMonth(int month);
	int setMonth(string month);
	int setYear(int year);

	//operators
	bool operator < (Date & rhs);
};

/*********************************************************************
* Constructor for date class
**********************************************************************/
Date::Date()
{
	//set data
	this->day = 0;
	this->month = 0;
	this->year = 0;
}

/*********************************************************************
* Date setDay
* set the day of the date
********************************************************************/
int Date::setDay(int day)
{
	//make sure the date is valid
	if (day >0 && day < 32)
	{
		this->day = day;
		return day;
	}
	return 0;
}

/*********************************************************************
* Date setMonth
* set the day of the date
********************************************************************/
int Date::setMonth(int month)
{
	string months[13] = {"", "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
                         "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};

	//make sure valid month, then set it
	if (month > 0 && month < 13)
	{
		this->month = month;
		this->monthName = months[month];
		return month;
	}
	return 0;
}

/*********************************************************************
* Date setYear
* set the year of the date
********************************************************************/
int Date::setYear(int year)
{
	//check if year is valid
	if (year > 0 && year <= CURRENT_YEAR)
	{
		this->year = year;
		return year;
	}
	return false;
}

/***************************************************************
* Date setMonth (string)
* set the month from a string (ie dec or JAN)
***************************************************************/
int Date::setMonth(string month)
{
	int monthNum;
	string months[13] = {"", "JAN", "FEB", "MAR", "APR", "MAY", "JUN",
                         "JUL", "AUG", "SEP", "OCT", "NOV", "DEC"};
	//make the month upper-case
	for (int i = 0; i < month.size(); ++i)
		month[i] = toupper(month[i]);

	//set the number
	for (int i = 1; i < 13; i++)
	{
		if (months[i] == month)
		{
			//set the month in the class
			this->month = i;
			this->monthName = month;
			return i;
		}
	}

	//failed
	return 0;
}

/***************************************************************
* Date < operator
* compares two dates and returns a boolean value
***************************************************************/
bool Date::operator < (Date & rhs)
{
	//start with the year
	if (this->year < rhs.year)
		return true;
	if (this->year > rhs.year)
		return false;

	//move to month
	if (this->month < rhs.month)
		return true;
	if (this->month > rhs.month)
		return false;

	//if same year and month
	if (this->day < rhs.day)
		return true;
	else
		return false;
}

/***********************************************************
*********************Individual class***********************
***********************************************************/
class Individual
{
public:
	string givenName; //first name of individual
	string lastName;   //last name of individual
	string id;            //unique id for individual
	Date birthDate;    //date of birth

	//operators
	bool operator<(Individual & rhs);
};

/******************************************************
* overloaded << to handle individual class
******************************************************/
ostream & operator<<(ostream & out, Individual & rhs)
{
	//first name if given
	if (rhs.givenName != "")
		out << rhs.givenName;

	//last name if given
	if (rhs.lastName != "")
		if (rhs.givenName != "")
			out << " ";
		out << rhs.lastName;

	//output a birthdate?
	if (rhs.birthDate.getDay() == 0 && rhs.birthDate.getMonthName() == "" && rhs.birthDate.getYear() == 0)
		return out;

	//output lable
	out << ", b.";

	//output birthdate
	if (rhs.birthDate.getDay() != 0)
		out << " " << rhs.birthDate.getDay();

	if (rhs.birthDate.getMonthName() != "")
		out << " " << rhs.birthDate.getMonthName();

	if (rhs.birthDate.getYear() != 0)
		out << " " << rhs.birthDate.getYear();

	return out;
}
/*************************************************************
* alphaComp <
* compare two strings alphabeticly.
*************************************************************/
int alphaComp(string & lhs, string & rhs)
{
	//first check if last name is empty, if it is it gets
	//lower alpha priority

	//if lhs is empyt
	if (lhs.size() == 0)
		return 1;
	if (rhs.size() == 0)
		return 0;

	//find smallest last name
	string *smallest = NULL;

	if (lhs <= rhs)
		smallest = &rhs;
	else
		smallest = &lhs;

	//loop through smallest word and compare letters
	for (int i = 0; i < smallest->size(); ++i)
	{
		if (lhs[i] < rhs[i])
			return 1;
		if (lhs[i] > rhs[i])
			return 0;
	}

	//must be the same
	return 3;
}

/*************************************************************
* Individual::operator<
* compares individuals by
* 1) Last Name
* 2) Firt Name
* 3) Birthdate
**************************************************************/
bool Individual::operator<(Individual & rhs)
{
	//compare last names
	//if this < rhs
	if (alphaComp(this->lastName, rhs.lastName) == 1)
		return true;

	//if this > lhs
	if (alphaComp(this->lastName, rhs.lastName) == 0)
		return false;

	//compare first names
	//if this < rhs
	if (alphaComp(this->givenName, rhs.givenName) == 1)
		return true;

	//if this > rhs
	if (alphaComp(this->givenName, rhs.givenName) == 0)
		return false;

	//compare birthdays 
	//if this < rhs
	if (this->birthDate < rhs.birthDate)
		return true;
	else 
		//possibly same person 
		return false;
	
}

/***********************************************************
**************************BTree class***********************
***********************************************************/
class BTree
{
   private:
      Individual *data;          // --- data stored in node of tree
      BTree* left;       // --- pointer to left subtree
      BTree* right;      // --- pointer to right subtree
      BTree* parent;     // --- pointer to the parent node;

   public:
      BTree(Individual* data = NULL);  
      ~BTree(void);
      void insertLeft(Individual *item);     // creates a new node and inserts node to left
      void insertRight(Individual *item);    // creates a new node and inserts node to right
      BTree* getLeftChild(void);     // return the ptr to the left child
      BTree* getRightChild(void);    // return the ptr to the right child
      BTree* getParent(void);        // return parent
      Individual* getData(void);
      void setData(Individual* item);
      void setLeft(BTree* tree);     
      void setRight(BTree* tree);
      void infix(void);              // do infix traversal
      void prefix(void);             // do prefix traversal
      void postfix(void);            // do postfix traversal
      void level(void);              // do level order traversal
      BTree* lookUp(string id);
      void listDisp(void);
      bool isNextGen;
};

/*********************************************************************
* BTree Constructor
* Creates a BTree node with specified data
********************************************************************/
BTree::BTree(Individual* data)
{
   //set the data
   this->data = data;

   //set nodes to Null
   left = NULL;
   right = NULL;
   parent = NULL;
   isNextGen = false;
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
void BTree::insertLeft(Individual* item)
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
void BTree::insertRight(Individual* item)
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
Individual* BTree::getData(void)
{
   //return the data in the node
   return data;
}

/*********************************************************************
* BTree setData
* sets the data of current node
********************************************************************/     
void BTree::setData(Individual* item)
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
* BTree search
* search in infix pattern and return pointer to individual with given
* id;
********************************************************************/
BTree* BTree::lookUp(string id)
{
   if (left != NULL) 
      left->lookUp(id);
   if (left->getData()->id == id)
   	return left;
   if (right->getData()->id == id)
   	return right;
   if (right != NULL) 
      right->lookUp(id);
}  

/*********************************************************************
* BTree infix
* performs an infix visit of nodes and dispays each (LVR)
********************************************************************/
void BTree::infix(void)
{
   if (left != NULL) 
      left->infix();
   cout << *data << endl;
   if (right != NULL) 
      right->infix();
}  

/*********************************************************************
* BTree prefix
* performs a prefix visit of nodes and dispays each (VLR)
********************************************************************/
void BTree::prefix(void)
{
   cout << *data << endl;
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
   cout << *data << endl;
}    

/*********************************************************************
* BTree postfix
* performs a postfix visit of nodes and dispays each (LRV)
********************************************************************/   
void BTree::listDisp(void)
{
   BTree *pNode = this;
   while (pNode->getRightChild())
   {
   		cout << *(pNode->data) << endl;
   		pNode = pNode->getRightChild();
   }
}       

/*********************************************************************
* BTree Constructor
* Visits each node in the tree by level and prints each out
********************************************************************/
void BTree::level(void)
{
	string generations[8] = {
		"The Ancestors of Gregory Lawrence Cameron:",
		"Parents:",
		"Grandparents:",
		"Great Grandparents:",
		"2nd Great Grandparents:",
		"3rd Great Grandparents:",
		"4th Great Grandparents:",
		"5th Great Grandparents:"
	};

	int genCount = 0;
   const int MAX = 100;
   BTree *queue[MAX];
   BTree *temp;
   int front = 0;
   int back = 0;
   int prevBack = 0;

   //flag the new generations
   BTree *pNode = this;
   while (true)
   {
   	//flag first node in each level
   	pNode->isNextGen = true;

   	//first try to go left, if fail go right
  		if (pNode->getLeftChild()) 
  			pNode = pNode->getLeftChild();
		else if (pNode->getRightChild())
			pNode = pNode->getRightChild();
		else
			break;	
   }


   queue[back++] = this;

   while (front != back)
   {
      temp = queue[front];
      front = (front + 1) % MAX;
      if (temp != NULL)
      {
         // visit
         
         if (temp->isNextGen)
         {
         	//output the label
         	cout << generations[genCount] << endl;
         	genCount++;
         }

         if (genCount != 1)
         	cout << "\t\t" << *(temp->data) << endl;
        
         // end Visit        
         queue[back] = temp->left;
         back = (back + 1) % MAX;
         queue[back] = temp->right;
         back = (back + 1) % MAX;
    }
  }
}

/*********************************************************************
 * getIndiById
 * get and idividual by their ID number
 ********************************************************************/
BTree* getIndiById(string id, BTree* head)
{
	BTree *pNode = head;
   	while(pNode)
   	{
   		//check if ids are the same
   		if (pNode->getData()->id == id)
   			return pNode;

   		//advance the iterator
   	 	pNode = pNode->getRightChild();
   	}

   	//id not found, return null
   	cout << id << endl;
   	return head;
}

void treeSearch(BTree * head, string id, BTree* & item)
{
	//check the id
    if (id == head->getData()->id)
    {
    	item = head;
    }

    //go left and check
	if (head->getLeftChild() != NULL) 
	{
      treeSearch(head->getLeftChild(), id, item);
	}

	//go right and check
   	if (head->getRightChild() != NULL)
   	{ 
      treeSearch(head->getRightChild(), id, item);
    }
}

/*********************************************************************
 * parseFile
 * Parse the file and sort it into a list
 ********************************************************************/
BTree* parseFile(string fileName)
{
	fstream fin(fileName.c_str());
	if (fin.fail())
	{
		cout << "Error opening " << fileName << endl;
	}

	string temp; //for reading in the file
	Individual *newIndi; //for new individuals
	Individual *root;    //for root individual

	bool isRoot = true;  //indicates if it is the first individual
	bool isRootFam = true; //indicates if it is the first family

	BTree* treeRoot = NULL; //root of the tree
	BTree* head = NULL;  //head node
	BTree* newNode = NULL; //node for new individuals

	//loop through the file a line at a time
	while (getline(fin,temp))
		{	
			//if there is a new individual
			if (temp.rfind("INDI") != string::npos)
			{	
				
				//create the newIndi individual
				newIndi = new Individual;

				//get the id number
				newIndi->id = temp.substr(temp.find("@") + 1, (temp.rfind("@") - temp.find("@")) - 1);

				//get given names
				while (temp.find("1 NAME"))
					getline(fin, temp);
				

				while (temp.find("1 SEX"))
				{
					//cout << "testing: " << temp << endl;
					if (temp.find("2 GIVN") != string::npos)
						newIndi->givenName = temp.substr(temp.find("N") + 2);

					if (temp.find("2 SURN") != string::npos)
						newIndi->lastName = temp.substr(temp.find("N") + 2);

					getline(fin, temp);
				}

				//cout << "name is: " << newIndi->givenName << " " << newIndi->lastName << endl << endl;
				//make sure a birthdate was given
				while (temp.find("3 TIME"))
				{
					getline(fin, temp);
					if (temp.find("1 BIRT") != string::npos)
					{
						getline(fin, temp);
						break;
					}
				}

				//set the date
				if (temp.find("2 DATE") != string::npos)
				{
					//see if only given the year
					bool isYearOnly = (temp.size() == 11 || temp.find("/") != string::npos);
					
					//get to the first data item in date
					temp = temp.substr(temp.find("E") + 2);

					//if we are year only
					if (isYearOnly)
					{
						//just get the year
						newIndi->birthDate.setYear(atoi(temp.substr(0,5).c_str()));
					}
					else //if given complete birth date
					{
						bool hasDay = (temp.size() != 8);

						if (hasDay)
						{
							//get the day
							string day;
							for (int i = 0; temp[i] != ' '; i++)
							{
								day += temp[i];
							}

							//set the day
							newIndi->birthDate.setDay(atoi(day.c_str()));

							newIndi->birthDate.setMonth((temp.substr(temp.find(" ") + 1, 3))); //month
						
							newIndi->birthDate.setYear(atoi(temp.substr(temp.rfind(" ") + 1,5).c_str())); //year
						}
						else //if only month and year given
						{
							if (temp[0] != 'A')
							{
								newIndi->birthDate.setMonth(temp.substr(0,3));
								newIndi->birthDate.setYear(atoi(temp.substr(3).c_str()));
							}
							else //if ABT entry just set the year
							{
								newIndi->birthDate.setYear(atoi(temp.substr(4).c_str()));
							}

						}
					}

				}


				//set the root individual
				if (isRoot)
				{
					root = newIndi;
					head = new BTree(root);
				}
				//if not the root
				else
				{
					//create new node and set the data
					newNode = new BTree(newIndi);

					BTree *pNode = head;
					int count = 0;

					//find the insertion point
					while (pNode->getRightChild() && (*(pNode->getData()) < *newIndi))
					{
						pNode = pNode->getRightChild();
						++count;
					}
					
					//insert the new node
					if (count == 0) //if replacing head node
					{
						//reset the head
						newNode->setRight(head);

						//point head to correct location
						head = newNode;
					}
					else //if we don't need to replace the head
					{
						//set the new nodes child
						newNode->setRight(pNode->getRightChild());

						//insert the new node
						pNode->setRight(newNode);
					}

				}

				isRoot = false;
			}
			//if a family record
			else if (temp.rfind("@ FAM") != string::npos)
			{
				//get the id of husband, wife, and child
				//husband
				while (temp.find("1 HUSB"))
					getline(fin,temp);
				string husband = temp.substr(temp.find("@") + 1);
				husband = husband.substr(0, husband.size() - 1);
				
				//wife
				while (temp.find("1 WIFE"))
					getline(fin, temp);
				string wife = temp.substr(temp.find("@") + 1);
				wife = wife.substr(0, wife.size() - 1);

				//Child
				while (temp.find("1 CHIL"))
					getline(fin, temp);
				string child = temp.substr(temp.find("@") + 1);
				child = child.substr(0, child.size() - 1);
				//find each individual in the family

				//if this is the first family
				if (isRootFam)
				{
					treeRoot = new BTree();
					treeRoot->setData(getIndiById(child, head)->getData());

					//set the father
					treeRoot->insertLeft(getIndiById(husband, head)->getData());

					//set the mother
					treeRoot->insertRight(getIndiById(wife, head)->getData());

					isRootFam = false;
				}
				else //if not the first family
				{
					//find the child of the family in the existing tree
					BTree *item = new BTree();

					treeSearch(treeRoot, child, item);

					//insert the father
					item->insertLeft(getIndiById(husband, head)->getData());

					//insert the mother
					item->insertRight(getIndiById(wife, head)->getData());
				}

			}
		}

	//close the file
	fin.close();

	//create the linked list file
	ofstream fout("sorted.dat");

	//loop through the linked list
	BTree *pNode = head;

	while (pNode != NULL)
	{
		fout << *(pNode->getData()) << endl;
		pNode = pNode->getRightChild();
	}

	fout.close();
	return treeRoot;
}

/*********************************************************************
 * main
 * main calls all other functions in there correct order. It first
 * calls the process file in order to process the .ged and then 
 * displays the generated tree.
 ********************************************************************/
int main(int argc, char **argv)
{ 
   string fileName;       //string for filename
   BTree *head;           //var for head/root

   //process the file
   switch(argc)
   {
    case 1:
      cout << "Enter a file: ";
      cin >> fileName;
      head = parseFile(fileName);
      break;
    case 2:
      head = parseFile(argv[1]);
      break;
    default:
      cout << "Too many Arguments\n"
           << "Usage is: a.out <file name>\n";
   }

   //display the tree
	head->level();

return 0;
}
