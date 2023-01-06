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

TEST_CASE("Testing task 2 where the only visited location is the Railstation because of time constraints")
{
	/*6 9
		Railstation ArtGallery 35
		Railstation RomanStadium 35
		ArtGallery DzhumayaSquare 4
		ArtGallery HistoricalMuseum 14
		ArtGallery AntiqueTheatre 7
		RomanStadium DzhumayaSquare 2
		DzhumayaSquare HistoricalMuseum 18
		HistoricalMuseum AntiqueTheatre 12
		RomanStadium HistoricalMuseum 1
		68*/

	std::string testInputFileName = "test_task2.txt";

	std::string testInput = "6 9\nRailstation ArtGallery 35\nRailstation RomanStadium 35\nArtGallery DzhumayaSquare 4\nArtGallery HistoricalMuseum 14\n";
	testInput += "ArtGallery AntiqueTheatre 7\nRomanStadium DzhumayaSquare 2\nDzhumayaSquare HistoricalMuseum 18\nHistoricalMuseum AntiqueTheatre 12\n";
	testInput += "RomanStadium HistoricalMuseum 1\n68";

	std::string actualOutput = executeTask2(testInputFileName, testInput);

	std::string expectedOutput = "Best Path: Railstation";

	REQUIRE(expectedOutput == actualOutput);
}

TEST_CASE("Testing task 2 where the only visited location is the Railstation because there are no paths from it to any other landmark")
{
	/*6 7
		ArtGallery DzhumayaSquare 4
		ArtGallery HistoricalMuseum 14
		ArtGallery AntiqueTheatre 7
		RomanStadium DzhumayaSquare 2
		DzhumayaSquare HistoricalMuseum 18
		HistoricalMuseum AntiqueTheatre 12
		RomanStadium HistoricalMuseum 1
		68*/

	std::string testInputFileName = "test_task2.txt";

	std::string testInput = "6 7\nArtGallery DzhumayaSquare 4\nArtGallery HistoricalMuseum 14\n";
	testInput += "ArtGallery AntiqueTheatre 7\nRomanStadium DzhumayaSquare 2\nDzhumayaSquare HistoricalMuseum 18\nHistoricalMuseum AntiqueTheatre 12\n";
	testInput += "RomanStadium HistoricalMuseum 1\n68";

	std::string actualOutput = executeTask2(testInputFileName, testInput);

	std::string expectedOutput = "Best Path: Railstation";

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

	std::string testInput = 
		"6 9\nRailstation ArtGallery 1\nRailstation RomanStadium 1\nArtGallery DzhumayaSquare 1\nArtGallery HistoricalMuseum 1\n";
	testInput += 
		"ArtGallery AntiqueTheatre 1\nRomanStadium DzhumayaSquare 1\nDzhumayaSquare HistoricalMuseum 1\nHistoricalMuseum AntiqueTheatre 1\n";
	testInput += "RomanStadium HistoricalMuseum 1\n68";

	std::string actualOutput = executeTask2(testInputFileName, testInput);

	std::string expectedOutput = 
		"Best Path: Railstation --> ArtGallery --> AntiqueTheatre --> HistoricalMuseum --> DzhumayaSquare --> RomanStadium --> Railstation";

	REQUIRE(expectedOutput == actualOutput);
}

TEST_CASE("Testing task 2 where there are many useless paths after already visiting every landmark possible, but one of the paths is really long")
{
	/*6 9
		Railstation ArtGallery 1
		Railstation RomanStadium 1
		ArtGallery DzhumayaSquare 1
		ArtGallery HistoricalMuseum 1
		ArtGallery AntiqueTheatre 1
		RomanStadium DzhumayaSquare 1
		DzhumayaSquare HistoricalMuseum 1
		HistoricalMuseum AntiqueTheatre 70
		RomanStadium HistoricalMuseum 1
		68*/

	std::string testInputFileName = "test_task2.txt";

	std::string testInput =
		"6 9\nRailstation ArtGallery 1\nRailstation RomanStadium 1\nArtGallery DzhumayaSquare 1\nArtGallery HistoricalMuseum 1\n";
	testInput +=
		"ArtGallery AntiqueTheatre 1\nRomanStadium DzhumayaSquare 1\nDzhumayaSquare HistoricalMuseum 1\nHistoricalMuseum AntiqueTheatre 70\n";
	testInput += "RomanStadium HistoricalMuseum 1\n68";

	std::string actualOutput = executeTask2(testInputFileName, testInput);

	std::string expectedOutput =
		"Best Path: Railstation --> RomanStadium --> DzhumayaSquare --> HistoricalMuseum --> ArtGallery --> AntiqueTheatre --> ArtGallery"
		+ std::string(" --> Railstation");

	REQUIRE(expectedOutput == actualOutput);
}

TEST_CASE("Testing task 2 where one of the locations is practically inaccessible because it's paths take too long")
{
	/*6 9
		Railstation ArtGallery 1
		Railstation RomanStadium 1
		ArtGallery DzhumayaSquare 1
		ArtGallery HistoricalMuseum 70
		ArtGallery AntiqueTheatre 1
		RomanStadium DzhumayaSquare 1
		DzhumayaSquare HistoricalMuseum 70
		HistoricalMuseum AntiqueTheatre 70
		RomanStadium HistoricalMuseum 70
		68*/

	std::string testInputFileName = "test_task2.txt";

	std::string testInput =
		"6 9\nRailstation ArtGallery 1\nRailstation RomanStadium 1\nArtGallery DzhumayaSquare 1\nArtGallery HistoricalMuseum 70\n";
	testInput +=
		"ArtGallery AntiqueTheatre 1\nRomanStadium DzhumayaSquare 1\nDzhumayaSquare HistoricalMuseum 70\nHistoricalMuseum AntiqueTheatre 70\n";
	testInput += "RomanStadium HistoricalMuseum 70\n68";

	std::string actualOutput = executeTask2(testInputFileName, testInput);

	std::string expectedOutput =
		"Best Path: Railstation --> ArtGallery --> AntiqueTheatre --> ArtGallery --> DzhumayaSquare --> RomanStadium"
		+ std::string(" --> Railstation");

	REQUIRE(expectedOutput == actualOutput);
}

TEST_CASE("Testing task 2 where there are many useless paths after already visiting all but 1 landmarks, because the last one takes too long to visit from the starting point")
{
	/*7 10
		Railstation ArtGallery 1
		Railstation RomanStadium 1
		ArtGallery DzhumayaSquare 1
		ArtGallery HistoricalMuseumCopy 1
		ArtGallery AntiqueTheatre 1
		RomanStadium DzhumayaSquare 1
		DzhumayaSquare HistoricalMuseumCopy 1
		HistoricalMuseumCopy RomanStadium 1
		HistoricalMuseumCopy AntiqueTheatre 1
		Railstation HistoricalMuseum 69
		68*/

	std::string testInputFileName = "test_task2.txt";

	std::string testInput =
		"7 10\nRailstation ArtGallery 1\nRailstation RomanStadium 1\nArtGallery DzhumayaSquare 1\nArtGallery HistoricalMuseumCopy 1\n";
	testInput +=
		"ArtGallery AntiqueTheatre 1\nRomanStadium DzhumayaSquare 1\nDzhumayaSquare HistoricalMuseumCopy 1\n"
		+ std::string("HistoricalMuseumCopy RomanStadium 1\nHistoricalMuseumCopy AntiqueTheatre 1\n");
	testInput += "Railstation HistoricalMuseum 69\n68";

	std::string actualOutput = executeTask2(testInputFileName, testInput);

	std::string expectedOutput =
		"Best Path: Railstation --> ArtGallery --> AntiqueTheatre --> HistoricalMuseumCopy --> DzhumayaSquare --> RomanStadium"
		+ std::string(" --> Railstation");

	REQUIRE(expectedOutput == actualOutput);
}

//Extreme stress test
//TEST_CASE("Testing task 2 where there are many useless paths after already visiting all but 1 landmarks and all the visited landmarks have paths between eachother")
//{
//	/*7 16
//		Railstation ArtGallery 1
//		Railstation RomanStadium 1
//		Railstation DzhumayaSquare 1
//		Railstation HistoricalMuseumCopy 1
//		Railstation AntiqueTheatre 1
//		RomanStadium DzhumayaSquare 1
//		RomanStadium HistoricalMuseumCopy 1
//		RomanStadium ArtGallery 1
//		RomanStadium AntiqueTheatre 1
//		ArtGallery DzhumayaSquare 1
//		ArtGallery HistoricalMuseumCopy 1
//		ArtGallery AntiqueTheatre 1
//		DzhumayaSquare HistoricalMuseumCopy 1
//		DzhumayaSquare AntiqueTheatre 1
//		HistoricalMuseumCopy AntiqueTheatre 1
//		Railstation HistoricalMuseum 69
//		68*/
//
//	std::string testInputFileName = "test_task2.txt";
//
//	std::string testInput = std::string("7 16\n") +
//		"Railstation ArtGallery 1\n" +
//		"Railstation RomanStadium 1\n" +
//		"Railstation DzhumayaSquare 1\n" +
//		"Railstation HistoricalMuseumCopy 1\n" +
//		"Railstation AntiqueTheatre 1\n" +
//		"RomanStadium DzhumayaSquare 1\n" +
//		"RomanStadium HistoricalMuseumCopy 1\n" +
//		"RomanStadium ArtGallery 1\n" +
//		"RomanStadium AntiqueTheatre 1\n" +
//		"ArtGallery DzhumayaSquare 1\n" +
//		"ArtGallery HistoricalMuseumCopy 1\n" +
//		"ArtGallery AntiqueTheatre 1\n" +
//		"DzhumayaSquare HistoricalMuseumCopy 1\n" +
//		"DzhumayaSquare AntiqueTheatre 1\n" +
//		"HistoricalMuseumCopy AntiqueTheatre 1\n" +
//		"Railstation HistoricalMuseum 69\n";
//	testInput += "68";
//
//	std::string actualOutput = executeTask2(testInputFileName, testInput);
//
//	std::string expectedOutput =
//		"Best Path: Railstation --> ArtGallery --> RomanStadium --> DzhumayaSquare --> HistoricalMuseumCopy --> AntiqueTheatre"
//		+ std::string(" --> Railstation");
//
//	REQUIRE(expectedOutput == actualOutput);
//}