#include <iostream>
#include <iterator>
#include "proj1.h"

using namespace std;

// Main func
int main(){
  int size = 0;

  // Loop and get number of vertices from user
  // Loop used in case incorrect value is entered for vertices
  while (size <= 1 || size > MAX_VERTICES){
    cout << "Enter the number of verticies: ";
    cin >> size;
  
    if (size <= 1 || size > MAX_VERTICES)
      cout << "Error: Number out of range (2 - 20)." << endl;
  }

  // Create graph with number of vertices given in length and width
  int graph[size][MAX_VERTICES];

  // Pass to initialize graph function
  InitializeGraph(graph, size);

  // Pass to get input for connected sides from user
  ConnectSides(graph, size);

  // Pass to function to check if graph(s) is/are connected
  if (IsConnected(graph, size))
    cout << "The graph is connected." << endl;
  else
    cout << "The graph is NOT connected." << endl;

  return 0;
}

// Function to get connected side input from user
void ConnectSides(int graph[][MAX_VERTICES], int size){
  // Declare input variables
  int a = -1;
  int b = -1;

  while (a != 0 && b != 0){
    GetTwoInput(a, b);
    // Exit case, do nothing, just used so no other cases proceed
    if (a == 0 && b == 0){
    }
    // Make sure a and b are in the accepted range
    else if (a < 0 || a > size){
      cout << "One or more numbers entered is not allowed. Please enter number from 0 to " << size << " only." << endl;
    }
    else if (b < 0 || b > size){
      cout << "One or more numbers entered is not allowed. Please enter number from 0 to " << size << " only." << endl;
    }
    // If they are in the accepted range continue to else statement
    else {
      // Check if input is already a side
      if (IsEdge(graph, size, a, b)){
	cout << "(" << a << "," << b << ") is already an edge." << endl;
      }
      // If input isn't already a side add it as a side
      else{
        CreateEdge(graph, size, a, b);
      }
    }
  }
}

// Function to check if graph is connected
bool IsConnected(int graph[][MAX_VERTICES], int size){
  int startValue = 1;
  int i = startValue;
  int j = i+1;
  if (RecursiveCheck(graph, size, startValue, i, j))
    return true;
  else
    return false;
}

// Recursively checks if the graph is connected
bool RecursiveCheck(int graph[][MAX_VERTICES], int size, int startValue, int i, int j){
  if (j > size)
    j = 1;
  if (j == 1 && i == size){
    if (IsEdge(graph, size, i, j))
      return true;
  }
  else if (IsEdge(graph, size, i, j))
    return RecursiveCheck(graph, size, startValue, i+1, j+1);
  else
    return false;
}

// Initialize graph func
void InitializeGraph(int graph[][MAX_VERTICES], int size){
  // Set all values being used to 0
  for (int i = 0; i < size; i++){
    for (int j = 0; j < size; j++){
      graph[i][j] = 0;
    }
  }
}

// Remove edge func
bool RemoveEdge(int graph[][MAX_VERTICES], int size, int u, int v){
  if (IsEdge(graph, size, u, v)){
    graph[u-1][v-1] = 0;
    graph[v-1][u-1] = 0;
    return true;
  }
  else
    return false;
}

// Create edge func
bool CreateEdge(int graph[][MAX_VERTICES], int size, int u, int v){
  if (u > size || v > size){
    return false;
  }
  else if (IsEdge(graph, size, u, v)){
    return false;
  }
  else{
    graph[u-1][v-1] = 1;
    graph[v-1][u-1] = 1;
    return true;
  }
}

// Is edge func
bool IsEdge(int graph[][MAX_VERTICES], int size, int u, int v){
  if ((graph[u-1][v-1] == 1) && (graph[v-1][u-1] == 1)){
    return true;
  }
  else
    return false;
}

// Function to get two input values
void GetTwoInput (int &value1, int &value2) {
  cout << "Enter a vertex pair (0 0 to end): ";

  istream_iterator<double> eos;         // end-of-stream iterator
  istream_iterator<double> iit (cin);   // stdin iterator

  if (iit!=eos) value1=*iit;

  iit++;
  if (iit!=eos) value2=*iit;
}
