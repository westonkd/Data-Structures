/***********************************************************************
* Author:
*  Weston Dransfield
* Summary:
*  Uses a deque to simulate stock sells and buys
***********************************************************************/
#include <iostream>
#include <string>
#include <deque>
#include <fstream>
#include <vector>
#include <stdlib.h> 
#include <iomanip>

using namespace std;

/*********************************************************************
* class Transactin
* This calss in an abstraction of a transactoin of shares on the
* stock market.
*********************************************************************/
class Transaction
{
public:
	//constructor
	Transaction(string type = "BUY");

	//getters and setters
	//set and get type (Buy or Sell)
	bool setType(const string type); 
	string getType() const {return type; }

	//set and get num of shares
	void setNumShares(const int num) {numShares = num; } 
	int getNumShares() const         {return numShares;}

	//set and get share price
	void setSharePrice(const double price) {sharePrice = price;} 
	double getSharePrice() const           {return sharePrice; }

  //display
  void display(bool inProgress = true, double profit = 0) const;

  //sell
  int sell(int numToSell);

private:
	string type;
	int numShares;
	double sharePrice;
};

/*********************************************************************
 * Transaction :: Transaction
 * Default constructor for transaction
 ********************************************************************/
Transaction::Transaction(string type) : numShares(0), sharePrice(0.0)  
{
	//set the transaction type (buy by default)
	setType(type);
}

/*********************************************************************
 * Transaction :: setType
 * This function sets the type of the transaction and checks to
 * see if it is a valid type
 ********************************************************************/
 bool Transaction::setType(const string type) 
 {
 	if (type == "BUY" || type == "SELL")
 		this->type = type;
 	else
 		return false;
 	return true;
 }

/*********************************************************************
 * Transaction :: Display
 * this function displays a transaction
 ********************************************************************/
 void Transaction::display(bool inProgress, double profit) const 
 {
   //display for buy and sell
   if (inProgress)
      cout << ((type == "BUY") ? "Bought " : "Sold ");

   cout << numShares 
        << (inProgress ? " shares at " : " shares bought for ")
        << "$" << fixed 
        << setprecision(2) << sharePrice;

   //show profit for sell only
   if (type == "SELL")
   {
     cout << " for a profit of $";

   //if negative, format accordingly
   if (profit < 0)
      cout << "(" << -profit << ")";
   else
      cout << profit;
   }

   cout << endl;
 }

/*********************************************************************
* Transaction :: Sell
* This function sells shares
*********************************************************************/
int Transaction::sell(int numToSell) 
{
   //subtract number of shares
   numShares -= numToSell;

   //if we are in the hole, return the remainder
   if (numShares < 0)
      return -numShares;

   //if we are still positive, no reamainder
   return 0;
}

/*********************************************************************
* makeSale
* This function assists in selling shares.
********************************************************************/
double makeSale(deque<Transaction> & myTrans, Transaction & newTrans)
{
   double saleProfit = 0; //keeps track of profit

   //make the sale
   int remainder = myTrans[0].sell(newTrans.getNumShares());
 
   //get the profit
   saleProfit += (newTrans.getSharePrice() - myTrans[0].getSharePrice())
                  * (newTrans.getNumShares() - remainder);

   //if there is a remaing amount to sell, 
   while (remainder > 0)
   {
      //remove the oldest transaction and subtract from next
      myTrans.pop_front();

      //update the profit
      saleProfit += (newTrans.getSharePrice() - myTrans[0].getSharePrice())
                     * remainder;

      remainder = myTrans[0].sell(remainder);
   }

   return saleProfit;
}

/*********************************************************************
* readFile
* reads the contents of the file into a string for later 
********************************************************************/
double processFile(const string instructions, deque<Transaction> & myTrans)
{
   //create a new transaction
   Transaction newTrans;

   if (instructions[0] == 'B')
     newTrans.setType("BUY");
   else
     newTrans.setType("SELL"); 
      
   //set the numStocks
   int numLen = 0;   //length of num stocks
   int startPos = 0; //starting position of num stocks

   //find starting position of data
   for (int i = 0; instructions[i] != ' '; i++)
      startPos++;
   startPos++; //add one more to get the first data item

   //first see how many digits the num is
   for (int i = startPos; instructions[i] != ' '; i++)
      numLen++;

   //set the num shares
   newTrans.setNumShares(atoi(instructions.substr(startPos,numLen).c_str()));

   //update the starting position
   startPos += numLen;

   //set length of price per share
   int priceLen = 0;
   for (int i = numLen; instructions[i] != '\0'; i++)
      priceLen++;

   //set the price per share
   newTrans.setSharePrice(atof(instructions.substr(startPos,priceLen).c_str()));
  
   //if it is a sale, make the sale.
   double saleProfit = 0.0;
   if (newTrans.getType() == "SELL")
      saleProfit = makeSale(myTrans, newTrans);

   //display the transaction
   newTrans.display(true, saleProfit);

   //store the transaction in a deque if it is a buy
   if (newTrans.getType() == "BUY")
   {
      myTrans.push_back(newTrans);
      return 0;
   }

   //return the net gain
   return saleProfit;
}

/*********************************************************************
 * readFile
 * reads the contents of the file into a string for later 
 ********************************************************************/
bool readFile(vector <string> & transactions, const string fileName)
{
	//open the file
	ifstream fin(fileName.c_str());
	if (fin.fail())
		return false;

	//read the file into transaction string
	string temp;
	while (getline(fin,temp))
		transactions.push_back(temp);

	return true;
}

/*********************************************************************
 * main
 * main calls all other functions in there correct order.
 ********************************************************************/
int main(int argc, char **argv)
{ 
   string fileName;     //holds the file name
   vector <string> transactions;       //transactions to take place
   deque <Transaction> myTransactions; //holds transactions 
   double totalProfit = 0.0; //tracks the profit

   //read the file
   switch(argc)
    {
    case 1:
      cout << "Enter a file: ";
      cin >> fileName;
      readFile(transactions, fileName);
      break;
    case 2:
      readFile(transactions, argv[1]);
      break;
    default:
      cout << "Too many Arguments\n"
           << "Usage is: a.out <file name>\n";
    }

    //process the instructions
    for (int i = 0; i < transactions.size(); i++)
      totalProfit += processFile(transactions[i], myTransactions);

    //dispaly the profit
   cout << "\nTotal Profit: $" << totalProfit << "\n\n";

   //display unsold shares
   cout << "Unsold Shares\n";
   for (deque<Transaction>::iterator it = myTransactions.begin();
        it != myTransactions.end(); it++)
   {
      if (it->getNumShares() > 0)
      {
         cout << "   ";
         it->display(false);
      }
   }

   return 0;
}
