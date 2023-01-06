#include "PathInfo.h"

void PathInfo::addEdge(GraphEdge<std::string> edge)
{
	this->lastEdge = edge.to;
	this->curPath.push_back(edge);
	this->timeTaken += edge.weight;
	this->visitedLandmarks.insert(edge.to);

	if (this->edgesVisitations.find(edge) == this->edgesVisitations.end())
	{
		this->edgesVisitations[edge] = 1;
	}
	else
	{
		this->edgesVisitations[edge] += 1;
	}
}
