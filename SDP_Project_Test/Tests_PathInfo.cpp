#include "doctest.h"
#include <iostream>
#include "../SDP_Project_Source/PathInfo.h"
#include <vector>

TEST_CASE("Test PathInfo constructor")
{
	auto pathInfo = PathInfo("From");

	CHECK_EQ(pathInfo.lastEdge, "From");
	CHECK_EQ(pathInfo.curPath.size(), 0);
	CHECK_EQ(pathInfo.edgesVisitations.size(), 0);
	CHECK_EQ(pathInfo.timeTaken, 0);
	CHECK_EQ(pathInfo.visitedLandmarks, std::set<std::string>{"From"});
}

TEST_CASE("Test adding and edge to the pathinfo")
{
	auto pathInfo = PathInfo("From");

	auto newEdge = GraphEdge<std::string>("From", "To", 3);
	pathInfo.addEdge(newEdge);

	auto expectedCurPath = std::vector<GraphEdge<std::string>>{ newEdge };

	auto expectedEdgeVisitations = std::unordered_map<GraphEdge<std::string>, int, PathInfo::GraphEdgeKeyHasher, PathInfo::GraphEdgeKeyEquals>
	{
		{newEdge, 1},
	};

	auto expectedVisitedLandmarks = std::set<std::string>{ "From", "To" };

	CHECK_EQ(pathInfo.lastEdge, "To");
	CHECK_EQ(pathInfo.curPath, expectedCurPath);
	CHECK_EQ(pathInfo.edgesVisitations, expectedEdgeVisitations);
	CHECK_EQ(pathInfo.timeTaken, 3);
	CHECK_EQ(pathInfo.visitedLandmarks, expectedVisitedLandmarks);

	auto newEdge2 = GraphEdge<std::string>("To", "KUUR", 25);
	pathInfo.addEdge(newEdge2);

	expectedCurPath.push_back(newEdge2);
	expectedEdgeVisitations[newEdge2] = 1;
	expectedVisitedLandmarks.insert("KUUR");

	CHECK_EQ(pathInfo.lastEdge, "KUUR");
	CHECK_EQ(pathInfo.curPath, expectedCurPath);
	CHECK_EQ(pathInfo.edgesVisitations, expectedEdgeVisitations);
	CHECK_EQ(pathInfo.timeTaken, 28);
	CHECK_EQ(pathInfo.visitedLandmarks, expectedVisitedLandmarks);

	auto newEdge3 = GraphEdge<std::string>("To", "From", 70);
	pathInfo.addEdge(newEdge3);

	expectedCurPath.push_back(newEdge3);
	expectedEdgeVisitations[newEdge3] = 2;

	CHECK_EQ(pathInfo.lastEdge, "From");
	CHECK_EQ(pathInfo.curPath, expectedCurPath);
	CHECK_EQ(pathInfo.edgesVisitations, expectedEdgeVisitations);
	CHECK_EQ(pathInfo.timeTaken, 98);
	CHECK_EQ(pathInfo.visitedLandmarks, expectedVisitedLandmarks);
}