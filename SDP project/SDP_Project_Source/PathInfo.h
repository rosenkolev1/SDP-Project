#pragma once
#include <vector>
#include <string>
#include "GraphEdge.h"
#include <set>

class PathInfo {
public:

	std::vector<GraphEdge<std::string>> curPath;
	GraphEdge<std::string>* lastEdge;
	std::set<std::string> visitedLandmarks;
	int timeTaken;
	
	PathInfo()
	{
		this->curPath = std::vector<GraphEdge<std::string>>();
		this->timeTaken = 0;
		this->visitedLandmarks = std::set<std::string> {
			"Railstation"
		};
		this->lastEdge = nullptr;
	}

	void addEdge(GraphEdge<std::string>* edge);
};
