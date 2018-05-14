//proj3.cpp
#include <iostream>
#include <string>
#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"

using namespace std;

//Global so all functions can access
Graph loadedGraph;

void loadFile(string fileName);
void displayVertices();
void displayEdges();
void displayConnected();
void printLoadedFile(string fileName);
void printMenu();

int main(){
  string userChoice = "a";
  string fileName = "none";
  while (userChoice != "q"){
    //Print file name and menu
    printLoadedFile(fileName);
    printMenu();

    //Read user input for choice
    cin >> userChoice;
    cout << endl;

    if (userChoice == "l"){
      cout << "Enter the file name: ";
      cin >> fileName;
      cout << endl;
      loadFile(fileName);
    }
    else if (userChoice == "v"){
      displayVertices();
    }
    else if (userChoice == "e"){
      displayEdges();
    }
    else if (userChoice == "c"){
      displayConnected();
    }
    else if (userChoice == "q"){
      cout << "Goodbye!" << endl;
      return 0;
    }
    else{
      cout << "No action for given input." << endl;
    }
  }
  return 0;
}

void loadFile(string fileName){
  bool truthValue = loadedGraph.LoadFromFile(fileName);
  if (truthValue == false){
    cout << "Error loading data file (" << fileName << ")." << endl << endl;
  }
}

void displayVertices(){
  vector<Vertex *> vertices = loadedGraph.GetVertices();

  //Print out vertices
  cout << "Vertices: " << endl;
  for (unsigned int i = 0; i < vertices.size(); i++){
    cout << "  ID: " << vertices[i]->GetID() << endl;
  }
  cout << endl;
}

void displayEdges(){
  vector<Edge *> edges = loadedGraph.GetEdges();

  //Print out edges
  cout << "Edges: " << endl;
  for (unsigned int i = 0; i < edges.size(); i++){
    cout << "  ID: " << edges[i]->GetV1()->GetID() << " <--> ID: "
	 << edges[i]->GetV2()->GetID() << endl;
  }
  cout << endl;
}

void displayConnected(){
  int vertexNum;
  Vertex* currVertex;
  cout << "Enter the vertex ID: ";
  cin >> vertexNum;

  //Match vertexNum with correct vertex
  vector<Vertex *> vertexList = loadedGraph.GetVertices();
  for (unsigned int i = 0; i < vertexList.size(); i++){
    int vID = vertexList[i]->GetID();
    if (vID == vertexNum){
      currVertex = vertexList[i];
    } 
  }

  //Print out connected components
  cout << "Connected component(s) of vertex with ID " << vertexNum << ":"
       << endl;
  vector<Vertex *> connected = loadedGraph.GetConnectedComponent(currVertex);
  for (unsigned int i = 0; i < connected.size(); i++){
    cout << "  ID: " << connected[i]->GetID() << endl;
  }
}

//Print name of loaded file
void printLoadedFile(string fileName){
  if (fileName == "none"){
    cout << "There is no data file loaded." << endl << endl;
  }
  else {
    cout << "The data file " << fileName << " is currently loaded." << endl
         << endl;
  }
}

//Print option menu
void printMenu(){
  cout << "Choose an action from the following menu:" << endl << endl;
  cout << "  l - load a graph data file" << endl;
  cout << "  v - list the vertices of the loaded graph" << endl;
  cout << "  e - list the edges of the loaded graph" << endl;
  cout << "  c - list the connected component of a specific vertex" << endl;
  cout << "  q - quit" << endl << endl;
  cout << "Selection: ";
}
