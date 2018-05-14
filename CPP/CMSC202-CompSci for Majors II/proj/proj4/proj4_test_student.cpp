#include <iostream>
#include <vector>
#include "WalkGraph.h"
#include "WalkEdge.h"
#include "WalkVertex.h"
#include "Intersection.h"
#include "SafeHouse.h"
#include "PoliceStation.h"
#include "/afs/umbc.edu/users/c/m/cmarron/pub/gtest-1.7.0/include/gtest/gtest.h"
//#include "../gtest-1.7.0/include/gtest/gtest.h"

using namespace std;

bool IsEdge(WalkVertex* v1, WalkVertex* v2, vector<WalkEdge*> edges);

TEST(Project4_STUDENT, WalkGraph_Walk) {

  /* Test code goes here */
  const unsigned int max_steps = 20;
  unsigned int seed = 1234;

  WalkGraph G;
  G.LoadFromFile("data/campus_v5.dat");

  vector<WalkVertex*> vertices;
  vector<WalkVertex*> walk;
  vector<WalkVertex*> walk2;
  vector<WalkEdge*> edges;

  vertices = G.GetVertices();
  edges = G.GetEdges();

  walk = G.Walk(vertices[0], max_steps, seed);
  walk2 = G.Walk(vertices[0], max_steps, seed);

  //Check that both walks are <= max_steps

  EXPECT_GE(max_steps, walk.size());
  EXPECT_GE(max_steps, walk2.size());

  // If walk ends in less than max_steps, last vertx must not
  // me an Intersection (must have ended with SUCCESS or FAILURE)

  if (walk.size() < max_steps)
    EXPECT_NE( CONTINUE, walk[walk.size() - 1]->Status() );
  if (walk2.size() < max_steps)
    EXPECT_NE( CONTINUE, walk2[walk2.size() - 1]->Status() );

  // Check that the walk is actually a walk, i.e. that the sequence
  // of vertices are all connected by edges.

  for (unsigned long i = 0; i < walk.size() - 1; i++) {
    WalkVertex* v1 = walk[i];
    WalkVertex* v2 = walk[i+1];
    EXPECT_EQ( true, IsEdge(v1, v2, edges) );
  }
  for (unsigned long i = 0; i < walk2.size() - 1; i++) {
    WalkVertex* v1 = walk2[i];
    WalkVertex* v2 = walk2[i+1];
    EXPECT_EQ( true, IsEdge(v1, v2, edges) );
  }

  //Check that the ID for each location is the same for both walks
  for (unsigned int i = 0; i < walk.size() - 1; i++) {
    int ID1 = walk[i]->GetID();
    int ID2 = walk2[i]->GetID();
    EXPECT_EQ( true, ID1 == ID2);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

bool IsEdge(WalkVertex* v1, WalkVertex* v2, vector<WalkEdge*> edges) {
  for (unsigned long i = 0; i < edges.size(); i++) {
    if ( ( v1 == edges[i]->GetV1() && v2 == edges[i]->GetV2() ) ||
         ( v1 == edges[i]->GetV2() && v2 == edges[i]->GetV1() ) )
      return true;
  }

  return false;
}
