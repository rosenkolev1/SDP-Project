#pragma once
#include <vector>
#include <string>
#include "GraphEdge.h"
#include <set>
#include <map>
#include <unordered_map>

class PathInfo {
public:

	struct GraphEdgeKeyHasher
	{
		std::size_t operator()(const GraphEdge<std::string>& k) const
		{
			auto hash1 = std::hash<std::string>{}(k.from);
			auto hash2 = std::hash<std::string>{}(k.to);

			if (hash1 != hash2) {
				return hash1 ^ hash2;
			}

			//1 1 0
			//0 0 1
			//1 1 1

			//1 0 0
			//0 1 1
			//1 1 1

			// If hash1 == hash2, their XOR is zero.
			return hash1;
		}
	};

	struct GraphEdgeKeyEquals
	{
		bool operator() (const GraphEdge<std::string>& t1, const GraphEdge<std::string>& t2) const
		{
			return t1.edgeDestinationsAreSame(t2);
		}
	};

	std::vector<GraphEdge<std::string>> curPath;
	std::string lastEdge;

	std::set<std::string> visitedLandmarks;
	std::unordered_map<GraphEdge<std::string>, int, GraphEdgeKeyHasher, GraphEdgeKeyEquals> edgesVisitations;

	int timeTaken;
	
	PathInfo()
	{
		this->curPath = std::vector<GraphEdge<std::string>>();
		this->lastEdge = "Railstation";

		this->visitedLandmarks = std::set<std::string> {
			"Railstation"
		};
		this->edgesVisitations = std::unordered_map<GraphEdge<std::string>, int, GraphEdgeKeyHasher, GraphEdgeKeyEquals>();

		this->timeTaken = 0;
	}

	void addEdge(GraphEdge<std::string> edge);
};
