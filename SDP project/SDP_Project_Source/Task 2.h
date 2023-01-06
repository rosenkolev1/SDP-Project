#pragma once
#include "UndirectedGraph.h"
#include <queue>
#include "StringManip.h"
#include <fstream>

std::vector<std::vector<GraphEdge<std::string>> > task2_getAllPathsInTime(const UndirectedGraph<std::string>& graph, std::string start, int maxTime);

std::string task2(std::ifstream& in);