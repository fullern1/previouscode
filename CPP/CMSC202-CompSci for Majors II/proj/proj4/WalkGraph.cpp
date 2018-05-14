#include <string>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include "WalkGraph.h"
#include "WalkVertex.h"
#include "WalkEdge.h"
#include "PoliceStation.h"
#include "Intersection.h"
#include "SafeHouse.h"

using namespace std;

WalkGraph::WalkGraph()
{ /* nothing to do */ }

WalkGraph::WalkGraph(vector<WalkVertex *> vertices, vector<WalkEdge *> edges) :
  m_vertices(vertices), m_edges(edges)
{
  for (int i = 0; i < vertices.size(); i++)
    if (vertices[i] == NULL) {
      cerr << "Error: WalkGraph constructor expects non-null vertices." << endl;
      exit(1);
    }
  
  for (int i = 0; i < edges.size(); i++)
    if (edges[i]->GetV1() == NULL || edges[i]->GetV2() == NULL) {
      cerr << "Error: WalkGraph constructor expects edges with non-null vertices." << endl;
      exit(1);
    }
}      

bool WalkGraph::LoadFromFile(string fileName) {
  int numVertices;
  int v1, v2;
  string type;
  char description[MAXDESCRIPTIONLEN];
  double prob;
  vector<WalkVertex*> vertices;
  vector<WalkEdge*> edges;
  ifstream dataFile;
      
  /* Set exception flags for file input stream */ 

  dataFile.exceptions(ios::failbit | ios::badbit);

  try {

    // Open the file and read the number of vertices (first data line)

    dataFile.open(fileName.c_str());
    dataFile >> numVertices;

    for ( int i = 0; i < numVertices; i++ ) {

      // Read vertex type and capture probability

      dataFile >> type >> prob;

      // Kludge to get rid of space between prob and description

      dataFile.get(); 

      // Read vertex description (remainder of line)

      dataFile.getline(description, MAXDESCRIPTIONLEN);

      if (type == "Intersection")
	vertices.push_back( new Intersection(string(description)) );
      else if (type == "PoliceStation")
	vertices.push_back( new PoliceStation(prob, string(description)) );
      else if (type == "SafeHouse")
	vertices.push_back( new SafeHouse(string(description)) );
      else
	cerr << "Warning: Invalid type in data file " << fileName 
	     << ". Line ignored." << endl;
    }

    // Read edge data
    
    dataFile >> v1 >> v2;
  
    while ( v1 > 0 && v2 > 0 ) {
      if (v1 <= numVertices && v2 <= numVertices )
	edges.push_back( new WalkEdge(vertices[v1-1], vertices[v2-1]) );
      dataFile >> v1 >> v2;
    }

    dataFile.close();
  }
  catch (exception e) {
    return false;
  }

  m_vertices = vertices;
  m_edges = edges;

  return true;
}

int WalkGraph::GetNumVertices() const {
  return m_vertices.size();
}

int WalkGraph::GetNumEdges() const {
  return m_edges.size();
}

 
vector<WalkVertex *> WalkGraph::GetVertices() const {
  return m_vertices;
}

vector<WalkEdge *> WalkGraph::GetEdges() const {
  return m_edges;
}

/*
 * Walk() function stub
 */

vector<WalkVertex*> WalkGraph::Walk(WalkVertex *start, int maxSteps, unsigned int seed) const {
  vector<WalkVertex*> walk;
  
  /* CODE GOES HERE */
  //Add Start location to walk vertex
  walk.push_back(start);

  //Initialize random number generator
  srand(seed);

  //Start loop to limit max steps
  for (int i = 0; i < maxSteps; i++){

    //Get neighbors of start and num of neighbors
    vector<WalkVertex*> neighbors = Neighbors(start);
    int numOfNeighbors = neighbors.size();

    //Use RandomInt to decide which neighbor to walk to
    int walkChoice = RandomInt(numOfNeighbors);

    //Walk to WalkVertex in neighbors that matches walkChoice number
    start = neighbors[walkChoice];

    //Add walk destination to walk vector then check walk status
    walk.push_back(start);

    //If SUCCESS or FAILURE return walk as is, if CONTINUE do nothing
    if (start->Status() == SUCCESS || start->Status() == FAILURE){
      return walk;
    }
  }

  return walk;
}

vector<WalkVertex*> WalkGraph::Neighbors(WalkVertex* v) const {
  vector<WalkVertex*> neighbors;
  for (int i = 0; i < m_edges.size(); i++) {
    if (m_edges[i]->GetV1() == v && m_edges[i]->GetV2() != v)
      neighbors.push_back(m_edges[i]->GetV2());
    else if (m_edges[i]->GetV2() == v && m_edges[i]->GetV1() != v) 
      neighbors.push_back(m_edges[i]->GetV1());
  }
  return neighbors;
}

int WalkGraph::Locate(vector<WalkVertex*> vertices, WalkVertex* v) {
  for (int i = 0; i < vertices.size(); i++)
    if (vertices[i] == v)
      return i;
  return -1;
}

int WalkGraph::Locate(vector<WalkVertex*> vertices, int id) {
  for (int i = 0; i < vertices.size(); i++)
    if (vertices[i]->GetID() == id)
      return i;
  return -1;
}

int WalkGraph::RandomInt(int upper) {
  const int DISPOSEDBITS = 10;  // throw away low bits
  const int MAXLIMIT = (1 << (30 - DISPOSEDBITS));

  if (upper <= 0 ) {
    cerr << "Warning: WalkGraph::RandomInt: upper limit is <= zero.  Will return zero." << endl;
    return 0;
  }
  if (upper > MAXLIMIT) {
    cerr << "Warning: WalkGraph::RandomInt: upper limit is > MAXLIMIT. " 
	 << "Will return RandomInt(MAXLIMIT)." << endl;
    upper = MAXLIMIT;
  }
  
  return ((rand() >> DISPOSEDBITS) % upper);
}  
