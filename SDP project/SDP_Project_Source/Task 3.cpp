#include "Box.h"
#include "StringManip.h"
#include <map>
#include "Task 3.h"

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