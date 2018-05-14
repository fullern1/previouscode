// File: proj1.h

#ifndef PROJ1_H
#define PROJ1_h

#define MAX_VERTICES 20

// For the following functions, 'graph' is a two-dimensional
// integer array used to store the graph and 'size' is the
// number of vertices in the graph.

void InitializeGraph(int graph[][MAX_VERTICES], int size);
// Initialize the (i,j) entries of the array to zero for
// 0 <= i, j < size.

bool RemoveEdge(int graph[][MAX_VERTICES], int size, int u, int v);
// Remove the edge between vertices u and v.
// Return false if there was no edge connecting u and v
// or if the specified vertices are invalid.
// Return true if there was an edge connecting u and v and
// it was removed.

bool CreateEdge(int graph[][MAX_VERTICES], int size, int u, int v);
// Create an edge between vertices u and v.
// Return false if there was already an edge connecting u and v
// or if the specified vertices are invalid.
// Return true if there was not an edge connecting u and v and
// it was created.

bool IsEdge(int graph[][MAX_VERTICES], int size, int u, int v);
// Return true if there is an edge connecting u and v;
// false otherwise.

void GetTwoInput (int &value1, int &value2);
// Gets two integer values entered on the same line.

bool IsConnected(int graph[][MAX_VERTICES], int size);
// 'graph' is the two-dimensional array used to store the
// graph and 'size' is the number of vertices in the graph.
// Returns true if the graph is connected; false otherwise.

void ConnectSides(int graph[][MAX_VERTICES], int size);
// function used to get input from user about which sides of the
// graph are connected

bool RecursiveCheck(int graph[][MAX_VERTICES], int size, int startValue, int i, int j);
// Recursively checks if the graph is connected

#endif
