/**
 * @file NetworkFlow.cpp
 * CS 225: Data Structures
 */

#include <vector>
#include <algorithm>
#include <set>

#include "graph.h"
#include "edge.h"

#include "NetworkFlow.h"

int min(int a, int b) {
  if (a<b)
    return a;
  else return b;
}

NetworkFlow::NetworkFlow(Graph & startingGraph, Vertex source, Vertex sink) :
  g_(startingGraph), residual_(Graph(true,true)), flow_(Graph(true,true)), source_(source), sink_(sink) {

  //
  /*for (Vertex v: startingGraph.getVertices())
  {
   
    flow_.insertVertex(v);
    residual_.insertVertex(v);
  }*/
  for (Edge e: startingGraph.getEdges())
  {
    residual_.insertEdge(e.source, e.dest);
    residual_.insertEdge(e.dest, e.source);//
    residual_.setEdgeWeight(e.source, e.dest, e.getWeight());
   
    residual_.setEdgeWeight(e.dest, e.source, 0);
    flow_.insertEdge(e.source, e.dest);
    flow_.setEdgeWeight(e.source, e.dest, 0);
   
  }
  // YOUR CODE HERE
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the helper function.
   *
   * @param source  The starting (current) vertex
   * @param sink    The destination vertex
   * @param path    The vertices in the path
   * @param visited A set of vertices we have visited
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink,
  std::vector<Vertex> &path, std::set<Vertex> &visited) {

  if (visited.count(source) != 0)
    return false;
  visited.insert(source);

  if (source == sink) {
    return true;
  }

  vector<Vertex> adjs = residual_.getAdjacent(source);
  for(auto it = adjs.begin(); it != adjs.end(); it++) {
    if (visited.count(*it) == 0 && residual_.getEdgeWeight(source,*it) > 0) {
      path.push_back(*it);
      if (findAugmentingPath(*it,sink,path,visited))
        return true;
      else {
        path.pop_back();
      }
    }
  }

  return false;
}

  /**
   * findAugmentingPath - use DFS to find a path in the residual graph with leftover capacity.
   *  This version is the main function.  It initializes a set to keep track of visited vertices.
   *
   * @param source The starting (current) vertex
   * @param sink   The destination vertex
   * @param path   The vertices in the path
   */

bool NetworkFlow::findAugmentingPath(Vertex source, Vertex sink, std::vector<Vertex> &path) {
   std::set<Vertex> visited;
   path.clear();
   path.push_back(source);
   return findAugmentingPath(source,sink,path,visited);
}

  /**
   * pathCapacity - Determine the capacity of a path in the residual graph.
   *
   * @param path   The vertices in the path
   */

int NetworkFlow::pathCapacity(const std::vector<Vertex> & path) const
  {
    // YOUR CODE HERE
   
    int a = 100000;
   
    for (int i = 0; i < (int)path.size() - 1; i++)
      {
      int b = residual_.getEdgeWeight(path[i], path[i+1]);
      if (b < a) {
        a = b;
      }
    }
    return a;
}

  /**
   * calculuateFlow - Determine the capacity of a path in the residual graph.
   * Sets the member function `maxFlow_` to be the flow, and updates the
   * residual graph and flow graph according to the algorithm.
   *
   * @return The network flow graph.
   */

const Graph & NetworkFlow::calculateFlow()
{
  std::vector<Vertex> path;
  int max = 0;
  while (findAugmentingPath(source_, sink_, path))
  {
    int capacity = pathCapacity(path);
    max += capacity;
    for (int i = 0; i < (int)path.size() - 1; i++)
    {
      Vertex curr = path[i];
      Vertex next = path[i + 1];
     
      if (flow_.edgeExists(curr, next))
      {
        flow_.setEdgeWeight(curr, next, capacity + flow_.getEdgeWeight(curr, next));
      } else
      {
        flow_.setEdgeWeight(next, curr, flow_.getEdgeWeight(next, curr) - capacity);
      }
      residual_.setEdgeWeight(curr, next, residual_.getEdgeWeight(curr, next) - capacity);
      residual_.setEdgeWeight(next, curr, residual_.getEdgeWeight(next, curr) + capacity);
    }
  }
  maxFlow_ = max;
  return flow_;
   //return flow_;
}

int NetworkFlow::getMaxFlow() const {
  return maxFlow_;
}

const Graph & NetworkFlow::getGraph() const {
  return g_;
}

const Graph & NetworkFlow::getFlowGraph() const {
  return flow_;
}

const Graph & NetworkFlow::getResidualGraph() const {
  return residual_;
}

