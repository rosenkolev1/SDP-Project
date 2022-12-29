#include "Box.h"
#include "StringManip.h"
#include <map>
#include <fstream>

void copyConstructorTest4()
{
    auto plates = std::make_shared<Box>("Plates",
        std::vector<std::string> {"DecorativePlate"}, std::vector<std::shared_ptr<Box>>());

    auto bags = std::make_shared<Box>("Bags",
        std::vector<std::string>(), std::vector<std::shared_ptr<Box>>());

    auto drawings = std::make_shared<Box>("Drawings",
        std::vector<std::string> {"OldPlovdiv"}, std::vector<std::shared_ptr<Box>>());

    auto figurines = std::make_shared<Box>("Figurines",
        std::vector<std::string> {"AncientFigurine"}, std::vector<std::shared_ptr<Box>>());

    auto cups = std::make_shared<Box>("Cups",
        std::vector<std::string> {"TraditionalCup"}, std::vector<std::shared_ptr<Box>>());

    auto staraZagoraBox = std::make_shared<Box>("StaraZagoraBox",
        std::vector<std::string> {"Postcard"}, std::vector<std::shared_ptr<Box>> {figurines, cups});

    auto theatreSouvenirs = std::make_shared<Box>("TheatreSouvenirs",
        std::vector<std::string>(), std::vector<std::shared_ptr<Box>> {plates, bags});

    auto theatreBox = std::make_shared<Box>("TheatreBox",
        std::vector<std::string>(), std::vector<std::shared_ptr<Box>>{ theatreSouvenirs });

    auto artBox = std::make_shared<Box>("ArtBox",
        std::vector<std::string>(), std::vector<std::shared_ptr<Box>> { drawings});

    auto plovdivBox = std::make_shared<Box>("PlovdivBox",
        std::vector<std::string> {"Magnet", "Book"},
        std::vector<std::shared_ptr<Box>> {artBox, theatreBox});

    //plovdivBox->print(std::cout);

    auto plovdivBoxCopy = std::make_shared<Box>(*plovdivBox);

    auto plovdivBoxCopy_Extra = std::make_shared<Box>("PlovdivBox_Extra",
        std::vector<std::string> {"Bell"},
        std::vector<std::shared_ptr<Box>>());

    plovdivBoxCopy->addBox(plovdivBoxCopy_Extra);

    //plovdivBoxCopy->print(std::cout);
    //plovdivBox->print(std::cout);

    auto plovdivBoxCopy2 = *plovdivBox;

    auto plovdivBoxCopy_Extra2 = std::make_shared<Box>("PlovdivBox_Extra2",
        std::vector<std::string> {"Bell2"},
        std::vector<std::shared_ptr<Box>>());

    plovdivBoxCopy2.addBox(plovdivBoxCopy_Extra2);

    //plovdivBox->print(std::cout);
    //plovdivBoxCopy2.print(std::cout);

    *plovdivBoxCopy = plovdivBoxCopy2;
    //plovdivBoxCopy->print(std::cout);

    plovdivBoxCopy2.addBox(plovdivBoxCopy_Extra);
    //plovdivBoxCopy->print(std::cout);
    //plovdivBoxCopy2.print(std::cout);

    /*10
        PlovdivBox 2 Magnet Book 2 ArtBox TheatreBox
        ArtBox 0 1 Drawings
        Drawings 1 OldPlovdiv 0
        TheatreBox 0 1 TheatreSouvenirs
        TheatreSouvenirs 0 2 Plates Bags
        Plates 1 DecorativePlate 0
        Bags 0 0
        StaraZagoraBox 1 Postcard 2 Figurines Cups
        Figurines 1 AncientFigurine 0
        Cups 1 TraditionalCup 0*/

        /*auto plates = new Box("Plates",
            std::vector<std::string> {"DecorativePlate"}, std::vector<Box*>());

        auto bags = new Box("Bags",
            std::vector<std::string>(), std::vector<Box*>());

        auto drawings = new Box("Drawings",
            std::vector<std::string> {"OldPlovdiv"}, std::vector<Box*>());

        auto figurines = new Box("Figurines",
            std::vector<std::string> {"AncientFigurine"}, std::vector<Box*>());

        auto cups = new Box("Cups",
            std::vector<std::string> {"TraditionalCup"}, std::vector<Box*>());

        auto staraZagoraBox = new Box("StaraZagoraBox",
            std::vector<std::string> {"Postcard"}, std::vector<Box*> {figurines, cups});

        auto theatreSouvenirs = new Box("TheatreSouvenirs",
            std::vector<std::string>(), std::vector<Box*> {plates, bags});

        auto theatreBox = new Box("TheatreBox",
            std::vector<std::string>(), std::vector<Box*> {theatreSouvenirs});

        auto artBox = new Box("ArtBox",
            std::vector<std::string>(), std::vector<Box*> {drawings});

        auto plovdivBox = new Box("PlovdivBox",
            std::vector<std::string> {"Magnet", "Book"},
            std::vector<Box*> {artBox, theatreBox});

        plovdivBox->print(std::cout);*/
}

std::string task3(std::ifstream& in)
{
    std::string input = "";

    in >> input;

    long countOfBoxes = StringManip::parseToLong(input);
    auto allNestedBoxes = std::map<std::string, std::vector<std::string>>();
    auto allBoxes = std::vector<std::shared_ptr<Box>>();

    for (int i = 0; i < countOfBoxes; i++)
    {
        in >> input;
        std::string boxName = input;

        in >> input;
        long countOfSouvenirs = StringManip::parseToLong(input);

        std::vector<std::string> souvenirs = std::vector<std::string>();

        for (int y = 0; y < countOfSouvenirs; y++)
        {
            in >> input;
            std::string souvenirName = input;
            souvenirs.push_back(souvenirName);
        }

        auto newBox = std::make_shared<Box>(boxName, souvenirs);

        in >> input;
        long countOfNestedBoxes = StringManip::parseToLong(input);

        std::vector<std::string> nestedBoxes = std::vector<std::string>();

        for (int y = 0; y < countOfNestedBoxes; y++)
        {
            in >> input;
            std::string nestedBoxName = input;
            nestedBoxes.push_back(nestedBoxName);
        }

        if (countOfNestedBoxes > 0)
        {
            allNestedBoxes[boxName] = nestedBoxes;
        }

        allBoxes.push_back(newBox);
    }

    std::vector<std::string> onlyNestedBoxes = std::vector<std::string>();

    //Add all the nested boxes
    for (std::shared_ptr<Box> box : allBoxes)
    {
        if (allNestedBoxes.find(box->getName()) != allNestedBoxes.end())
        {
            for (std::string nestedBoxName : allNestedBoxes[box->getName()])
            {
                for (std::shared_ptr<Box> nestedBox : allBoxes)
                {
                    if (nestedBox->getName() == nestedBoxName)
                    {
                        box->addBox(nestedBox);
                        onlyNestedBoxes.push_back(nestedBox->getName());
                        break;
                    }
                }
            }
        }
    }

    auto topBoxes = std::vector<std::shared_ptr<Box>>();

    //Get the most containing boxes
    for (std::shared_ptr<Box> box : allBoxes)
    {
        if (std::count(onlyNestedBoxes.begin(), onlyNestedBoxes.end(), box->getName()) == 0)
        {
            topBoxes.push_back(box);
        }
    }

    //Simplify the most containing boxes
    for (auto box : topBoxes)
    {
        box->simplifyBox();
    }

    std::string res = "";

    //Print only the outer most boxes
    for (std::shared_ptr<Box> box : topBoxes)
    {
        //Check if one of the top boxes is completely empty after simplifying
        if (box->getNestedBoxes().size() != 0 || box->getSouvenirs().size() != 0)
        {
            res += box->toString();
        }
    }

    return res;
}