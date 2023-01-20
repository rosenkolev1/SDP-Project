#include "doctest.h"
#include <iostream>
#include "../SDP_Project_Source/GraphEdge.h"

TEST_CASE("Test edgesAreEqual method")
{
	auto first = GraphEdge<std::string>("firstDestination", "secondDestination", 10);
	auto second = GraphEdge<std::string>("firstDestination", "secondDestination", 10);

	CHECK(first.edgesAreEqual(second));

	second = GraphEdge<std::string>("firstDestination", "secondDestination", 9);
	CHECK_FALSE(first.edgesAreEqual(second));

	second = GraphEdge<std::string>("firstDestination", "secondDestinationHAHA", 10);
	CHECK_FALSE(first.edgesAreEqual(second));

	second = GraphEdge<std::string>("firstDestinationHAHA", "secondDestination", 10);
	CHECK_FALSE(first.edgesAreEqual(second));

	second = GraphEdge<std::string>("secondDestination", "firstDestination", 10);
	CHECK_FALSE(first.edgesAreEqual(second));
}

TEST_CASE("Test edgeDestinationsAreSame method")
{
	auto first = GraphEdge<std::string>("firstDestination", "secondDestination", 10);
	auto second = GraphEdge<std::string>("firstDestination", "secondDestination", 7);

	CHECK(first.edgeDestinationsAreSame(second));

	second = GraphEdge<std::string>("secondDestination", "firstDestination", 7);
	CHECK(first.edgeDestinationsAreSame(second));

	second = GraphEdge<std::string>("firstDestinationHAHA", "secondDestination", 10);
	CHECK_FALSE(first.edgeDestinationsAreSame(second));

	second = GraphEdge<std::string>("firstDestination", "secondDestinationHAHA", 10);
	CHECK_FALSE(first.edgeDestinationsAreSame(second));
}
