#include <iostream>
#include "IntArray.h"

using namespace std;

int main()
{
  // Create IntArray objects and call methods here...
  //Constructor
  IntArray firstArray(-1);
  IntArray secondArray(10000000000);
  IntArray thirdArray(.5);
  //Equality operator
  IntArray fourthArray(5);
  IntArray fifthArray;
  fourthArray==(fifthArray);
  IntArray sixthArray;
  IntArray seventhArray;
  sixthArray==(seventhArray);

  //Inequality operator
  fourthArray!=(fifthArray);
  sixthArray!=(seventhArray);

  //Add-assign operator
  fourthArray+=(fifthArray);

  //Add operator
  sixthArray+(fourthArray);
  fourthArray+(fifthArray);
  
  //Index operator
  

  //Get
  fourthArray.Get(-1);
  fourthArray.Get(8);

  //Set item
  fourthArray.SetItem(-1,5);
  fourthArray.SetItem(8,2);

  //Insert
  fifthArray.Insert(0,5);
  fourthArray.Insert(-1,2);
  fourthArray.Insert(8,2);

  //Del
  fifthArray.Del(0);
  fourthArray.Del(-1);
  fourthArray.Del(8);

  //Remove
  fifthArray.Remove(0);
  fourthArray.Remove(10);

  //Clear
  fifthArray.Clear();

  //Contains
  fifthArray.Contains(5);

  //Contains 2
  fifthArray.Contains(5, 5);
  fourthArray.Contains(5, -1);
  fourthArray.Contains(5, 8);

  //IndexOf
  fifthArray.IndexOf(5);
  fourthArray.IndexOf(5);

  //AddToAll
  fifthArray.AddToAll(5);

  //Scale
  fifthArray.Scale(5);

  //Sum
  fourthArray.Sum(fifthArray);
  fifthArray.Sum(fourthArray);
  IntArray eighthArray(10);
  fourthArray.Sum(eighthArray);

  //Product
  fourthArray.Product(fifthArray);
  fifthArray.Product(fourthArray);
  fourthArray.Product(eighthArray);

  // Print out the number of errors/edge cases found
  cout << endl << endl << IntArray::GetProgress() << endl;
    
  return 0;
}
