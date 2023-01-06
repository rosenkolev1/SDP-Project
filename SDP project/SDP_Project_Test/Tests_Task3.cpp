#include "doctest.h"
#include <iostream>
#include "../SDP_Project_Source/Task 3.h"
#include <sstream>
#include <vector>
#include "../SDP_Project_Source/Box.h"
#include "TestCasesUtil.h"

std::string executeTask3(std::string testInputFileName, std::string testInput)
{
	std::ofstream osTest(testInputFileName);
	osTest << testInput;
	osTest.close();

	std::ifstream isTest(testInputFileName);
	std::string actualOutput = task3(isTest);
	isTest.close();

	remove(testInputFileName.c_str());

	return actualOutput;
}

TEST_CASE(TestCasesUtil::testCasesStrings.at(TestCasesUtil::TESTS_TASK3)(1))
{
	/*
	10
	PlovdivBox 2 Magnet Book 2 ArtBox TheatreBox
	ArtBox 0 1 Drawings
	Drawings 1 OldPlovdiv 0
	TheatreBox 0 1 TheatreSouvenirs
	TheatreSouvenirs 0 2 Plates Bags
	Plates 1 DecorativePlate 0
	Bags 0 0
	StaraZagoraBox 1 Postcard 2 Figurines Cups
	Figurines 1 AncientFigurine 0
	Cups 1 TraditionalCup 0
	*/
	std::string input = std::string("10\n") +
		"PlovdivBox 2 Magnet Book 2 ArtBox TheatreBox\n" +
		"ArtBox 0 1 Drawings\n" +
		"Drawings 1 OldPlovdiv 0\n" +
		"TheatreBox 0 1 TheatreSouvenirs\n" +
		"TheatreSouvenirs 0 2 Plates Bags\n" +
		"Plates 1 DecorativePlate 0\n" +
		"Bags 0 0\n" +
		"StaraZagoraBox 1 Postcard 2 Figurines Cups\n" +
		"Figurines 1 AncientFigurine 0\n" +
		"Cups 1 TraditionalCup 0\n";

	std::string testInputFileName = "test_task3.txt";

	auto plates = std::make_shared<Box>("Plates",
		std::vector<std::string>{"DecorativePlate"}, std::vector<std::shared_ptr<Box>>());

	auto bags = std::make_shared<Box>("Bags",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>());

	auto theatreSouvenirs = std::make_shared<Box>("TheatreSouvenirs",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> {plates, bags});

	auto theatreBox = std::make_shared<Box>("TheatreBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{ theatreSouvenirs });

	auto drawings = std::make_shared<Box>("Drawings",
		std::vector<std::string>{"OldPlovdiv"}, std::vector<std::shared_ptr<Box>>());

	auto artBox = std::make_shared<Box>("ArtBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> { drawings});

	auto plovdivBox = std::make_shared<Box>("PlovdivBox",
		std::vector<std::string>{"Magnet", "Book"},
		std::vector<std::shared_ptr<Box>> {artBox, theatreBox});

	auto figurines = std::make_shared<Box>("Figurines",
		std::vector<std::string> {"AncientFigurine"}, std::vector<std::shared_ptr<Box>>());

	auto cups = std::make_shared<Box>("Cups",
		std::vector<std::string> {"TraditionalCup"}, std::vector<std::shared_ptr<Box>>());

	auto staraZagoraBox = std::make_shared<Box>("StaraZagoraBox",
		std::vector<std::string> {"Postcard"}, std::vector<std::shared_ptr<Box>> {figurines, cups});

	plovdivBox->simplifyBox();
	staraZagoraBox->simplifyBox();

	std::string expectedOutput = plovdivBox->toString() + staraZagoraBox->toString();

	std::string output = executeTask3(testInputFileName, input);

	CHECK_EQ(expectedOutput, output);
}

TEST_CASE(TestCasesUtil::testCasesStrings.at(TestCasesUtil::TESTS_TASK3)(2))
{
	/*
	19
	PlovdivBox 2 Magnet Book 2 ArtBox TheatreBox
	ArtBox 0 1 Drawings
	Drawings 0 1 DrawingsNested1
	DrawingsNested1 0 1 DrawingsNested2
	DrawingsNested2 1 OldPlovdiv 0
	TheatreBox 0 1 TheatreSouvenirs
	TheatreSouvenirs 0 3 Plates Bags SouvenirsNested1
	Plates 1 DecorativePlate 0
	Bags 1 BagsSouvenir 1 BagsNested1
	BagsNested1 0 1 BagsNested2
	BagsNested2 0 1 BagsNested3
	BagsNested3 0 0
	SouvenirsNested1 0 1 SouvenirsNested2
	SouvenirsNested2 0 1 SouvenirsNested3
	SouvenirsNested3 0 1 SouvenirsNested4
	SouvenirsNested4 1 NestedSouvenirItem 0
	StaraZagoraBox 1 Postcard 2 Figurines Cups
	Figurines 1 AncientFigurine 0
	Cups 1 TraditionalCup 0
	*/
	std::string input = std::string("19\n") +
		"PlovdivBox 2 Magnet Book 2 ArtBox TheatreBox\n" +
		"ArtBox 0 1 Drawings\n" +
		"Drawings 0 1 DrawingsNested1\n" +
		"DrawingsNested1 0 1 DrawingsNested2\n" +
		"DrawingsNested2 1 OldPlovdiv 0\n" +
		"TheatreBox 0 1 TheatreSouvenirs\n" +
		"TheatreSouvenirs 0 3 Plates Bags SouvenirsNested1\n" +
		"Plates 1 DecorativePlate 0\n" +
		"Bags 1 BagsSouvenir 1 BagsNested1\n" +
		"BagsNested1 0 1 BagsNested2\n" +
		"BagsNested2 0 1 BagsNested3\n" +
		"BagsNested3 0 0\n" +
		"SouvenirsNested1 0 1 SouvenirsNested2\n" +
		"SouvenirsNested2 0 1 SouvenirsNested3\n" +
		"SouvenirsNested3 0 1 SouvenirsNested4\n" +
		"SouvenirsNested4 1 NestedSouvenirItem 0\n" +
		"StaraZagoraBox 1 Postcard 2 Figurines Cups\n" +
		"Figurines 1 AncientFigurine 0\n" +
		"Cups 1 TraditionalCup 0\n";

	std::string testInputFileName = "test_task3.txt";

	auto plates = std::make_shared<Box>("Plates",
		std::vector<std::string>{"DecorativePlate"}, std::vector<std::shared_ptr<Box>>());

	auto bagsNested3 = std::make_shared<Box>("BagsNested3",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>());

	auto souvenirsNested4 = std::make_shared<Box>("SouvenirsNested4",
		std::vector<std::string>{"NestedSouvenirItem"}, std::vector<std::shared_ptr<Box>>());

	auto bagsNested2 = std::make_shared<Box>("BagsNested2",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{bagsNested3});

	auto souvenirsNested3 = std::make_shared<Box>("SouvenirsNested3",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested4});

	auto bagsNested1 = std::make_shared<Box>("BagsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{bagsNested2});

	auto souvenirsNested2 = std::make_shared<Box>("SouvenirsNested2",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested3});

	auto bags = std::make_shared<Box>("Bags",
		std::vector<std::string>{"BagsSouvenir"}, std::vector<std::shared_ptr<Box>>{bagsNested1});

	auto souvenirsNested1 = std::make_shared<Box>("SouvenirsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested2});

	auto theatreSouvenirs = std::make_shared<Box>("TheatreSouvenirs",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> {plates, bags, souvenirsNested1});

	auto theatreBox = std::make_shared<Box>("TheatreBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{ theatreSouvenirs });

	auto drawingsNested2 = std::make_shared<Box>("DrawingsNested2",
		std::vector<std::string>{"OldPlovdiv"}, std::vector<std::shared_ptr<Box>>());

	auto drawingsNested1 = std::make_shared<Box>("DrawingsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{drawingsNested2});

	auto drawings = std::make_shared<Box>("Drawings",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{drawingsNested1});

	auto artBox = std::make_shared<Box>("ArtBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> { drawings});

	auto plovdivBox = std::make_shared<Box>("PlovdivBox",
		std::vector<std::string>{"Magnet", "Book"},
		std::vector<std::shared_ptr<Box>> {artBox, theatreBox});

	auto figurines = std::make_shared<Box>("Figurines",
		std::vector<std::string> {"AncientFigurine"}, std::vector<std::shared_ptr<Box>>());

	auto cups = std::make_shared<Box>("Cups",
		std::vector<std::string> {"TraditionalCup"}, std::vector<std::shared_ptr<Box>>());

	auto staraZagoraBox = std::make_shared<Box>("StaraZagoraBox",
		std::vector<std::string> {"Postcard"}, std::vector<std::shared_ptr<Box>> {figurines, cups});

	plovdivBox->simplifyBox();
	staraZagoraBox->simplifyBox();

	std::string expectedOutput = plovdivBox->toString() + staraZagoraBox->toString();

	std::string output = executeTask3(testInputFileName, input);

	CHECK_EQ(expectedOutput, output);
}

TEST_CASE(TestCasesUtil::testCasesStrings.at(TestCasesUtil::TESTS_TASK3)(3))
{
	/*
	19
	PlovdivBox 2 Magnet Book 2 ArtBox TheatreBox
	ArtBox 0 1 Drawings
	Drawings 0 1 DrawingsNested1
	DrawingsNested1 0 1 DrawingsNested2
	DrawingsNested2 1 OldPlovdiv 0
	TheatreBox 0 1 TheatreSouvenirs
	TheatreSouvenirs 0 3 Plates Bags SouvenirsNested1
	Plates 1 DecorativePlate 0
	Bags 1 BagsSouvenir 1 BagsNested1
	BagsNested1 1 BagsSouvenirNested1 1 BagsNested2
	BagsNested2 0 1 BagsNested3
	BagsNested3 0 0
	SouvenirsNested1 0 1 SouvenirsNested2
	SouvenirsNested2 0 1 SouvenirsNested3
	SouvenirsNested3 0 1 SouvenirsNested4
	SouvenirsNested4 1 NestedSouvenirItem 0
	StaraZagoraBox 1 Postcard 2 Figurines Cups
	Figurines 1 AncientFigurine 0
	Cups 1 TraditionalCup 0
	*/
	std::string input = std::string("19\n") +
		"PlovdivBox 2 Magnet Book 2 ArtBox TheatreBox\n" +
		"ArtBox 0 1 Drawings\n" +
		"Drawings 0 1 DrawingsNested1\n" +
		"DrawingsNested1 0 1 DrawingsNested2\n" +
		"DrawingsNested2 1 OldPlovdiv 0\n" +
		"TheatreBox 0 1 TheatreSouvenirs\n" +
		"TheatreSouvenirs 0 3 Plates Bags SouvenirsNested1\n" +
		"Plates 1 DecorativePlate 0\n" +
		"Bags 1 BagsSouvenir 1 BagsNested1\n" +
		"BagsNested1 1 BagsSouvenirNested1 1 BagsNested2\n" +
		"BagsNested2 0 1 BagsNested3\n" +
		"BagsNested3 0 0\n" +
		"SouvenirsNested1 0 1 SouvenirsNested2\n" +
		"SouvenirsNested2 0 1 SouvenirsNested3\n" +
		"SouvenirsNested3 0 1 SouvenirsNested4\n" +
		"SouvenirsNested4 1 NestedSouvenirItem 0\n" +
		"StaraZagoraBox 1 Postcard 2 Figurines Cups\n" +
		"Figurines 1 AncientFigurine 0\n" +
		"Cups 1 TraditionalCup 0\n";

	std::string testInputFileName = "test_task3.txt";

	auto plates = std::make_shared<Box>("Plates",
		std::vector<std::string>{"DecorativePlate"}, std::vector<std::shared_ptr<Box>>());

	auto bagsNested3 = std::make_shared<Box>("BagsNested3",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>());

	auto souvenirsNested4 = std::make_shared<Box>("SouvenirsNested4",
		std::vector<std::string>{"NestedSouvenirItem"}, std::vector<std::shared_ptr<Box>>());

	auto bagsNested2 = std::make_shared<Box>("BagsNested2",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{bagsNested3});

	auto souvenirsNested3 = std::make_shared<Box>("SouvenirsNested3",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested4});

	auto bagsNested1 = std::make_shared<Box>("BagsNested1",
		std::vector<std::string>{"BagsSouvenirNested1"}, std::vector<std::shared_ptr<Box>>{bagsNested2});

	auto souvenirsNested2 = std::make_shared<Box>("SouvenirsNested2",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested3});

	auto bags = std::make_shared<Box>("Bags",
		std::vector<std::string>{"BagsSouvenir"}, std::vector<std::shared_ptr<Box>>{bagsNested1});

	auto souvenirsNested1 = std::make_shared<Box>("SouvenirsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested2});

	auto theatreSouvenirs = std::make_shared<Box>("TheatreSouvenirs",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> {plates, bags, souvenirsNested1});

	auto theatreBox = std::make_shared<Box>("TheatreBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{ theatreSouvenirs });

	auto drawingsNested2 = std::make_shared<Box>("DrawingsNested2",
		std::vector<std::string>{"OldPlovdiv"}, std::vector<std::shared_ptr<Box>>());

	auto drawingsNested1 = std::make_shared<Box>("DrawingsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{drawingsNested2});

	auto drawings = std::make_shared<Box>("Drawings",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{drawingsNested1});

	auto artBox = std::make_shared<Box>("ArtBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> { drawings});

	auto plovdivBox = std::make_shared<Box>("PlovdivBox",
		std::vector<std::string>{"Magnet", "Book"},
		std::vector<std::shared_ptr<Box>> {artBox, theatreBox});

	auto figurines = std::make_shared<Box>("Figurines",
		std::vector<std::string> {"AncientFigurine"}, std::vector<std::shared_ptr<Box>>());

	auto cups = std::make_shared<Box>("Cups",
		std::vector<std::string> {"TraditionalCup"}, std::vector<std::shared_ptr<Box>>());

	auto staraZagoraBox = std::make_shared<Box>("StaraZagoraBox",
		std::vector<std::string> {"Postcard"}, std::vector<std::shared_ptr<Box>> {figurines, cups});

	plovdivBox->simplifyBox();
	staraZagoraBox->simplifyBox();

	std::string expectedOutput = plovdivBox->toString() + staraZagoraBox->toString();

	std::string output = executeTask3(testInputFileName, input);

	CHECK_EQ(expectedOutput, output);
}

TEST_CASE(TestCasesUtil::testCasesStrings.at(TestCasesUtil::TESTS_TASK3)(4))
{
	/*
	19
	PlovdivBox 2 Magnet Book 2 ArtBox TheatreBox
	ArtBox 0 1 Drawings
	Drawings 0 1 DrawingsNested1
	DrawingsNested1 0 1 DrawingsNested2
	DrawingsNested2 1 OldPlovdiv 0
	TheatreBox 0 1 TheatreSouvenirs
	TheatreSouvenirs 0 3 Plates Bags SouvenirsNested1
	Plates 1 DecorativePlate 0
	Bags 1 BagsSouvenir 1 BagsNested1
	BagsNested1 0 1 BagsNested2
	BagsNested2 1 BagsSouvenirNested2 1 BagsNested3
	BagsNested3 0 0
	SouvenirsNested1 0 1 SouvenirsNested2
	SouvenirsNested2 0 1 SouvenirsNested3
	SouvenirsNested3 0 1 SouvenirsNested4
	SouvenirsNested4 1 NestedSouvenirItem 0
	StaraZagoraBox 1 Postcard 2 Figurines Cups
	Figurines 1 AncientFigurine 0
	Cups 1 TraditionalCup 0
	*/
	std::string input = std::string("19\n") +
		"PlovdivBox 2 Magnet Book 2 ArtBox TheatreBox\n" +
		"ArtBox 0 1 Drawings\n" +
		"Drawings 0 1 DrawingsNested1\n" +
		"DrawingsNested1 0 1 DrawingsNested2\n" +
		"DrawingsNested2 1 OldPlovdiv 0\n" +
		"TheatreBox 0 1 TheatreSouvenirs\n" +
		"TheatreSouvenirs 0 3 Plates Bags SouvenirsNested1\n" +
		"Plates 1 DecorativePlate 0\n" +
		"Bags 1 BagsSouvenir 1 BagsNested1\n" +
		"BagsNested1 0 1 BagsNested2\n" +
		"BagsNested2 1 BagsSouvenirNested2 1 BagsNested3\n" +
		"BagsNested3 0 0\n" +
		"SouvenirsNested1 0 1 SouvenirsNested2\n" +
		"SouvenirsNested2 0 1 SouvenirsNested3\n" +
		"SouvenirsNested3 0 1 SouvenirsNested4\n" +
		"SouvenirsNested4 1 NestedSouvenirItem 0\n" +
		"StaraZagoraBox 1 Postcard 2 Figurines Cups\n" +
		"Figurines 1 AncientFigurine 0\n" +
		"Cups 1 TraditionalCup 0\n";

	std::string testInputFileName = "test_task3.txt";

	auto plates = std::make_shared<Box>("Plates",
		std::vector<std::string>{"DecorativePlate"}, std::vector<std::shared_ptr<Box>>());

	auto bagsNested3 = std::make_shared<Box>("BagsNested3",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>());

	auto souvenirsNested4 = std::make_shared<Box>("SouvenirsNested4",
		std::vector<std::string>{"NestedSouvenirItem"}, std::vector<std::shared_ptr<Box>>());

	auto bagsNested2 = std::make_shared<Box>("BagsNested2",
		std::vector<std::string>{"BagsSouvenirNested2"}, std::vector<std::shared_ptr<Box>>{bagsNested3});

	auto souvenirsNested3 = std::make_shared<Box>("SouvenirsNested3",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested4});

	auto bagsNested1 = std::make_shared<Box>("BagsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{bagsNested2});

	auto souvenirsNested2 = std::make_shared<Box>("SouvenirsNested2",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested3});

	auto bags = std::make_shared<Box>("Bags",
		std::vector<std::string>{"BagsSouvenir"}, std::vector<std::shared_ptr<Box>>{bagsNested1});

	auto souvenirsNested1 = std::make_shared<Box>("SouvenirsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested2});

	auto theatreSouvenirs = std::make_shared<Box>("TheatreSouvenirs",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> {plates, bags, souvenirsNested1});

	auto theatreBox = std::make_shared<Box>("TheatreBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{ theatreSouvenirs });

	auto drawingsNested2 = std::make_shared<Box>("DrawingsNested2",
		std::vector<std::string>{"OldPlovdiv"}, std::vector<std::shared_ptr<Box>>());

	auto drawingsNested1 = std::make_shared<Box>("DrawingsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{drawingsNested2});

	auto drawings = std::make_shared<Box>("Drawings",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{drawingsNested1});

	auto artBox = std::make_shared<Box>("ArtBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> { drawings});

	auto plovdivBox = std::make_shared<Box>("PlovdivBox",
		std::vector<std::string>{"Magnet", "Book"},
		std::vector<std::shared_ptr<Box>> {artBox, theatreBox});

	auto figurines = std::make_shared<Box>("Figurines",
		std::vector<std::string> {"AncientFigurine"}, std::vector<std::shared_ptr<Box>>());

	auto cups = std::make_shared<Box>("Cups",
		std::vector<std::string> {"TraditionalCup"}, std::vector<std::shared_ptr<Box>>());

	auto staraZagoraBox = std::make_shared<Box>("StaraZagoraBox",
		std::vector<std::string> {"Postcard"}, std::vector<std::shared_ptr<Box>> {figurines, cups});

	plovdivBox->simplifyBox();
	staraZagoraBox->simplifyBox();

	std::string expectedOutput = plovdivBox->toString() + staraZagoraBox->toString();

	std::string output = executeTask3(testInputFileName, input);

	CHECK_EQ(expectedOutput, output);
}

TEST_CASE(TestCasesUtil::testCasesStrings.at(TestCasesUtil::TESTS_TASK3)(5))
{
	/*
	19
	PlovdivBox 2 Magnet Book 2 ArtBox TheatreBox
	ArtBox 0 1 Drawings
	Drawings 0 1 DrawingsNested1
	DrawingsNested1 0 1 DrawingsNested2
	DrawingsNested2 1 OldPlovdiv 0
	TheatreBox 0 1 TheatreSouvenirs
	TheatreSouvenirs 0 3 Plates Bags SouvenirsNested1
	Plates 1 DecorativePlate 0
	Bags 1 BagsSouvenir 1 BagsNested1
	BagsNested1 1 BagsSouvenirNested1 1 BagsNested2
	BagsNested2 1 BagsSouvenirNested2 1 BagsNested3
	BagsNested3 0 0
	SouvenirsNested1 0 1 SouvenirsNested2
	SouvenirsNested2 0 1 SouvenirsNested3
	SouvenirsNested3 0 1 SouvenirsNested4
	SouvenirsNested4 1 NestedSouvenirItem 0
	StaraZagoraBox 1 Postcard 2 Figurines Cups
	Figurines 1 AncientFigurine 0
	Cups 1 TraditionalCup 0
	*/
	std::string input = std::string("19\n") +
		"PlovdivBox 2 Magnet Book 2 ArtBox TheatreBox\n" +
		"ArtBox 0 1 Drawings\n" +
		"Drawings 0 1 DrawingsNested1\n" +
		"DrawingsNested1 0 1 DrawingsNested2\n" +
		"DrawingsNested2 1 OldPlovdiv 0\n" +
		"TheatreBox 0 1 TheatreSouvenirs\n" +
		"TheatreSouvenirs 0 3 Plates Bags SouvenirsNested1\n" +
		"Plates 1 DecorativePlate 0\n" +
		"Bags 1 BagsSouvenir 1 BagsNested1\n" +
		"BagsNested1 1 BagsSouvenirNested1 1 BagsNested2\n" +
		"BagsNested2 1 BagsSouvenirNested2 1 BagsNested3\n" +
		"BagsNested3 0 0\n" +
		"SouvenirsNested1 0 1 SouvenirsNested2\n" +
		"SouvenirsNested2 0 1 SouvenirsNested3\n" +
		"SouvenirsNested3 0 1 SouvenirsNested4\n" +
		"SouvenirsNested4 1 NestedSouvenirItem 0\n" +
		"StaraZagoraBox 1 Postcard 2 Figurines Cups\n" +
		"Figurines 1 AncientFigurine 0\n" +
		"Cups 1 TraditionalCup 0\n";

	std::string testInputFileName = "test_task3.txt";

	auto plates = std::make_shared<Box>("Plates",
		std::vector<std::string>{"DecorativePlate"}, std::vector<std::shared_ptr<Box>>());

	auto bagsNested3 = std::make_shared<Box>("BagsNested3",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>());

	auto souvenirsNested4 = std::make_shared<Box>("SouvenirsNested4",
		std::vector<std::string>{"NestedSouvenirItem"}, std::vector<std::shared_ptr<Box>>());

	auto bagsNested2 = std::make_shared<Box>("BagsNested2",
		std::vector<std::string>{"BagsSouvenirNested2"}, std::vector<std::shared_ptr<Box>>{bagsNested3});

	auto souvenirsNested3 = std::make_shared<Box>("SouvenirsNested3",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested4});

	auto bagsNested1 = std::make_shared<Box>("BagsNested1",
		std::vector<std::string>{"BagsSouvenirNested1"}, std::vector<std::shared_ptr<Box>>{bagsNested2});

	auto souvenirsNested2 = std::make_shared<Box>("SouvenirsNested2",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested3});

	auto bags = std::make_shared<Box>("Bags",
		std::vector<std::string>{"BagsSouvenir"}, std::vector<std::shared_ptr<Box>>{bagsNested1});

	auto souvenirsNested1 = std::make_shared<Box>("SouvenirsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested2});

	auto theatreSouvenirs = std::make_shared<Box>("TheatreSouvenirs",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> {plates, bags, souvenirsNested1});

	auto theatreBox = std::make_shared<Box>("TheatreBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{ theatreSouvenirs });

	auto drawingsNested2 = std::make_shared<Box>("DrawingsNested2",
		std::vector<std::string>{"OldPlovdiv"}, std::vector<std::shared_ptr<Box>>());

	auto drawingsNested1 = std::make_shared<Box>("DrawingsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{drawingsNested2});

	auto drawings = std::make_shared<Box>("Drawings",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{drawingsNested1});

	auto artBox = std::make_shared<Box>("ArtBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> { drawings});

	auto plovdivBox = std::make_shared<Box>("PlovdivBox",
		std::vector<std::string>{"Magnet", "Book"},
		std::vector<std::shared_ptr<Box>> {artBox, theatreBox});

	auto figurines = std::make_shared<Box>("Figurines",
		std::vector<std::string> {"AncientFigurine"}, std::vector<std::shared_ptr<Box>>());

	auto cups = std::make_shared<Box>("Cups",
		std::vector<std::string> {"TraditionalCup"}, std::vector<std::shared_ptr<Box>>());

	auto staraZagoraBox = std::make_shared<Box>("StaraZagoraBox",
		std::vector<std::string> {"Postcard"}, std::vector<std::shared_ptr<Box>> {figurines, cups});

	plovdivBox->simplifyBox();
	staraZagoraBox->simplifyBox();

	std::string expectedOutput = plovdivBox->toString() + staraZagoraBox->toString();

	std::string output = executeTask3(testInputFileName, input);

	CHECK_EQ(expectedOutput, output);
}

TEST_CASE(TestCasesUtil::testCasesStrings.at(TestCasesUtil::TESTS_TASK3)(6))
{
	/*
	19
	PlovdivBox 2 Magnet Book 2 ArtBox TheatreBox
	ArtBox 0 1 Drawings
	Drawings 0 1 DrawingsNested1
	DrawingsNested1 0 1 DrawingsNested2
	DrawingsNested2 1 OldPlovdiv 0
	TheatreBox 0 1 TheatreSouvenirs
	TheatreSouvenirs 0 3 Plates Bags SouvenirsNested1
	Plates 1 DecorativePlate 0
	Bags 0 1 BagsNested1
	BagsNested1 1 BagsSouvenirNested1 1 BagsNested2
	BagsNested2 0 1 BagsNested3
	BagsNested3 0 0
	SouvenirsNested1 0 1 SouvenirsNested2
	SouvenirsNested2 0 1 SouvenirsNested3
	SouvenirsNested3 0 1 SouvenirsNested4
	SouvenirsNested4 1 NestedSouvenirItem 0
	StaraZagoraBox 1 Postcard 2 Figurines Cups
	Figurines 1 AncientFigurine 0
	Cups 1 TraditionalCup 0
	*/
	std::string input = std::string("19\n") +
		"PlovdivBox 2 Magnet Book 2 ArtBox TheatreBox\n" +
		"ArtBox 0 1 Drawings\n" +
		"Drawings 0 1 DrawingsNested1\n" +
		"DrawingsNested1 0 1 DrawingsNested2\n" +
		"DrawingsNested2 1 OldPlovdiv 0\n" +
		"TheatreBox 0 1 TheatreSouvenirs\n" +
		"TheatreSouvenirs 0 3 Plates Bags SouvenirsNested1\n" +
		"Plates 1 DecorativePlate 0\n" +
		"Bags 0 1 BagsNested1\n" +
		"BagsNested1 1 BagsSouvenirNested1 1 BagsNested2\n" +
		"BagsNested2 0 1 BagsNested3\n" +
		"BagsNested3 0 0\n" +
		"SouvenirsNested1 0 1 SouvenirsNested2\n" +
		"SouvenirsNested2 0 1 SouvenirsNested3\n" +
		"SouvenirsNested3 0 1 SouvenirsNested4\n" +
		"SouvenirsNested4 1 NestedSouvenirItem 0\n" +
		"StaraZagoraBox 1 Postcard 2 Figurines Cups\n" +
		"Figurines 1 AncientFigurine 0\n" +
		"Cups 1 TraditionalCup 0\n";

	std::string testInputFileName = "test_task3.txt";

	auto plates = std::make_shared<Box>("Plates",
		std::vector<std::string>{"DecorativePlate"}, std::vector<std::shared_ptr<Box>>());

	auto bagsNested3 = std::make_shared<Box>("BagsNested3",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>());

	auto souvenirsNested4 = std::make_shared<Box>("SouvenirsNested4",
		std::vector<std::string>{"NestedSouvenirItem"}, std::vector<std::shared_ptr<Box>>());

	auto bagsNested2 = std::make_shared<Box>("BagsNested2",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{bagsNested3});

	auto souvenirsNested3 = std::make_shared<Box>("SouvenirsNested3",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested4});

	auto bagsNested1 = std::make_shared<Box>("BagsNested1",
		std::vector<std::string>{"BagsSouvenirNested1"}, std::vector<std::shared_ptr<Box>>{bagsNested2});

	auto souvenirsNested2 = std::make_shared<Box>("SouvenirsNested2",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested3});

	auto bags = std::make_shared<Box>("Bags",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{bagsNested1});

	auto souvenirsNested1 = std::make_shared<Box>("SouvenirsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested2});

	auto theatreSouvenirs = std::make_shared<Box>("TheatreSouvenirs",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> {plates, bags, souvenirsNested1});

	auto theatreBox = std::make_shared<Box>("TheatreBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{ theatreSouvenirs });

	auto drawingsNested2 = std::make_shared<Box>("DrawingsNested2",
		std::vector<std::string>{"OldPlovdiv"}, std::vector<std::shared_ptr<Box>>());

	auto drawingsNested1 = std::make_shared<Box>("DrawingsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{drawingsNested2});

	auto drawings = std::make_shared<Box>("Drawings",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{drawingsNested1});

	auto artBox = std::make_shared<Box>("ArtBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> { drawings});

	auto plovdivBox = std::make_shared<Box>("PlovdivBox",
		std::vector<std::string>{"Magnet", "Book"},
		std::vector<std::shared_ptr<Box>> {artBox, theatreBox});

	auto figurines = std::make_shared<Box>("Figurines",
		std::vector<std::string> {"AncientFigurine"}, std::vector<std::shared_ptr<Box>>());

	auto cups = std::make_shared<Box>("Cups",
		std::vector<std::string> {"TraditionalCup"}, std::vector<std::shared_ptr<Box>>());

	auto staraZagoraBox = std::make_shared<Box>("StaraZagoraBox",
		std::vector<std::string> {"Postcard"}, std::vector<std::shared_ptr<Box>> {figurines, cups});

	plovdivBox->simplifyBox();
	staraZagoraBox->simplifyBox();

	std::string expectedOutput = plovdivBox->toString() + staraZagoraBox->toString();

	std::string output = executeTask3(testInputFileName, input);

	CHECK_EQ(expectedOutput, output);
}

TEST_CASE(TestCasesUtil::testCasesStrings.at(TestCasesUtil::TESTS_TASK3)(7))
{
	/*
	19
	PlovdivBox 2 Magnet Book 2 ArtBox TheatreBox
	ArtBox 0 1 Drawings
	Drawings 0 1 DrawingsNested1
	DrawingsNested1 0 1 DrawingsNested2
	DrawingsNested2 1 OldPlovdiv 0
	TheatreBox 0 1 TheatreSouvenirs
	TheatreSouvenirs 0 3 Plates Bags SouvenirsNested1
	Plates 1 DecorativePlate 0
	Bags 0 1 BagsNested1
	BagsNested1 0 1 BagsNested2
	BagsNested2 1 BagsSouvenirNested2 1 BagsNested3
	BagsNested3 0 0
	SouvenirsNested1 0 1 SouvenirsNested2
	SouvenirsNested2 0 1 SouvenirsNested3
	SouvenirsNested3 0 1 SouvenirsNested4
	SouvenirsNested4 1 NestedSouvenirItem 0
	StaraZagoraBox 1 Postcard 2 Figurines Cups
	Figurines 1 AncientFigurine 0
	Cups 1 TraditionalCup 0
	*/
	std::string input = std::string("19\n") +
		"PlovdivBox 2 Magnet Book 2 ArtBox TheatreBox\n" +
		"ArtBox 0 1 Drawings\n" +
		"Drawings 0 1 DrawingsNested1\n" +
		"DrawingsNested1 0 1 DrawingsNested2\n" +
		"DrawingsNested2 1 OldPlovdiv 0\n" +
		"TheatreBox 0 1 TheatreSouvenirs\n" +
		"TheatreSouvenirs 0 3 Plates Bags SouvenirsNested1\n" +
		"Plates 1 DecorativePlate 0\n" +
		"Bags 0 1 BagsNested1\n" +
		"BagsNested1 0 1 BagsNested2\n" +
		"BagsNested2 1 BagsSouvenirNested2 1 BagsNested3\n" +
		"BagsNested3 0 0\n" +
		"SouvenirsNested1 0 1 SouvenirsNested2\n" +
		"SouvenirsNested2 0 1 SouvenirsNested3\n" +
		"SouvenirsNested3 0 1 SouvenirsNested4\n" +
		"SouvenirsNested4 1 NestedSouvenirItem 0\n" +
		"StaraZagoraBox 1 Postcard 2 Figurines Cups\n" +
		"Figurines 1 AncientFigurine 0\n" +
		"Cups 1 TraditionalCup 0\n";

	std::string testInputFileName = "test_task3.txt";

	auto plates = std::make_shared<Box>("Plates",
		std::vector<std::string>{"DecorativePlate"}, std::vector<std::shared_ptr<Box>>());

	auto bagsNested3 = std::make_shared<Box>("BagsNested3",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>());

	auto souvenirsNested4 = std::make_shared<Box>("SouvenirsNested4",
		std::vector<std::string>{"NestedSouvenirItem"}, std::vector<std::shared_ptr<Box>>());

	auto bagsNested2 = std::make_shared<Box>("BagsNested2",
		std::vector<std::string>{"BagsSouvenirNested2"}, std::vector<std::shared_ptr<Box>>{bagsNested3});

	auto souvenirsNested3 = std::make_shared<Box>("SouvenirsNested3",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested4});

	auto bagsNested1 = std::make_shared<Box>("BagsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{bagsNested2});

	auto souvenirsNested2 = std::make_shared<Box>("SouvenirsNested2",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested3});

	auto bags = std::make_shared<Box>("Bags",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{bagsNested1});

	auto souvenirsNested1 = std::make_shared<Box>("SouvenirsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested2});

	auto theatreSouvenirs = std::make_shared<Box>("TheatreSouvenirs",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> {plates, bags, souvenirsNested1});

	auto theatreBox = std::make_shared<Box>("TheatreBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{ theatreSouvenirs });

	auto drawingsNested2 = std::make_shared<Box>("DrawingsNested2",
		std::vector<std::string>{"OldPlovdiv"}, std::vector<std::shared_ptr<Box>>());

	auto drawingsNested1 = std::make_shared<Box>("DrawingsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{drawingsNested2});

	auto drawings = std::make_shared<Box>("Drawings",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{drawingsNested1});

	auto artBox = std::make_shared<Box>("ArtBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> { drawings});

	auto plovdivBox = std::make_shared<Box>("PlovdivBox",
		std::vector<std::string>{"Magnet", "Book"},
		std::vector<std::shared_ptr<Box>> {artBox, theatreBox});

	auto figurines = std::make_shared<Box>("Figurines",
		std::vector<std::string> {"AncientFigurine"}, std::vector<std::shared_ptr<Box>>());

	auto cups = std::make_shared<Box>("Cups",
		std::vector<std::string> {"TraditionalCup"}, std::vector<std::shared_ptr<Box>>());

	auto staraZagoraBox = std::make_shared<Box>("StaraZagoraBox",
		std::vector<std::string> {"Postcard"}, std::vector<std::shared_ptr<Box>> {figurines, cups});

	plovdivBox->simplifyBox();
	staraZagoraBox->simplifyBox();

	std::string expectedOutput = plovdivBox->toString() + staraZagoraBox->toString();

	std::string output = executeTask3(testInputFileName, input);

	CHECK_EQ(expectedOutput, output);
}

TEST_CASE(TestCasesUtil::testCasesStrings.at(TestCasesUtil::TESTS_TASK3)(8))
{
	/*
	19
	PlovdivBox 2 Magnet Book 2 ArtBox TheatreBox
	ArtBox 0 1 Drawings
	Drawings 0 1 DrawingsNested1
	DrawingsNested1 0 1 DrawingsNested2
	DrawingsNested2 1 OldPlovdiv 0
	TheatreBox 0 1 TheatreSouvenirs
	TheatreSouvenirs 0 3 Plates Bags SouvenirsNested1
	Plates 1 DecorativePlate 0
	Bags 0 1 BagsNested1
	BagsNested1 1 BagsSouvenirNested1 1 BagsNested2
	BagsNested2 1 BagsSouvenirNested2 1 BagsNested3
	BagsNested3 0 0
	SouvenirsNested1 0 1 SouvenirsNested2
	SouvenirsNested2 0 1 SouvenirsNested3
	SouvenirsNested3 0 1 SouvenirsNested4
	SouvenirsNested4 1 NestedSouvenirItem 0
	StaraZagoraBox 1 Postcard 2 Figurines Cups
	Figurines 1 AncientFigurine 0
	Cups 1 TraditionalCup 0
	*/
	std::string input = std::string("19\n") +
		"PlovdivBox 2 Magnet Book 2 ArtBox TheatreBox\n" +
		"ArtBox 0 1 Drawings\n" +
		"Drawings 0 1 DrawingsNested1\n" +
		"DrawingsNested1 0 1 DrawingsNested2\n" +
		"DrawingsNested2 1 OldPlovdiv 0\n" +
		"TheatreBox 0 1 TheatreSouvenirs\n" +
		"TheatreSouvenirs 0 3 Plates Bags SouvenirsNested1\n" +
		"Plates 1 DecorativePlate 0\n" +
		"Bags 0 1 BagsNested1\n" +
		"BagsNested1 1 BagsSouvenirNested1 1 BagsNested2\n" +
		"BagsNested2 1 BagsSouvenirNested2 1 BagsNested3\n" +
		"BagsNested3 0 0\n" +
		"SouvenirsNested1 0 1 SouvenirsNested2\n" +
		"SouvenirsNested2 0 1 SouvenirsNested3\n" +
		"SouvenirsNested3 0 1 SouvenirsNested4\n" +
		"SouvenirsNested4 1 NestedSouvenirItem 0\n" +
		"StaraZagoraBox 1 Postcard 2 Figurines Cups\n" +
		"Figurines 1 AncientFigurine 0\n" +
		"Cups 1 TraditionalCup 0\n";

	std::string testInputFileName = "test_task3.txt";

	auto plates = std::make_shared<Box>("Plates",
		std::vector<std::string>{"DecorativePlate"}, std::vector<std::shared_ptr<Box>>());

	auto bagsNested3 = std::make_shared<Box>("BagsNested3",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>());

	auto souvenirsNested4 = std::make_shared<Box>("SouvenirsNested4",
		std::vector<std::string>{"NestedSouvenirItem"}, std::vector<std::shared_ptr<Box>>());

	auto bagsNested2 = std::make_shared<Box>("BagsNested2",
		std::vector<std::string>{"BagsSouvenirNested2"}, std::vector<std::shared_ptr<Box>>{bagsNested3});

	auto souvenirsNested3 = std::make_shared<Box>("SouvenirsNested3",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested4});

	auto bagsNested1 = std::make_shared<Box>("BagsNested1",
		std::vector<std::string>{"BagsSouvenirNested1"}, std::vector<std::shared_ptr<Box>>{bagsNested2});

	auto souvenirsNested2 = std::make_shared<Box>("SouvenirsNested2",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested3});

	auto bags = std::make_shared<Box>("Bags",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{bagsNested1});

	auto souvenirsNested1 = std::make_shared<Box>("SouvenirsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested2});

	auto theatreSouvenirs = std::make_shared<Box>("TheatreSouvenirs",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> {plates, bags, souvenirsNested1});

	auto theatreBox = std::make_shared<Box>("TheatreBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{ theatreSouvenirs });

	auto drawingsNested2 = std::make_shared<Box>("DrawingsNested2",
		std::vector<std::string>{"OldPlovdiv"}, std::vector<std::shared_ptr<Box>>());

	auto drawingsNested1 = std::make_shared<Box>("DrawingsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{drawingsNested2});

	auto drawings = std::make_shared<Box>("Drawings",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{drawingsNested1});

	auto artBox = std::make_shared<Box>("ArtBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> { drawings});

	auto plovdivBox = std::make_shared<Box>("PlovdivBox",
		std::vector<std::string>{"Magnet", "Book"},
		std::vector<std::shared_ptr<Box>> {artBox, theatreBox});

	auto figurines = std::make_shared<Box>("Figurines",
		std::vector<std::string> {"AncientFigurine"}, std::vector<std::shared_ptr<Box>>());

	auto cups = std::make_shared<Box>("Cups",
		std::vector<std::string> {"TraditionalCup"}, std::vector<std::shared_ptr<Box>>());

	auto staraZagoraBox = std::make_shared<Box>("StaraZagoraBox",
		std::vector<std::string> {"Postcard"}, std::vector<std::shared_ptr<Box>> {figurines, cups});

	plovdivBox->simplifyBox();
	staraZagoraBox->simplifyBox();

	std::string expectedOutput = plovdivBox->toString() + staraZagoraBox->toString();

	std::string output = executeTask3(testInputFileName, input);

	CHECK_EQ(expectedOutput, output);
}

TEST_CASE(TestCasesUtil::testCasesStrings.at(TestCasesUtil::TESTS_TASK3)(9))
{
	/*
	19
	PlovdivBox 2 Magnet Book 2 ArtBox TheatreBox
	ArtBox 0 1 Drawings
	Drawings 0 1 DrawingsNested1
	DrawingsNested1 0 1 DrawingsNested2
	DrawingsNested2 1 OldPlovdiv 0
	TheatreBox 0 1 TheatreSouvenirs
	TheatreSouvenirs 0 3 Plates Bags SouvenirsNested1
	Plates 1 DecorativePlate 0
	Bags 0 1 BagsNested1
	BagsNested1 0 1 BagsNested2
	BagsNested2 0 1 BagsNested3
	BagsNested3 0 0
	SouvenirsNested1 0 1 SouvenirsNested2
	SouvenirsNested2 0 1 SouvenirsNested3
	SouvenirsNested3 0 1 SouvenirsNested4
	SouvenirsNested4 1 NestedSouvenirItem 0
	StaraZagoraBox 1 Postcard 2 Figurines Cups
	Figurines 1 AncientFigurine 0
	Cups 1 TraditionalCup 0
	*/
	std::string input = std::string("19\n") +
		"PlovdivBox 2 Magnet Book 2 ArtBox TheatreBox\n" +
		"ArtBox 0 1 Drawings\n" +
		"Drawings 0 1 DrawingsNested1\n" +
		"DrawingsNested1 0 1 DrawingsNested2\n" +
		"DrawingsNested2 1 OldPlovdiv 0\n" +
		"TheatreBox 0 1 TheatreSouvenirs\n" +
		"TheatreSouvenirs 0 3 Plates Bags SouvenirsNested1\n" +
		"Plates 1 DecorativePlate 0\n" +
		"Bags 0 BagsNested1\n" +
		"BagsNested1 0 1 BagsNested2\n" +
		"BagsNested2 0 1 BagsNested3\n" +
		"BagsNested3 0 0\n" +
		"SouvenirsNested1 0 1 SouvenirsNested2\n" +
		"SouvenirsNested2 0 1 SouvenirsNested3\n" +
		"SouvenirsNested3 0 1 SouvenirsNested4\n" +
		"SouvenirsNested4 1 NestedSouvenirItem 0\n" +
		"StaraZagoraBox 1 Postcard 2 Figurines Cups\n" +
		"Figurines 1 AncientFigurine 0\n" +
		"Cups 1 TraditionalCup 0\n";

	std::string testInputFileName = "test_task3.txt";

	auto plates = std::make_shared<Box>("Plates",
		std::vector<std::string>{"DecorativePlate"}, std::vector<std::shared_ptr<Box>>());

	auto bagsNested3 = std::make_shared<Box>("BagsNested3",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>());

	auto souvenirsNested4 = std::make_shared<Box>("SouvenirsNested4",
		std::vector<std::string>{"NestedSouvenirItem"}, std::vector<std::shared_ptr<Box>>());

	auto bagsNested2 = std::make_shared<Box>("BagsNested2",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{bagsNested3});

	auto souvenirsNested3 = std::make_shared<Box>("SouvenirsNested3",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested4});

	auto bagsNested1 = std::make_shared<Box>("BagsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{bagsNested2});

	auto souvenirsNested2 = std::make_shared<Box>("SouvenirsNested2",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested3});

	auto bags = std::make_shared<Box>("Bags",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{bagsNested1});

	auto souvenirsNested1 = std::make_shared<Box>("SouvenirsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested2});

	auto theatreSouvenirs = std::make_shared<Box>("TheatreSouvenirs",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> {plates, bags, souvenirsNested1});

	auto theatreBox = std::make_shared<Box>("TheatreBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{ theatreSouvenirs });

	auto drawingsNested2 = std::make_shared<Box>("DrawingsNested2",
		std::vector<std::string>{"OldPlovdiv"}, std::vector<std::shared_ptr<Box>>());

	auto drawingsNested1 = std::make_shared<Box>("DrawingsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{drawingsNested2});

	auto drawings = std::make_shared<Box>("Drawings",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{drawingsNested1});

	auto artBox = std::make_shared<Box>("ArtBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> { drawings});

	auto plovdivBox = std::make_shared<Box>("PlovdivBox",
		std::vector<std::string>{"Magnet", "Book"},
		std::vector<std::shared_ptr<Box>> {artBox, theatreBox});

	auto figurines = std::make_shared<Box>("Figurines",
		std::vector<std::string> {"AncientFigurine"}, std::vector<std::shared_ptr<Box>>());

	auto cups = std::make_shared<Box>("Cups",
		std::vector<std::string> {"TraditionalCup"}, std::vector<std::shared_ptr<Box>>());

	auto staraZagoraBox = std::make_shared<Box>("StaraZagoraBox",
		std::vector<std::string> {"Postcard"}, std::vector<std::shared_ptr<Box>> {figurines, cups});

	plovdivBox->simplifyBox();
	staraZagoraBox->simplifyBox();

	std::string expectedOutput = plovdivBox->toString() + staraZagoraBox->toString();

	std::string output = executeTask3(testInputFileName, input);

	CHECK_EQ(expectedOutput, output);
}

TEST_CASE(TestCasesUtil::testCasesStrings.at(TestCasesUtil::TESTS_TASK3)(10))
{
	/*
	19
	PlovdivBox 2 Magnet Book 2 ArtBox TheatreBox
	ArtBox 0 1 Drawings
	Drawings 0 1 DrawingsNested1
	DrawingsNested1 0 1 DrawingsNested2
	DrawingsNested2 1 OldPlovdiv 0
	TheatreBox 0 1 TheatreSouvenirs
	TheatreSouvenirs 0 3 Plates Bags SouvenirsNested1
	Plates 0 0
	Bags 0 1 BagsNested1
	BagsNested1 0 1 BagsNested2
	BagsNested2 0 1 BagsNested3
	BagsNested3 0 0
	SouvenirsNested1 0 1 SouvenirsNested2
	SouvenirsNested2 0 1 SouvenirsNested3
	SouvenirsNested3 0 1 SouvenirsNested4
	SouvenirsNested4 0 0
	StaraZagoraBox 1 Postcard 2 Figurines Cups
	Figurines 1 AncientFigurine 0
	Cups 1 TraditionalCup 0
	*/
	std::string input = std::string("19\n") +
		"PlovdivBox 2 Magnet Book 2 ArtBox TheatreBox\n" +
		"ArtBox 0 1 Drawings\n" +
		"Drawings 0 1 DrawingsNested1\n" +
		"DrawingsNested1 0 1 DrawingsNested2\n" +
		"DrawingsNested2 1 OldPlovdiv 0\n" +
		"TheatreBox 0 1 TheatreSouvenirs\n" +
		"TheatreSouvenirs 0 3 Plates Bags SouvenirsNested1\n" +
		"Plates 0 0\n" +
		"Bags 0 1 BagsNested1\n" +
		"BagsNested1 0 1 BagsNested2\n" +
		"BagsNested2 0 1 BagsNested3\n" +
		"BagsNested3 0 0\n" +
		"SouvenirsNested1 0 1 SouvenirsNested2\n" +
		"SouvenirsNested2 0 1 SouvenirsNested3\n" +
		"SouvenirsNested3 0 1 SouvenirsNested4\n" +
		"SouvenirsNested4 0 0\n" +
		"StaraZagoraBox 1 Postcard 2 Figurines Cups\n" +
		"Figurines 1 AncientFigurine 0\n" +
		"Cups 1 TraditionalCup 0\n";

	std::string testInputFileName = "test_task3.txt";

	auto plates = std::make_shared<Box>("Plates",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>());

	auto bagsNested3 = std::make_shared<Box>("BagsNested3",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>());

	auto souvenirsNested4 = std::make_shared<Box>("SouvenirsNested4",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>());

	auto bagsNested2 = std::make_shared<Box>("BagsNested2",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{bagsNested3});

	auto souvenirsNested3 = std::make_shared<Box>("SouvenirsNested3",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested4});

	auto bagsNested1 = std::make_shared<Box>("BagsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{bagsNested2});

	auto souvenirsNested2 = std::make_shared<Box>("SouvenirsNested2",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested3});

	auto bags = std::make_shared<Box>("Bags",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{bagsNested1});

	auto souvenirsNested1 = std::make_shared<Box>("SouvenirsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested2});

	auto theatreSouvenirs = std::make_shared<Box>("TheatreSouvenirs",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> {plates, bags, souvenirsNested1});

	auto theatreBox = std::make_shared<Box>("TheatreBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{ theatreSouvenirs });

	auto drawingsNested2 = std::make_shared<Box>("DrawingsNested2",
		std::vector<std::string>{"OldPlovdiv"}, std::vector<std::shared_ptr<Box>>());

	auto drawingsNested1 = std::make_shared<Box>("DrawingsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{drawingsNested2});

	auto drawings = std::make_shared<Box>("Drawings",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{drawingsNested1});

	auto artBox = std::make_shared<Box>("ArtBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> { drawings});

	auto plovdivBox = std::make_shared<Box>("PlovdivBox",
		std::vector<std::string>{"Magnet", "Book"},
		std::vector<std::shared_ptr<Box>> {artBox, theatreBox});

	auto figurines = std::make_shared<Box>("Figurines",
		std::vector<std::string> {"AncientFigurine"}, std::vector<std::shared_ptr<Box>>());

	auto cups = std::make_shared<Box>("Cups",
		std::vector<std::string> {"TraditionalCup"}, std::vector<std::shared_ptr<Box>>());

	auto staraZagoraBox = std::make_shared<Box>("StaraZagoraBox",
		std::vector<std::string> {"Postcard"}, std::vector<std::shared_ptr<Box>> {figurines, cups});

	plovdivBox->simplifyBox();
	staraZagoraBox->simplifyBox();

	std::string expectedOutput = plovdivBox->toString() + staraZagoraBox->toString();

	std::string output = executeTask3(testInputFileName, input);

	CHECK_EQ(expectedOutput, output);
}

TEST_CASE(TestCasesUtil::testCasesStrings.at(TestCasesUtil::TESTS_TASK3)(11))
{
	/*
	19
	PlovdivBox 1 OnlyPlovdivSouvenir 2 ArtBox TheatreBox
	ArtBox 0 1 Drawings
	Drawings 0 1 DrawingsNested1
	DrawingsNested1 0 1 DrawingsNested2
	DrawingsNested2 0 0
	TheatreBox 0 1 TheatreSouvenirs
	TheatreSouvenirs 0 3 Plates Bags SouvenirsNested1
	Plates 0 0
	Bags 0 1 BagsNested1
	BagsNested1 0 1 BagsNested2
	BagsNested2 0 1 BagsNested3
	BagsNested3 0 0
	SouvenirsNested1 0 1 SouvenirsNested2
	SouvenirsNested2 0 1 SouvenirsNested3
	SouvenirsNested3 0 1 SouvenirsNested4
	SouvenirsNested4 0 0
	StaraZagoraBox 1 Postcard 2 Figurines Cups
	Figurines 1 AncientFigurine 0
	Cups 1 TraditionalCup 0
	*/
	std::string input = std::string("19\n") +
		"PlovdivBox 1 OnlyPlovdivSouvenir 2 ArtBox TheatreBox\n" +
		"ArtBox 0 1 Drawings\n" +
		"Drawings 0 1 DrawingsNested1\n" +
		"DrawingsNested1 0 1 DrawingsNested2\n" +
		"DrawingsNested2 0 0\n" +
		"TheatreBox 0 1 TheatreSouvenirs\n" +
		"TheatreSouvenirs 0 3 Plates Bags SouvenirsNested1\n" +
		"Plates 0 0\n" +
		"Bags 0 1 BagsNested1\n" +
		"BagsNested1 0 1 BagsNested2\n" +
		"BagsNested2 0 1 BagsNested3\n" +
		"BagsNested3 0 0\n" +
		"SouvenirsNested1 0 1 SouvenirsNested2\n" +
		"SouvenirsNested2 0 1 SouvenirsNested3\n" +
		"SouvenirsNested3 0 1 SouvenirsNested4\n" +
		"SouvenirsNested4 0 0\n" +
		"StaraZagoraBox 1 Postcard 2 Figurines Cups\n" +
		"Figurines 1 AncientFigurine 0\n" +
		"Cups 1 TraditionalCup 0\n";

	std::string testInputFileName = "test_task3.txt";

	auto plates = std::make_shared<Box>("Plates",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>());

	auto bagsNested3 = std::make_shared<Box>("BagsNested3",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>());

	auto souvenirsNested4 = std::make_shared<Box>("SouvenirsNested4",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>());

	auto bagsNested2 = std::make_shared<Box>("BagsNested2",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{bagsNested3});

	auto souvenirsNested3 = std::make_shared<Box>("SouvenirsNested3",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested4});

	auto bagsNested1 = std::make_shared<Box>("BagsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{bagsNested2});

	auto souvenirsNested2 = std::make_shared<Box>("SouvenirsNested2",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested3});

	auto bags = std::make_shared<Box>("Bags",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{bagsNested1});

	auto souvenirsNested1 = std::make_shared<Box>("SouvenirsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested2});

	auto theatreSouvenirs = std::make_shared<Box>("TheatreSouvenirs",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> {plates, bags, souvenirsNested1});

	auto theatreBox = std::make_shared<Box>("TheatreBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{ theatreSouvenirs });

	auto drawingsNested2 = std::make_shared<Box>("DrawingsNested2",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>());

	auto drawingsNested1 = std::make_shared<Box>("DrawingsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{drawingsNested2});

	auto drawings = std::make_shared<Box>("Drawings",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{drawingsNested1});

	auto artBox = std::make_shared<Box>("ArtBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> { drawings});

	auto plovdivBox = std::make_shared<Box>("PlovdivBox",
		std::vector<std::string>{"OnlyPlovdivSouvenir"},
		std::vector<std::shared_ptr<Box>> {artBox, theatreBox});

	auto figurines = std::make_shared<Box>("Figurines",
		std::vector<std::string> {"AncientFigurine"}, std::vector<std::shared_ptr<Box>>());

	auto cups = std::make_shared<Box>("Cups",
		std::vector<std::string> {"TraditionalCup"}, std::vector<std::shared_ptr<Box>>());

	auto staraZagoraBox = std::make_shared<Box>("StaraZagoraBox",
		std::vector<std::string> {"Postcard"}, std::vector<std::shared_ptr<Box>> {figurines, cups});

	plovdivBox->simplifyBox();
	staraZagoraBox->simplifyBox();

	std::string expectedOutput = plovdivBox->toString() + staraZagoraBox->toString();

	std::string output = executeTask3(testInputFileName, input);

	CHECK_EQ(expectedOutput, output);
}

TEST_CASE(TestCasesUtil::testCasesStrings.at(TestCasesUtil::TESTS_TASK3)(12))
{
	/*
	19
	PlovdivBox 0 2 ArtBox TheatreBox
	ArtBox 0 1 Drawings
	Drawings 0 1 DrawingsNested1
	DrawingsNested1 0 1 DrawingsNested2
	DrawingsNested2 0 0
	TheatreBox 0 1 TheatreSouvenirs
	TheatreSouvenirs 0 3 Plates Bags SouvenirsNested1
	Plates 0 0
	Bags 0 1 BagsNested1
	BagsNested1 0 1 BagsNested2
	BagsNested2 0 1 BagsNested3
	BagsNested3 0 0
	SouvenirsNested1 0 1 SouvenirsNested2
	SouvenirsNested2 0 1 SouvenirsNested3
	SouvenirsNested3 0 1 SouvenirsNested4
	SouvenirsNested4 0 0
	StaraZagoraBox 1 Postcard 2 Figurines Cups
	Figurines 1 AncientFigurine 0
	Cups 1 TraditionalCup 0
	*/

	std::string input = std::string("19\n") +
		"PlovdivBox 0 2 ArtBox TheatreBox\n" +
		"ArtBox 0 1 Drawings\n" +
		"Drawings 0 1 DrawingsNested1\n" +
		"DrawingsNested1 0 1 DrawingsNested2\n" +
		"DrawingsNested2 0 0\n" +
		"TheatreBox 0 1 TheatreSouvenirs\n" +
		"TheatreSouvenirs 0 3 Plates Bags SouvenirsNested1\n" +
		"Plates 0 0\n" +
		"Bags 0 1 BagsNested1\n" +
		"BagsNested1 0 1 BagsNested2\n" +
		"BagsNested2 0 1 BagsNested3\n" +
		"BagsNested3 0 0\n" +
		"SouvenirsNested1 0 1 SouvenirsNested2\n" +
		"SouvenirsNested2 0 1 SouvenirsNested3\n" +
		"SouvenirsNested3 0 1 SouvenirsNested4\n" +
		"SouvenirsNested4 0 0\n" +
		"StaraZagoraBox 1 Postcard 2 Figurines Cups\n" +
		"Figurines 1 AncientFigurine 0\n" +
		"Cups 1 TraditionalCup 0\n";

	std::string testInputFileName = "test_task3.txt";

	auto plates = std::make_shared<Box>("Plates",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>());

	auto bagsNested3 = std::make_shared<Box>("BagsNested3",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>());

	auto souvenirsNested4 = std::make_shared<Box>("SouvenirsNested4",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>());

	auto bagsNested2 = std::make_shared<Box>("BagsNested2",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{bagsNested3});

	auto souvenirsNested3 = std::make_shared<Box>("SouvenirsNested3",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested4});

	auto bagsNested1 = std::make_shared<Box>("BagsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{bagsNested2});

	auto souvenirsNested2 = std::make_shared<Box>("SouvenirsNested2",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested3});

	auto bags = std::make_shared<Box>("Bags",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{bagsNested1});

	auto souvenirsNested1 = std::make_shared<Box>("SouvenirsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested2});

	auto theatreSouvenirs = std::make_shared<Box>("TheatreSouvenirs",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> {plates, bags, souvenirsNested1});

	auto theatreBox = std::make_shared<Box>("TheatreBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{ theatreSouvenirs });

	auto drawingsNested2 = std::make_shared<Box>("DrawingsNested2",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>());

	auto drawingsNested1 = std::make_shared<Box>("DrawingsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{drawingsNested2});

	auto drawings = std::make_shared<Box>("Drawings",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{drawingsNested1});

	auto artBox = std::make_shared<Box>("ArtBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> { drawings});

	auto plovdivBox = std::make_shared<Box>("PlovdivBox",
		std::vector<std::string>(),
		std::vector<std::shared_ptr<Box>> {artBox, theatreBox});

	auto figurines = std::make_shared<Box>("Figurines",
		std::vector<std::string> {"AncientFigurine"}, std::vector<std::shared_ptr<Box>>());

	auto cups = std::make_shared<Box>("Cups",
		std::vector<std::string> {"TraditionalCup"}, std::vector<std::shared_ptr<Box>>());

	auto staraZagoraBox = std::make_shared<Box>("StaraZagoraBox",
		std::vector<std::string> {"Postcard"}, std::vector<std::shared_ptr<Box>> {figurines, cups});

	staraZagoraBox->simplifyBox();

	std::string expectedOutput = staraZagoraBox->toString();

	std::string output = executeTask3(testInputFileName, input);

	CHECK_EQ(expectedOutput, output);
}

TEST_CASE("Test task 3 no box contains any souvenirs")
{
	/*
	19
	PlovdivBox 0 2 ArtBox TheatreBox
	ArtBox 0 1 Drawings
	Drawings 0 1 DrawingsNested1
	DrawingsNested1 0 1 DrawingsNested2
	DrawingsNested2 0 0
	TheatreBox 0 1 TheatreSouvenirs
	TheatreSouvenirs 0 3 Plates Bags SouvenirsNested1
	Plates 0 0
	Bags 0 1 BagsNested1
	BagsNested1 0 1 BagsNested2
	BagsNested2 0 1 BagsNested3
	BagsNested3 0 0
	SouvenirsNested1 0 1 SouvenirsNested2
	SouvenirsNested2 0 1 SouvenirsNested3
	SouvenirsNested3 0 1 SouvenirsNested4
	SouvenirsNested4 0 0
	StaraZagoraBox 0 2 Figurines Cups
	Figurines 0 0
	Cups 0 0
	*/

	std::string input = std::string("19\n") +
		"PlovdivBox 0 2 ArtBox TheatreBox\n" +
		"ArtBox 0 1 Drawings\n" +
		"Drawings 0 1 DrawingsNested1\n" +
		"DrawingsNested1 0 1 DrawingsNested2\n" +
		"DrawingsNested2 0 0\n" +
		"TheatreBox 0 1 TheatreSouvenirs\n" +
		"TheatreSouvenirs 0 3 Plates Bags SouvenirsNested1\n" +
		"Plates 0 0\n" +
		"Bags 0 1 BagsNested1\n" +
		"BagsNested1 0 1 BagsNested2\n" +
		"BagsNested2 0 1 BagsNested3\n" +
		"BagsNested3 0 0\n" +
		"SouvenirsNested1 0 1 SouvenirsNested2\n" +
		"SouvenirsNested2 0 1 SouvenirsNested3\n" +
		"SouvenirsNested3 0 1 SouvenirsNested4\n" +
		"SouvenirsNested4 0 0\n" +
		"StaraZagoraBox 0 2 Figurines Cups\n" +
		"Figurines 0 0\n" +
		"Cups 0 0\n";

	std::string testInputFileName = "test_task3.txt";

	auto plates = std::make_shared<Box>("Plates",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>());

	auto bagsNested3 = std::make_shared<Box>("BagsNested3",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>());

	auto souvenirsNested4 = std::make_shared<Box>("SouvenirsNested4",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>());

	auto bagsNested2 = std::make_shared<Box>("BagsNested2",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{bagsNested3});

	auto souvenirsNested3 = std::make_shared<Box>("SouvenirsNested3",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested4});

	auto bagsNested1 = std::make_shared<Box>("BagsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{bagsNested2});

	auto souvenirsNested2 = std::make_shared<Box>("SouvenirsNested2",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested3});

	auto bags = std::make_shared<Box>("Bags",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{bagsNested1});

	auto souvenirsNested1 = std::make_shared<Box>("SouvenirsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{souvenirsNested2});

	auto theatreSouvenirs = std::make_shared<Box>("TheatreSouvenirs",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> {plates, bags, souvenirsNested1});

	auto theatreBox = std::make_shared<Box>("TheatreBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{ theatreSouvenirs });

	auto drawingsNested2 = std::make_shared<Box>("DrawingsNested2",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>());

	auto drawingsNested1 = std::make_shared<Box>("DrawingsNested1",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{drawingsNested2});

	auto drawings = std::make_shared<Box>("Drawings",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{drawingsNested1});

	auto artBox = std::make_shared<Box>("ArtBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> { drawings});

	auto plovdivBox = std::make_shared<Box>("PlovdivBox",
		std::vector<std::string>(),
		std::vector<std::shared_ptr<Box>> {artBox, theatreBox});

	auto figurines = std::make_shared<Box>("Figurines",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>());

	auto cups = std::make_shared<Box>("Cups",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>());

	auto staraZagoraBox = std::make_shared<Box>("StaraZagoraBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> {figurines, cups});

	std::string expectedOutput = "";

	std::string output = executeTask3(testInputFileName, input);

	CHECK_EQ(expectedOutput, output);
}