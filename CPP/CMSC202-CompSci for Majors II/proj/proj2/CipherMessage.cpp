/*
 * Template CipherMessage.cpp
 * 
 * Students may NOT modify the provided constructors or LoadFromFile()
 * function.  Functions may be added AFTER LoadFromFile().
 */

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <cmath>
#include "CipherMessage.h"
#include "Date.h"

using namespace std;

CipherMessage::CipherMessage() 
  : m_text(""), m_from(""), m_to(""), m_sentDate(Date(1,1,1970))
{ /* Empty function body */ }

CipherMessage::CipherMessage(string from, string to, Date sentDate, string text) 
  : m_from(from), m_to(to), m_sentDate(sentDate)
{ 
  m_text = "";

  /* Only copy uppercase letters to m_text */

  for (int i = 0; i < text.length(); i++)
    if (text[i] >= 'A' && text[i] <= 'Z')
      m_text += text[i];
}

bool CipherMessage::LoadFromFile(string fileName) {
  ifstream dataFile;
  string from;
  string to;
  int month, day, year;
  char text_cstr[MAX_CIPHERLEN];
  string text;

  /* Set exception flags for file input stream */ 

  dataFile.exceptions(ios::failbit | ios::badbit);

  try {

    dataFile.open(fileName.c_str());

    /* Read from, to, month, day, year */

    dataFile >> from;
    dataFile >> to;
    dataFile >> month >> day >> year;

    /* Read text.  First getline() clears previous newline */

    dataFile.getline(text_cstr, MAX_CIPHERLEN);
    dataFile.getline(text_cstr, MAX_CIPHERLEN);

    /* Only copy uppercase letters to string */
    
    for (int i = 0; i < strlen(text_cstr); i++)
      if (text_cstr[i] >= 'A' && text_cstr[i] <= 'Z')
	text += text_cstr[i];

    dataFile.close();
  } 
  catch (exception e) {
    return false;
  }

  /* Made it through file read; assign to class variables. */

  m_from = from;
  m_to = to;
  m_sentDate = Date(month, day, year);
  m_text = text;

  return true;
}

//Decipher the message with no given key
string CipherMessage::Decipher() {

  //Get best text prediction from each
  string byOne = DecipherByOne(m_text);
  string byTwo = DecipherByTwo();
  string byThree = DecipherByThree();
  string byFour = DecipherByFour();
  string byFive = DecipherByFive();
  string bySix = DecipherBySix();

  /* Check which has the highest probability. Lower numbers multiplied by
   higher numbers to give a better value than higher if similar odds */
  double prob = logProb(byOne)*6;
  if (logProb(byTwo)*5 > prob){
    prob = logProb(byTwo)*5;
  }
  if (logProb(byThree)*4 > prob){
    prob = logProb(byThree)*4;
  }
  if (logProb(byFour)*3 > prob){
    prob = logProb(byFour)*3;
  }
  if (logProb(byFive)*2 > prob){
    prob = logProb(byFive)*2;
  }
  if (logProb(bySix) > prob){
    prob = logProb(bySix);
  }

  //Match highest probability with the decipher and return correct string
  if (logProb(byOne)*6 == prob){
    return byOne;
  }
  else if (logProb(byTwo)*5 == prob){
    return byTwo;
  }
  else if (logProb(byThree)*4 == prob){
    return byThree;
  }
  else if (logProb(byFour)*3 == prob){
    return byFour;
  }
  else if (logProb(byFive)*2 == prob){
    return byFive;
  }
  else if (logProb(bySix) == prob){
    return bySix;
  }
  else{
    return "Error";
  }
}

//Decipher the message with a given key
string CipherMessage::Decipher(string key){
  
  //Initialize array with repeating int value of key for length of cipher
  int keyIntValues[m_text.length()];
  string repeatedKey = "";

  while (repeatedKey.length() < m_text.length()){
    repeatedKey += key;
  }

  for ( int i = 0; i < m_text.length(); i++){
    for (int j = 0; j < ALPHABET.length(); j++){
      if (repeatedKey[i] == ALPHABET[j]){
	keyIntValues[i] = j;
      }
    }
  }
  
  //Initialize array to hold converted int values
  int cipherIntValues[m_text.length()];
  for (int i = 0; i < m_text.length(); i++){
    for (int j = 0; j < ALPHABET.length(); j++){
      if (m_text[i] == ALPHABET[j]){
	cipherIntValues[i] = j;
      }
    }
  }
  
  //Subtract keyIntValues from cipherIntValues
  int subtractedValues[m_text.length()];
  for (int i = 0; i < m_text.length(); i++){
    subtractedValues[i] = (cipherIntValues[i] - keyIntValues[i]);
  }
  
  //If negative add 26 to value
  for (int i = 0; i < m_text.length(); i++){
    if (subtractedValues[i] < 0){
      subtractedValues[i] += 26;
    }
  }
  
  //Convert from numbers to letters
  string finishedCipher = "";
  for (int i = 0; i < m_text.length(); i++){
    finishedCipher += ALPHABET[subtractedValues[i]];
  }
  return finishedCipher;
}

//Return cipher text
string CipherMessage::GetText() const {
  return m_text;
}

//Return sender info
string CipherMessage::GetFrom() const {
  return m_from;
}

//Return recipient info
string CipherMessage::GetTo() const {
  return m_to;
}

//Return message sent date
Date CipherMessage::GetSentDate() const {
  return m_sentDate;
}

//Set cipher to given uppercase text
void CipherMessage::SetText(string text) {
  m_text = "";
  
  /* Only copy uppercase letters to m_text */
  
  for (int i = 0; i < text.length(); i++)
    if (text[i] >= 'A' && text[i] <= 'Z')
      m_text += text[i];
}

//Set sender info to given text
void CipherMessage::SetFrom(string from) {
  m_from = from;
}

//Set recipient info to given text
void CipherMessage::SetTo(string to) {
  m_to = to;
}

//Set sent date to given date
void CipherMessage::SetSentDate(const Date& sentDate) {
  m_sentDate = sentDate;
}

double CipherMessage::logProb(string message) {
  double prob = 0;
  for (int i = 0; i < message.length(); i++){
    for (int j = 0; j < ALPHABET.length(); j++){
      if (message[i] == ALPHABET[j]){
	prob += (log(26*EN_FREQ[j]));
      }
    }
  }
  return prob;
}

string CipherMessage::DecipherByOne(string mess){
  string actualMessage = "";
  double highestProb = 0;
  string highestProbKey = "A";

  //Loop through alphabet trying each letter, record higest prob key
  for (int i = 0; i < ALPHABET.length(); i++){
    char letter = ALPHABET[i];
    string lett = "";
    lett += letter;
    string decipher = Decipher(lett, mess);
    double prob = logProb(decipher);

    if (prob > highestProb){
      highestProb = prob;
      highestProbKey = ALPHABET[i];
    }
  }
  actualMessage = Decipher(highestProbKey, mess);
  return actualMessage;
}

string CipherMessage::DecipherByTwo(){
  string messOne = "";
  string messTwo = "";
  string finalMessage = "";

  //Split message by every other letter and store to appropriate variable
  for (int i = 0; i < m_text.length(); i+=2){
    messOne += m_text[i];
  }
  for (int i = 1; i < m_text.length(); i+=2){
    messTwo += m_text[i];
  }

  //Decipher each message
  string guessOne = DecipherByOne(messOne);
  string guessTwo = DecipherByOne(messTwo);

  //Add messages back into one string
  for (int i = 0; i < messOne.length(); i++){
    if (i < guessOne.length()){
      finalMessage += guessOne[i];
    }
    if (i < guessTwo.length()){
      finalMessage += guessTwo[i];
    }
  }
  return finalMessage;
}

string CipherMessage::DecipherByThree(){
  string finalMessage = "";
  string messOne = "";
  string messTwo = "";
  string messThree = "";

  //Split messages into separate by 3
  for (int i = 0; i < m_text.length(); i+=3){
    messOne += m_text[i];
  }
  for (int i = 1; i < m_text.length(); i+=3){
    messTwo += m_text[i];
  }
  for (int i = 2; i < m_text.length(); i+=3){
    messThree += m_text[i];
  }

  //Decipher each message
  string guessOne = DecipherByOne(messOne);
  string guessTwo = DecipherByOne(messTwo);
  string guessThree = DecipherByOne(messThree);

  //Add message back together
  for (int i = 0; i < messOne.length(); i++){
    if (i < guessOne.length()){
      finalMessage += guessOne[i];
    }
    if (i < guessTwo.length()){
      finalMessage += guessTwo[i];
    }
    if (i < guessThree.length()){
      finalMessage += guessThree[i];
    }
  }
  return finalMessage;
}

string CipherMessage::DecipherByFour(){
  string finalMessage = "";
  string messOne = "";
  string messTwo = "";
  string messThree = "";
  string messFour = "";

  //Split into 4 strings to decypher
  for (int i = 0; i < m_text.length(); i+=4){
    messOne += m_text[i];
  }
  for (int i = 1; i < m_text.length(); i+=4){
    messTwo += m_text[i];
  }
  for (int i = 2; i < m_text.length(); i+=4){
    messThree += m_text[i];
  }
  for (int i = 3; i < m_text.length(); i+=4){
    messFour += m_text[i];
  }

  //Decipher each string
  string guessOne = DecipherByOne(messOne);
  string guessTwo = DecipherByOne(messTwo);
  string guessThree = DecipherByOne(messThree);
  string guessFour = DecipherByOne(messFour);

  //Return all to one string
  for (int i = 0; i < guessOne.length(); i++){
    if (i < guessOne.length()){
      finalMessage += guessOne[i];
    }
    if (i < guessTwo.length()){
      finalMessage += guessTwo[i];
    }
    if (i < guessThree.length()){
      finalMessage += guessThree[i];
    }
    if (i < guessFour.length()){
      finalMessage += guessFour[i];
    }
  }
  return finalMessage;
}

string CipherMessage::DecipherByFive(){
  string finalMessage = "";
  string messOne = "";
  string messTwo = "";
  string messThree = "";
  string messFour = "";
  string messFive = "";

  //Split into 5 strings to decypher
  for (int i = 0; i < m_text.length(); i+=5){
    messOne += m_text[i];
  }
  for (int i = 1; i < m_text.length(); i+=5){
    messTwo += m_text[i];
  }
  for (int i = 2; i < m_text.length(); i+=5){
    messThree += m_text[i];
  }
  for (int i = 3; i < m_text.length(); i+=5){
    messFour += m_text[i];
  }
  for (int i = 4; i < m_text.length(); i+=5){
    messFive += m_text[i];
  }

  //Decipher each string
  string guessOne = DecipherByOne(messOne);
  string guessTwo = DecipherByOne(messTwo);
  string guessThree = DecipherByOne(messThree);
  string guessFour = DecipherByOne(messFour);
  string guessFive = DecipherByOne(messFive);

  //Return all to one string
  for (int i = 0; i < guessOne.length(); i++){
    if (i < guessOne.length()){
      finalMessage += guessOne[i];
    }
    if (i < guessTwo.length()){
      finalMessage += guessTwo[i];
    }
    if (i < guessThree.length()){
      finalMessage += guessThree[i];
    }
    if (i < guessFour.length()){
      finalMessage += guessFour[i];
    }
    if (i < guessFive.length()){
      finalMessage += guessFive[i];
    }
  }
  return finalMessage;
}

string CipherMessage::DecipherBySix(){
  string finalMessage = "";
  string messOne = "";
  string messTwo = "";
  string messThree = "";
  string messFour = "";
  string messFive = "";
  string messSix = "";

  //Split into 6 strings to decypher
  for (int i = 0; i < m_text.length(); i+=6){
    messOne += m_text[i];
  }
  for (int i = 1; i < m_text.length(); i+=6){
    messTwo += m_text[i];
  }
  for (int i = 2; i < m_text.length(); i+=6){
    messThree += m_text[i];
  }
  for (int i = 3; i < m_text.length(); i+=6){
    messFour += m_text[i];
  }
  for (int i = 4; i < m_text.length(); i+=6){
    messFive += m_text[i];
  }
  for (int i = 5; i < m_text.length(); i+=6){
    messSix += m_text[i];
  }

  //Decipher each string
  string guessOne = DecipherByOne(messOne);
  string guessTwo = DecipherByOne(messTwo);
  string guessThree = DecipherByOne(messThree);
  string guessFour = DecipherByOne(messFour);
  string guessFive = DecipherByOne(messFive);
  string guessSix = DecipherByOne(messSix);


  //Return all to one string
  for (int i = 0; i < guessOne.length(); i++){
    if (i < guessOne.length()){
      finalMessage += guessOne[i];
    }
    if (i < guessTwo.length()){
      finalMessage += guessTwo[i];
    }
    if (i < guessThree.length()){
      finalMessage += guessThree[i];
    }
    if (i < guessFour.length()){
      finalMessage += guessFour[i];
    }
    if (i < guessFive.length()){
      finalMessage += guessFive[i];
    }
    if (i < guessSix.length()){
      finalMessage += guessSix[i];
    }
  }
  return finalMessage;
}

string CipherMessage::Decipher(string key, string message){
  //Initialize array with repeating int value of key for length of cipher
  int keyIntValues[message.length()];
  string repeatedKey = "";

  while (repeatedKey.length() < message.length()){
    repeatedKey += key;
  }

  for ( int i = 0; i < message.length(); i++){
    for (int j = 0; j < ALPHABET.length(); j++){
      if (repeatedKey[i] == ALPHABET[j]){
        keyIntValues[i] = j;
      }
    }
  }

  //Initialize array to hold converted int values
  int cipherIntValues[message.length()];
  for (int i = 0; i < message.length(); i++){
    for (int j = 0; j < ALPHABET.length(); j++){
      if (message[i] == ALPHABET[j]){
        cipherIntValues[i] = j;
      }
    }
  }

  //Subtract keyIntValues from cipherIntValues
  int subtractedValues[message.length()];
  for (int i = 0; i < message.length(); i++){
    subtractedValues[i] = (cipherIntValues[i] - keyIntValues[i]);
  }
  //If negative add 26 to value
  for (int i = 0; i < message.length(); i++){
    if (subtractedValues[i] < 0){
      subtractedValues[i] += 26;
    }
  }

  //Convert from numbers to letters
  string finishedCipher = "";
  for (int i = 0; i < message.length(); i++){
    finishedCipher += ALPHABET[subtractedValues[i]];
  }
  return finishedCipher;
}
