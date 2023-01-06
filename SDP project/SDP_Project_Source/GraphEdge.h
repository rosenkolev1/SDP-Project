#pragma once

template <typename T>
struct GraphEdge
{
	T from;
	T to;
	int weight;

	GraphEdge(T from, T to)
	{
		this->from = from;
		this->to = to;
		this->weight = 0;
	}

	GraphEdge(T from, T to, int weight)
	{
		this->from = from;
		this->to = to;
		this->weight = weight;
	}

	bool edgeDestinationsAreSame(const GraphEdge<T>& other) const
	{
		return (this->to == other.to && this->from == other.from
			|| this->to == other.from && this->from == other.to);
	}

	bool edgesAreEqual(const GraphEdge<T>& other) const {
		return this->to == other.to && this->from == other.from && this->weight == other.weight;
	}
};