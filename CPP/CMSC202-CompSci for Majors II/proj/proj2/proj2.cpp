#include <iostream>
#include <string>
#include "CipherMessage.h"
#include "Date.h"

using namespace std;

//Global so all functions can access it
CipherMessage cipher;

//Extra endl used to make better spacing

void loadFile(string fileName);
void displayHeader();
void displayText();
void decipherWithKey();
void decipherWithoutKey();
void printLoadedFile(string fileName);
void printMenu();

int main(){
  string userChoice = "a";
  string fileName = "none";
  while (userChoice != "q"){
    //print file name and menu
    printLoadedFile(fileName);
    printMenu();
    int userChoiceInteger;

    //Read user input for choice 
    cin >> userChoice;
    cout << endl;

    //Make userChoice into integer for switch statement
    if (userChoice == "l")
      userChoiceInteger = 1;
    else if (userChoice == "h")
      userChoiceInteger = 2;
    else if (userChoice == "t")
      userChoiceInteger = 3;
    else if (userChoice == "d")
      userChoiceInteger = 4;
    else if (userChoice == "u")
      userChoiceInteger = 5;
    else if (userChoice == "q")
      userChoiceInteger = 6;
    
    //Use userChoice to execute the appropriate option using switch
    switch(userChoiceInteger){
    case 1:
      cout << "Enter the file name: ";
      cin >> fileName;
      cout << endl;
      loadFile(fileName);
      break;
    case 2:
      displayHeader();
      break;
    case 3:
      displayText();
      break;
    case 4:
      decipherWithKey();
      break;
    case 5:
      decipherWithoutKey();
      break;
    case 6:
      cout << "Goodbye!" << endl;
      return 0;
    default:
      cout << "No action for given character." << endl;
    }
  
    /*
    //Use userChoice to exeute the appropriate option
    if (userChoice == "l"){
      cout << "Enter the file name: ";
      cin >> fileName;
      cout << endl;
      loadFile(fileName);
    }
    else if (userChoice == "h"){
      displayHeader();
    }
    else if (userChoice == "t"){
      displayText();
    }
    else if (userChoice == "d"){
      decipherWithKey();
    }
    else if (userChoice == "u"){
      decipherWithoutKey();
    }
    else if (userChoice == "q"){
      cout << "Goodbye!" << endl;
      return 0;
    }
    else{
      cout << "No action for given character." << endl;
    } 
    */
  }
  return 0;
}

//Attempt to load file from given filename
void loadFile(string fileName){
  cipher.LoadFromFile(fileName);
}

void displayHeader(){
  //Create date variable to store date info returned from GetSentDate()
  Date cipherDate;
  cipherDate = cipher.GetSentDate();
  cout << cipher.GetFrom() << endl
       << cipher.GetTo() << endl;
  cipherDate.PrintDate();
  cout << endl;
}

//Print out cipher text
void displayText(){
  cout << cipher.GetText() << endl << endl;
}

//Prompt user for key and call to Decipher(key)
void decipherWithKey(){
  string key = "asdfasdfasdf";
  //Make sure key length is not longer than allowed
  while (key.length() > MAX_KEYLEN){
    cout << "Enter the key (all caps): ";
    cin >> key;
    cout << endl;
    if (key.length() > MAX_KEYLEN){
      cout << "Key length too long. Please enter a key with length under " 
	   << MAX_KEYLEN << endl;
    }
  }
  string decipheredMessage = cipher.Decipher(key);
  cout << "Plain: " << decipheredMessage << endl << endl;
}

//Call to Decipher() 
void decipherWithoutKey(){
  string decipheredMessage = cipher.Decipher();
  cout << "Plain: " << decipheredMessage << endl << endl;
}

//Print out name of loaded file
void printLoadedFile(string fileName){
  if (fileName == "none"){
    cout << "There is no cipher file loaded." << endl << endl;
  }
  else {
    cout << "The cipher file " << fileName << " is currently loaded." << endl
	 << endl;
  }
}

//Print option menu
void printMenu(){
  cout << "Choose an action from the following menu:" << endl << endl;
  cout << "  l - load a cipher file" << endl;
  cout << "  h - display cipher file header" << endl;
  cout << "  t - display cipher file text" << endl;
  cout << "  d - decipher file with known key" << endl;
  cout << "  u - decipher file without a key" << endl;
  cout << "  q - quit" << endl << endl;
  cout << "Selection: ";
}
