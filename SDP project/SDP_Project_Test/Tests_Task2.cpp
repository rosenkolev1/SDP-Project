#include "doctest.h"
#include <iostream>
#include "../SDP_Project_Source/Task 2.h"
#include <sstream>

std::string executeTask2(std::string testInputFileName, std::string testInput)
{
	std::ofstream osTest(testInputFileName);
	osTest << testInput;
	osTest.close();

	std::ifstream isTest(testInputFileName);
	std::string actualOutput = task2(isTest);
	isTest.close();

	remove(testInputFileName.c_str());

	return actualOutput;
}

TEST_CASE("Testing task 2 with default test case")
{
	/*6 8
		Railstation ArtGallery 26
		Railstation RomanStadium 20
		ArtGallery DzhumayaSquare 5
		ArtGallery HistoricalMuseum 14
		ArtGallery AntiqueTheatre 7
		RomanStadium DzhumayaSquare 2
		DzhumayaSquare HistoricalMuseum 18
		HistoricalMuseum AntiqueTheatre 12
		68*/

	std::string testInputFileName = "Plovdiv.txt";

	std::string testInput = "6 8\nRailstation ArtGallery 26\nRailstation RomanStadium 20\nArtGallery DzhumayaSquare 5\nArtGallery HistoricalMuseum 14\n";
	testInput += "ArtGallery AntiqueTheatre 7\nRomanStadium DzhumayaSquare 2\nDzhumayaSquare HistoricalMuseum 18\nHistoricalMuseum AntiqueTheatre 12\n";
	testInput += "68";

	std::string actualOutput = executeTask2(testInputFileName, testInput);

	std::string expectedOutput = "Best Path: Railstation --> ArtGallery --> AntiqueTheatre --> ArtGallery --> DzhumayaSquare --> RomanStadium --> Railstation";

	REQUIRE(expectedOutput == actualOutput);
}

TEST_CASE("Testing task 2 where there are many useless paths which cycle back and forth between 2 already visited landmarks")
{
	/*6 9
		Railstation ArtGallery 26
		Railstation RomanStadium 20
		ArtGallery DzhumayaSquare 4
		ArtGallery HistoricalMuseum 14
		ArtGallery AntiqueTheatre 7
		RomanStadium DzhumayaSquare 2
		DzhumayaSquare HistoricalMuseum 18
		HistoricalMuseum AntiqueTheatre 12
		RomanStadium HistoricalMuseum 1
		68*/

	std::string testInputFileName = "test_task2.txt";

	std::string testInput = "6 9\nRailstation ArtGallery 26\nRailstation RomanStadium 20\nArtGallery DzhumayaSquare 4\nArtGallery HistoricalMuseum 14\n";
	testInput += "ArtGallery AntiqueTheatre 7\nRomanStadium DzhumayaSquare 2\nDzhumayaSquare HistoricalMuseum 18\nHistoricalMuseum AntiqueTheatre 12\n";
	testInput += "RomanStadium HistoricalMuseum 1\n68";

	std::string actualOutput = executeTask2(testInputFileName, testInput);

	std::string expectedOutput = "Best Path: Railstation --> RomanStadium --> DzhumayaSquare --> ArtGallery --> AntiqueTheatre --> HistoricalMuseum --> RomanStadium --> Railstation";

	REQUIRE(expectedOutput == actualOutput);
}

TEST_CASE("Testing task 2 where there are many useless paths after already visiting every landmark possible")
{
	/*6 9
		Railstation ArtGallery 1
		Railstation RomanStadium 1
		ArtGallery DzhumayaSquare 1
		ArtGallery HistoricalMuseum 1
		ArtGallery AntiqueTheatre 1
		RomanStadium DzhumayaSquare 1
		DzhumayaSquare HistoricalMuseum 1
		HistoricalMuseum AntiqueTheatre 1
		RomanStadium HistoricalMuseum 1
		68*/

	std::string testInputFileName = "test_task2.txt";

	std::string testInput = "6 9\nRailstation ArtGallery 1\nRailstation RomanStadium 1\nArtGallery DzhumayaSquare 1\nArtGallery HistoricalMuseum 1\n";
	testInput += "ArtGallery AntiqueTheatre 1\nRomanStadium DzhumayaSquare 1\nDzhumayaSquare HistoricalMuseum 1\nHistoricalMuseum AntiqueTheatre 1\n";
	testInput += "RomanStadium HistoricalMuseum 1\n68";

	std::string actualOutput = executeTask2(testInputFileName, testInput);

	std::string expectedOutput = "Best Path: Railstation --> RomanStadium --> DzhumayaSquare --> ArtGallery --> AntiqueTheatre --> HistoricalMuseum --> RomanStadium --> Railstation";

	REQUIRE(expectedOutput == actualOutput);
}