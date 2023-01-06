#include "PathInfo.h"

void PathInfo::addEdge(GraphEdge<std::string>* edge)
{
	this->lastEdge = edge;
	this->curPath.push_back(*edge);
	this->timeTaken += edge->weight;
	this->visitedLandmarks.insert(edge->to);
}
