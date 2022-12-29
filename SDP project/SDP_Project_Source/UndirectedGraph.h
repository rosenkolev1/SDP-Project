#pragma once

#include "GraphEdge.h"
#include <vector>
#include <map>
#include <iostream>

template <typename T>
class UndirectedGraph
{
private:

	std::vector<GraphEdge<T>> edges;
	std::map<T, std::vector<GraphEdge<T>> > vertexEdges;

public:

	UndirectedGraph()
	{
		this->edges = std::vector<GraphEdge<T>>();
		this->vertexEdges = std::map<T, std::vector<GraphEdge<T>> >();
	}

	bool edgeExists(GraphEdge<T> edge) const
	{
		for (GraphEdge<T> curEdge : this->edges)
		{
			if (edge.edgeDestinationsAreSame(curEdge)) return true;
		}

		return false;
	}

	void addEdge(T from, T to, int weight)
	{
		this->addEdge(GraphEdge<T>(from, to, weight));
	}

	void addEdge(GraphEdge<T> edge)
	{
		if (this->edgeExists(edge)) return;

		this->edges.push_back(edge);

		//If from edge exists, add the edge to its edges
		if (this->vertexEdges.find(edge.from) == this->vertexEdges.end())
		{
			this->vertexEdges[edge.from] = std::vector<GraphEdge<T>>{ edge };
		}
		else
		{
			this->vertexEdges[edge.from].push_back(edge);
		}

		//If to edge exists, add the edge to its edges
		if (this->vertexEdges.find(edge.to) == this->vertexEdges.end())
		{
			this->vertexEdges[edge.to] = std::vector<GraphEdge<T>>{ edge };
		}
		else
		{
			this->vertexEdges[edge.to].push_back(edge);
		}
	}

	std::map<T, std::vector<GraphEdge<T>> > getVertexEdges() const
	{
		return this->vertexEdges;
	}

	void print(std::ostream& out) const
	{
		out << "--------------------------------------------------------" << std::endl;
		out << "The graph is: " << std::endl;
		for (int i = 0; i < this->edges.size(); i++)
		{
			auto edge = this->edges[i];
			out << edge.from << " --> " << edge.to << " | Weight: " << edge.weight << std::endl;
		}
		out << "--------------------------------------------------------" << std::endl;
	}
};