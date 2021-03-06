//proj4.cpp

#include <iostream>
#include <string>
#include "WalkGraph.h"
#include "WalkVertex.h"
#include "WalkEdge.h"
#include "SafeHouse.h"
#include "PoliceStation.h"
#include "Intersection.h"

using namespace std;

//Global WalkGraph
WalkGraph myWalkData;

void loadFile(string fileName);
void printLoadedFile(string fileName);
void printMenu();
void displayVertices();
void displayEdges();
void simulateWalk();

int main(){
  //Base class pointer
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
    else if (userChoice == "v")
      userChoiceInteger = 2;
    else if (userChoice == "e")
      userChoiceInteger = 3;
    else if (userChoice == "w")
      userChoiceInteger = 4;
    else if (userChoice == "q")
      userChoiceInteger = 5;

    //Use userChoice to execute the appropriate option using switch
    switch(userChoiceInteger){
    case 1:
      cout << "Enter the file name: ";
      cin >> fileName;
      cout << endl;
      loadFile(fileName);
      break;
    case 2:
      displayVertices();
      break;
    case 3:
      displayEdges();
      break;
    case 4:
      simulateWalk();
      break;
    case 5:
      cout << "Goodbye!" << endl;
      return 0;
    default:
      cout << "No action for given character." << endl;
    }
  }
  return 0;
}

//Print option menu
void printMenu(){
  cout << "Choose an action from the following menu:" << endl << endl;
  cout << "  l - load a graph data file" << endl;
  cout << "  v - list the vertices of the loaded graph" << endl;
  cout << "  e - list the edges of the loaded graph" << endl;
  cout << "  w - simulate a random walk from a given vertex" << endl;
  cout << "  q - quit" << endl << endl;
  cout << "Selection: ";
}

//Print out name of loaded file
void printLoadedFile(string fileName){
  if (fileName == "none"){
    cout << "There is no data file loaded." << endl << endl;
  }
  else {
    cout << "The data file " << fileName << " is currently loaded." << endl
         << endl;
  }
}

//Attempt to load file from given filename
void loadFile(string fileName){
  myWalkData.LoadFromFile(fileName);
}

//Print out vertices
void displayVertices(){
  int numOfVertices = myWalkData.GetNumVertices();
  vector<WalkVertex *> vertices = myWalkData.GetVertices();

  cout << "Vertices: " << endl;

  for (int i = 0; i < numOfVertices; i++){
    cout << "  " << vertices[i]->ToString() << endl;
  }
  cout << endl;
}

//Print out edges
void displayEdges(){
  int numOfEdges = myWalkData.GetNumEdges();
  vector<WalkEdge *> edges = myWalkData.GetEdges();
  WalkVertex* v1;
  WalkVertex* v2;

  cout << "Edges: " << endl;

  for (int i = 0; i < numOfEdges; i++){
    v1 = edges[i]->GetV1();
    v2 = edges[i]->GetV2();
    cout << v1->ToString() << "\n    <--> " << v2->ToString() << endl;
  }
  cout << endl;
}

//Attempt to simulate walk
void simulateWalk(){
  int numOfVertices = myWalkData.GetNumVertices();
  vector<WalkVertex *> vertices = myWalkData.GetVertices();
  WalkVertex* myVertex;

  //Get input from user
  int vertexID = -1;
  while ((vertexID < 0) || (vertexID > (numOfVertices-1))){
    cout << "Enter vertex ID: ";
    cin >> vertexID;
    if ((vertexID > (numOfVertices-1)) || (vertexID < 0)){
      cout << "No vertex with given ID, please try again." << endl;
    }
  }
  
  int maxSteps;
  cout << "Enter the maximum number of steps in the simulation: ";
  cin >> maxSteps;

  int seed;
  cout << "Enter an integer seed for the random number generator: ";
  cin >> seed;
  cout << endl;

  //Get vector from given ID
  for (int i = 0; i < numOfVertices; i++){
    if (vertices[i]->GetID() == vertexID){
      myVertex = vertices[i];
    }
  }

  vector<WalkVertex *> myWalk = myWalkData.Walk(myVertex, maxSteps, seed);

  if (myWalk.size() == 0){
    cout << "No walk!" << endl;
  }
  else{
    cout << "Random Walk:" << endl;
    
    //print out myWalk
    for (int i = 0; i < myWalk.size(); i++){
      cout << "  " << myWalk[i]->ToString() << endl;
    }
  }
  // Prints out appropriate reaction for end of walk
  string str1 = "SafeHouse";
  string str2 = "PoliceStation";
  string end = myWalk.back()->ToString();

  if (end.find(str1) != -1){
    cout << "You made it to safety! But crime doesn't pay..." << endl << endl;
  }
  else if (end.find(str2) != -1){
    cout << "You were caught!" << endl << endl;
  }
}
