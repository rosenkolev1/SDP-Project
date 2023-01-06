#include "doctest.h"
#include <iostream>
#include <vector>
#include "../SDP_Project_Source/Box.h"
#include "TestCasesUtil.h"

TEST_CASE("Test the copy constructor and assignment operator for box class!")
{
	auto plates = std::make_shared<Box>("Plates",
		std::vector<std::string> {"DecorativePlate"}, std::vector<std::shared_ptr<Box>>());

	auto bags = std::make_shared<Box>("Bags",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>());

	auto drawings = std::make_shared<Box>("Drawings",
		std::vector<std::string> {"OldPlovdiv"}, std::vector<std::shared_ptr<Box>>());

	auto theatreSouvenirs = std::make_shared<Box>("TheatreSouvenirs",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> {plates, bags});

	auto theatreBox = std::make_shared<Box>("TheatreBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{ theatreSouvenirs });

	auto artBox = std::make_shared<Box>("ArtBox",
		std::vector<std::string>(), std::vector<std::shared_ptr<Box>> { drawings});

	auto plovdivBox = std::make_shared<Box>("PlovdivBox",
		std::vector<std::string> {"Magnet", "Book"},
		std::vector<std::shared_ptr<Box>> {artBox, theatreBox});

	auto plovdivBoxCopy = std::make_shared<Box>(*plovdivBox);

	auto plovdivBoxCopy_Extra = std::make_shared<Box>("PlovdivBox_Extra",
		std::vector<std::string> {"Bell"},
		std::vector<std::shared_ptr<Box>>());

	plovdivBoxCopy->addBox(plovdivBoxCopy_Extra);

	CHECK_NE(plovdivBoxCopy->toString(), plovdivBox->toString());

	auto plovdivBoxCopy2 = *plovdivBox;

	auto plovdivBoxCopy_Extra2 = std::make_shared<Box>("PlovdivBox_Extra2",
		std::vector<std::string> {"Bell2"},
		std::vector<std::shared_ptr<Box>>());

	plovdivBoxCopy2.addBox(plovdivBoxCopy_Extra2);

	CHECK_NE(plovdivBoxCopy2.toString(), plovdivBox->toString());

	*plovdivBoxCopy = plovdivBoxCopy2;

	CHECK_EQ(plovdivBoxCopy2.toString(), plovdivBoxCopy->toString());

	plovdivBoxCopy2.addBox(plovdivBoxCopy_Extra);

	CHECK_NE(plovdivBoxCopy2.toString(), plovdivBoxCopy->toString());
}

TEST_CASE("Test the toString method for the box class!")
{
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

	/*plovdivBox->simplifyBox();*/

	std::string nestedIndent = "	";
	std::string expectedOutput = std::string("--------------------------------------------------------\n") +
		"The box is:\n" +
		"Name: PlovdivBox\n" +
		"Souvenirs: Magnet, Book\n" +
		"Boxes:\n" +
		nestedIndent + "--------------------------------------------------------\n" +
		nestedIndent + "The box is:\n" +
		nestedIndent + "Name: ArtBox\n" +
		nestedIndent + "Souvenirs: \n" +
		nestedIndent + "Boxes:\n" +
		nestedIndent + nestedIndent + "--------------------------------------------------------\n" +
		nestedIndent + nestedIndent + "The box is:\n" +
		nestedIndent + nestedIndent + "Name: Drawings\n" +
		nestedIndent + nestedIndent + "Souvenirs: \n" +
		nestedIndent + nestedIndent + "Boxes:\n" +
		nestedIndent + nestedIndent + nestedIndent + "--------------------------------------------------------\n" +
		nestedIndent + nestedIndent + nestedIndent + "The box is:\n" +
		nestedIndent + nestedIndent + nestedIndent + "Name: DrawingsNested1\n" +
		nestedIndent + nestedIndent + nestedIndent + "Souvenirs: \n" +
		nestedIndent + nestedIndent + nestedIndent + "Boxes:\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + "--------------------------------------------------------\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + "The box is:\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + "Name: DrawingsNested2\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + "Souvenirs: OldPlovdiv\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + "Boxes:\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + "--------------------------------------------------------\n" +
		"\n" + 
		nestedIndent + nestedIndent + nestedIndent + "--------------------------------------------------------\n" +
		"\n" +
		nestedIndent + nestedIndent + "--------------------------------------------------------\n" +
		"\n" +
		nestedIndent + "--------------------------------------------------------\n" +
		"\n" +
		nestedIndent + "--------------------------------------------------------\n" +
		nestedIndent + "The box is:\n" +
		nestedIndent + "Name: TheatreBox\n" +
		nestedIndent + "Souvenirs: \n" +
		nestedIndent + "Boxes:\n" +
		nestedIndent + nestedIndent + "--------------------------------------------------------\n" +
		nestedIndent + nestedIndent + "The box is:\n" +
		nestedIndent + nestedIndent + "Name: TheatreSouvenirs\n" +
		nestedIndent + nestedIndent + "Souvenirs: \n" +
		nestedIndent + nestedIndent + "Boxes:\n" +
		nestedIndent + nestedIndent + nestedIndent + "--------------------------------------------------------\n" +
		nestedIndent + nestedIndent + nestedIndent + "The box is:\n" +
		nestedIndent + nestedIndent + nestedIndent + "Name: Plates\n" +
		nestedIndent + nestedIndent + nestedIndent + "Souvenirs: DecorativePlate\n" +
		nestedIndent + nestedIndent + nestedIndent + "Boxes:\n" +
		nestedIndent + nestedIndent + nestedIndent + "--------------------------------------------------------\n" +
		"\n" +
		nestedIndent + nestedIndent + nestedIndent + "--------------------------------------------------------\n" +
		nestedIndent + nestedIndent + nestedIndent + "The box is:\n" +
		nestedIndent + nestedIndent + nestedIndent + "Name: Bags\n" +
		nestedIndent + nestedIndent + nestedIndent + "Souvenirs: BagsSouvenir\n" +
		nestedIndent + nestedIndent + nestedIndent + "Boxes:\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + "--------------------------------------------------------\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + "The box is:\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + "Name: BagsNested1\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + "Souvenirs: BagsSouvenirNested1\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + "Boxes:\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + "--------------------------------------------------------\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + "The box is:\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + "Name: BagsNested2\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + "Souvenirs: BagsSouvenirNested2\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + "Boxes:\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + "--------------------------------------------------------\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + "The box is:\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + "Name: BagsNested3\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + "Souvenirs: \n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + "Boxes:\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + "--------------------------------------------------------\n" +
		"\n" + 
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + "--------------------------------------------------------\n" +
		"\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + "--------------------------------------------------------\n" +
		"\n" +
		nestedIndent + nestedIndent + nestedIndent + "--------------------------------------------------------\n" +
		"\n" +
		nestedIndent + nestedIndent + nestedIndent + "--------------------------------------------------------\n" +
		nestedIndent + nestedIndent + nestedIndent + "The box is:\n" +
		nestedIndent + nestedIndent + nestedIndent + "Name: SouvenirsNested1\n" +
		nestedIndent + nestedIndent + nestedIndent + "Souvenirs: \n" +
		nestedIndent + nestedIndent + nestedIndent + "Boxes:\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + "--------------------------------------------------------\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + "The box is:\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + "Name: SouvenirsNested2\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + "Souvenirs: \n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + "Boxes:\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + "--------------------------------------------------------\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + "The box is:\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + "Name: SouvenirsNested3\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + "Souvenirs: \n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + "Boxes:\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + "--------------------------------------------------------\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + "The box is:\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + "Name: SouvenirsNested4\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + "Souvenirs: NestedSouvenirItem\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + "Boxes:\n" +
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + "--------------------------------------------------------\n" +
		"\n" + 
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + nestedIndent + "--------------------------------------------------------\n" +
		"\n" + 
		nestedIndent + nestedIndent + nestedIndent + nestedIndent + "--------------------------------------------------------\n" +
		"\n" + 
		nestedIndent + nestedIndent + nestedIndent + "--------------------------------------------------------\n" +
		"\n" +
		nestedIndent + nestedIndent + "--------------------------------------------------------\n" +
		"\n" +
		nestedIndent + "--------------------------------------------------------\n" +
		"\n" + 
		"--------------------------------------------------------\n";

	std::string output = plovdivBox->toString();

	CHECK_EQ(expectedOutput, output);
}

TEST_CASE("Test the toString method for the box class when box is empty")
{
	auto plovdivBox = std::make_shared<Box>("PlovdivBox",
		std::vector<std::string>(),
		std::vector<std::shared_ptr<Box>> ());

	std::string nestedIndent = "	";
	std::string expectedOutput = std::string("--------------------------------------------------------\n") +
		"The box is:\n" +
		"Name: PlovdivBox\n" +
		"Souvenirs: \n" +
		"Boxes:\n" +
		"--------------------------------------------------------\n";

	std::string output = plovdivBox->toString();

	CHECK_EQ(expectedOutput, output);
}

TEST_CASE(TestCasesUtil::testCasesStrings.at(TestCasesUtil::TESTS_BOX)(1))
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

	plovdivBox->simplifyBox();

	CHECK_EQ(plovdivBox->getSouvenirs(), std::vector<std::string>{"Magnet", "Book"});
	CHECK_EQ(plovdivBox->getNestedBoxes(), std::vector<std::shared_ptr<Box>>{drawings, plates});

	CHECK_EQ(drawings->getSouvenirs(), std::vector<std::string>{"OldPlovdiv"});
	CHECK_EQ(drawings->getNestedBoxes().size(), 0);

	CHECK_EQ(plates->getSouvenirs(), std::vector<std::string>{"DecorativePlate"});
	CHECK_EQ(plates->getNestedBoxes().size(), 0);
}

TEST_CASE(TestCasesUtil::testCasesStrings.at(TestCasesUtil::TESTS_BOX)(2))
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

	plovdivBox->simplifyBox();

	CHECK_EQ(plovdivBox->getSouvenirs(), std::vector<std::string>{"Magnet", "Book"});
	CHECK_EQ(plovdivBox->getNestedBoxes(), std::vector<std::shared_ptr<Box>>{drawingsNested2, theatreSouvenirs});

	CHECK_EQ(drawingsNested2->getSouvenirs(), std::vector<std::string>{"OldPlovdiv"});
	CHECK_EQ(drawingsNested2->getNestedBoxes().size(), 0);

	CHECK_EQ(theatreSouvenirs->getSouvenirs().size(), 0);
	CHECK_EQ(theatreSouvenirs->getNestedBoxes(), std::vector<std::shared_ptr<Box>>{plates, bags, souvenirsNested4});

	CHECK_EQ(plates->getSouvenirs(), std::vector<std::string>{"DecorativePlate"});
	CHECK_EQ(plates->getNestedBoxes().size(), 0);

	CHECK_EQ(bags->getSouvenirs(), std::vector<std::string>{"BagsSouvenir"});
	CHECK_EQ(bags->getNestedBoxes().size(), 0);

	CHECK_EQ(souvenirsNested4->getSouvenirs(), std::vector<std::string>{"NestedSouvenirItem"});
	CHECK_EQ(souvenirsNested4->getNestedBoxes().size(), 0);
}

TEST_CASE(TestCasesUtil::testCasesStrings.at(TestCasesUtil::TESTS_BOX)(3))
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

	plovdivBox->simplifyBox();

	CHECK_EQ(plovdivBox->getSouvenirs(), std::vector<std::string>{"Magnet", "Book"});
	CHECK_EQ(plovdivBox->getNestedBoxes(), std::vector<std::shared_ptr<Box>>{drawingsNested2, theatreSouvenirs});

	CHECK_EQ(drawingsNested2->getSouvenirs(), std::vector<std::string>{"OldPlovdiv"});
	CHECK_EQ(drawingsNested2->getNestedBoxes().size(), 0);

	CHECK_EQ(theatreSouvenirs->getSouvenirs().size(), 0);
	CHECK_EQ(theatreSouvenirs->getNestedBoxes(), std::vector<std::shared_ptr<Box>>{plates, bags, souvenirsNested4});

	CHECK_EQ(plates->getSouvenirs(), std::vector<std::string>{"DecorativePlate"});
	CHECK_EQ(plates->getNestedBoxes().size(), 0);

	CHECK_EQ(bags->getSouvenirs(), std::vector<std::string>{"BagsSouvenir"});
	CHECK_EQ(bags->getNestedBoxes(), std::vector<std::shared_ptr<Box>>{bagsNested1});

	CHECK_EQ(bagsNested1->getSouvenirs(), std::vector<std::string>{"BagsSouvenirNested1"});
	CHECK_EQ(bagsNested1->getNestedBoxes().size(), 0);

	CHECK_EQ(souvenirsNested4->getSouvenirs(), std::vector<std::string>{"NestedSouvenirItem"});
	CHECK_EQ(souvenirsNested4->getNestedBoxes().size(), 0);
}

TEST_CASE(TestCasesUtil::testCasesStrings.at(TestCasesUtil::TESTS_BOX)(4))
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

	plovdivBox->simplifyBox();

	CHECK_EQ(plovdivBox->getSouvenirs(), std::vector<std::string>{"Magnet", "Book"});
	CHECK_EQ(plovdivBox->getNestedBoxes(), std::vector<std::shared_ptr<Box>>{drawingsNested2, theatreSouvenirs});

	CHECK_EQ(drawingsNested2->getSouvenirs(), std::vector<std::string>{"OldPlovdiv"});
	CHECK_EQ(drawingsNested2->getNestedBoxes().size(), 0);

	CHECK_EQ(theatreSouvenirs->getSouvenirs().size(), 0);
	CHECK_EQ(theatreSouvenirs->getNestedBoxes(), std::vector<std::shared_ptr<Box>>{plates, bags, souvenirsNested4});

	CHECK_EQ(plates->getSouvenirs(), std::vector<std::string>{"DecorativePlate"});
	CHECK_EQ(plates->getNestedBoxes().size(), 0);

	CHECK_EQ(bags->getSouvenirs(), std::vector<std::string>{"BagsSouvenir"});
	CHECK_EQ(bags->getNestedBoxes(), std::vector<std::shared_ptr<Box>>{bagsNested2});

	CHECK_EQ(bagsNested2->getSouvenirs(), std::vector<std::string>{"BagsSouvenirNested2"});
	CHECK_EQ(bagsNested2->getNestedBoxes().size(), 0);

	CHECK_EQ(souvenirsNested4->getSouvenirs(), std::vector<std::string>{"NestedSouvenirItem"});
	CHECK_EQ(souvenirsNested4->getNestedBoxes().size(), 0);
}

TEST_CASE(TestCasesUtil::testCasesStrings.at(TestCasesUtil::TESTS_BOX)(5))
{
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

	plovdivBox->simplifyBox();

	CHECK_EQ(plovdivBox->getSouvenirs(), std::vector<std::string>{"Magnet", "Book"});
	CHECK_EQ(plovdivBox->getNestedBoxes(), std::vector<std::shared_ptr<Box>>{drawingsNested2, theatreSouvenirs});

	CHECK_EQ(drawingsNested2->getSouvenirs(), std::vector<std::string>{"OldPlovdiv"});
	CHECK_EQ(drawingsNested2->getNestedBoxes().size(), 0);

	CHECK_EQ(theatreSouvenirs->getSouvenirs().size(), 0);
	CHECK_EQ(theatreSouvenirs->getNestedBoxes(), std::vector<std::shared_ptr<Box>>{plates, bags, souvenirsNested4});

	CHECK_EQ(plates->getSouvenirs(), std::vector<std::string>{"DecorativePlate"});
	CHECK_EQ(plates->getNestedBoxes().size(), 0);

	CHECK_EQ(bags->getSouvenirs(), std::vector<std::string>{"BagsSouvenir"});
	CHECK_EQ(bags->getNestedBoxes(), std::vector<std::shared_ptr<Box>>{bagsNested1});

	CHECK_EQ(bagsNested1->getSouvenirs(), std::vector<std::string>{"BagsSouvenirNested1"});
	CHECK_EQ(bagsNested1->getNestedBoxes(), std::vector<std::shared_ptr<Box>>{bagsNested2});

	CHECK_EQ(bagsNested2->getSouvenirs(), std::vector<std::string>{"BagsSouvenirNested2"});
	CHECK_EQ(bagsNested2->getNestedBoxes().size(), 0);

	CHECK_EQ(souvenirsNested4->getSouvenirs(), std::vector<std::string>{"NestedSouvenirItem"});
	CHECK_EQ(souvenirsNested4->getNestedBoxes().size(), 0);
}

TEST_CASE(TestCasesUtil::testCasesStrings.at(TestCasesUtil::TESTS_BOX)(6))
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

	plovdivBox->simplifyBox();

	CHECK_EQ(plovdivBox->getSouvenirs(), std::vector<std::string>{"Magnet", "Book"});
	CHECK_EQ(plovdivBox->getNestedBoxes(), std::vector<std::shared_ptr<Box>>{drawingsNested2, theatreSouvenirs});

	CHECK_EQ(drawingsNested2->getSouvenirs(), std::vector<std::string>{"OldPlovdiv"});
	CHECK_EQ(drawingsNested2->getNestedBoxes().size(), 0);

	CHECK_EQ(theatreSouvenirs->getSouvenirs().size(), 0);
	CHECK_EQ(theatreSouvenirs->getNestedBoxes(), std::vector<std::shared_ptr<Box>>{plates, bagsNested1, souvenirsNested4});

	CHECK_EQ(plates->getSouvenirs(), std::vector<std::string>{"DecorativePlate"});
	CHECK_EQ(plates->getNestedBoxes().size(), 0);

	CHECK_EQ(bagsNested1->getSouvenirs(), std::vector<std::string>{"BagsSouvenirNested1"});
	CHECK_EQ(bagsNested1->getNestedBoxes().size(), 0);

	CHECK_EQ(souvenirsNested4->getSouvenirs(), std::vector<std::string>{"NestedSouvenirItem"});
	CHECK_EQ(souvenirsNested4->getNestedBoxes().size(), 0);
}

TEST_CASE(TestCasesUtil::testCasesStrings.at(TestCasesUtil::TESTS_BOX)(7))
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

	plovdivBox->simplifyBox();

	CHECK_EQ(plovdivBox->getSouvenirs(), std::vector<std::string>{"Magnet", "Book"});
	CHECK_EQ(plovdivBox->getNestedBoxes(), std::vector<std::shared_ptr<Box>>{drawingsNested2, theatreSouvenirs});

	CHECK_EQ(drawingsNested2->getSouvenirs(), std::vector<std::string>{"OldPlovdiv"});
	CHECK_EQ(drawingsNested2->getNestedBoxes().size(), 0);

	CHECK_EQ(theatreSouvenirs->getSouvenirs().size(), 0);
	CHECK_EQ(theatreSouvenirs->getNestedBoxes(), std::vector<std::shared_ptr<Box>>{plates, bagsNested2, souvenirsNested4});

	CHECK_EQ(plates->getSouvenirs(), std::vector<std::string>{"DecorativePlate"});
	CHECK_EQ(plates->getNestedBoxes().size(), 0);

	CHECK_EQ(bagsNested2->getSouvenirs(), std::vector<std::string>{"BagsSouvenirNested2"});
	CHECK_EQ(bagsNested2->getNestedBoxes().size(), 0);

	CHECK_EQ(souvenirsNested4->getSouvenirs(), std::vector<std::string>{"NestedSouvenirItem"});
	CHECK_EQ(souvenirsNested4->getNestedBoxes().size(), 0);
}

TEST_CASE(TestCasesUtil::testCasesStrings.at(TestCasesUtil::TESTS_BOX)(8))
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

	plovdivBox->simplifyBox();

	CHECK_EQ(plovdivBox->getSouvenirs(), std::vector<std::string>{"Magnet", "Book"});
	CHECK_EQ(plovdivBox->getNestedBoxes(), std::vector<std::shared_ptr<Box>>{drawingsNested2, theatreSouvenirs});

	CHECK_EQ(drawingsNested2->getSouvenirs(), std::vector<std::string>{"OldPlovdiv"});
	CHECK_EQ(drawingsNested2->getNestedBoxes().size(), 0);

	CHECK_EQ(theatreSouvenirs->getSouvenirs().size(), 0);
	CHECK_EQ(theatreSouvenirs->getNestedBoxes(), std::vector<std::shared_ptr<Box>>{plates, bagsNested1, souvenirsNested4});

	CHECK_EQ(plates->getSouvenirs(), std::vector<std::string>{"DecorativePlate"});
	CHECK_EQ(plates->getNestedBoxes().size(), 0);

	CHECK_EQ(bagsNested1->getSouvenirs(), std::vector<std::string>{"BagsSouvenirNested1"});
	CHECK_EQ(bagsNested1->getNestedBoxes(), std::vector<std::shared_ptr<Box>>{bagsNested2});

	CHECK_EQ(bagsNested2->getSouvenirs(), std::vector<std::string>{"BagsSouvenirNested2"});
	CHECK_EQ(bagsNested2->getNestedBoxes().size(), 0);

	CHECK_EQ(souvenirsNested4->getSouvenirs(), std::vector<std::string>{"NestedSouvenirItem"});
	CHECK_EQ(souvenirsNested4->getNestedBoxes().size(), 0);
}

TEST_CASE(TestCasesUtil::testCasesStrings.at(TestCasesUtil::TESTS_BOX)(9))
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

	plovdivBox->simplifyBox();

	CHECK_EQ(plovdivBox->getSouvenirs(), std::vector<std::string>{"Magnet", "Book"});
	CHECK_EQ(plovdivBox->getNestedBoxes(), std::vector<std::shared_ptr<Box>>{drawingsNested2, theatreSouvenirs});

	CHECK_EQ(drawingsNested2->getSouvenirs(), std::vector<std::string>{"OldPlovdiv"});
	CHECK_EQ(drawingsNested2->getNestedBoxes().size(), 0);

	CHECK_EQ(theatreSouvenirs->getSouvenirs().size(), 0);
	CHECK_EQ(theatreSouvenirs->getNestedBoxes(), std::vector<std::shared_ptr<Box>>{plates, souvenirsNested4});

	CHECK_EQ(plates->getSouvenirs(), std::vector<std::string>{"DecorativePlate"});
	CHECK_EQ(plates->getNestedBoxes().size(), 0);

	CHECK_EQ(souvenirsNested4->getSouvenirs(), std::vector<std::string>{"NestedSouvenirItem"});
	CHECK_EQ(souvenirsNested4->getNestedBoxes().size(), 0);
}

TEST_CASE(TestCasesUtil::testCasesStrings.at(TestCasesUtil::TESTS_BOX)(10))
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

	plovdivBox->simplifyBox();

	CHECK_EQ(plovdivBox->getSouvenirs(), std::vector<std::string>{"Magnet", "Book"});
	CHECK_EQ(plovdivBox->getNestedBoxes(), std::vector<std::shared_ptr<Box>>{drawingsNested2});

	CHECK_EQ(drawingsNested2->getSouvenirs(), std::vector<std::string>{"OldPlovdiv"});
	CHECK_EQ(drawingsNested2->getNestedBoxes().size(), 0);
}

TEST_CASE(TestCasesUtil::testCasesStrings.at(TestCasesUtil::TESTS_BOX)(11))
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

	plovdivBox->simplifyBox();

	CHECK_EQ(plovdivBox->getSouvenirs(), std::vector<std::string>{"OnlyPlovdivSouvenir"});
	CHECK_EQ(plovdivBox->getNestedBoxes().size(), 0);
}

TEST_CASE(TestCasesUtil::testCasesStrings.at(TestCasesUtil::TESTS_BOX)(12))
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

	plovdivBox->simplifyBox();

	CHECK_EQ(plovdivBox->getSouvenirs().size(), 0);
	CHECK_EQ(plovdivBox->getNestedBoxes().size(), 0);
}