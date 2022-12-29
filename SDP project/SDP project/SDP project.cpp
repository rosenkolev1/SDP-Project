// SDP project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <map>
#include "SkipList.h"
#include "StringManip.h"
#include "UndirectedGraph.h"
#include <fstream>
#include <queue>
#include "Box.h"

void copyConstructorTest1()
{
    auto sofiaN = new Node<std::string>("Sofia");
    auto pazardzhikN = new Node<std::string>("Pazardzhik");
    auto plovdivN = new Node<std::string>("Plovdiv");
    auto dimitrovgradN = new Node<std::string>("Dimitrovgrad");
    auto staraZagoraN = new Node<std::string>("StaraZagora");
    auto novaZagoraN = new Node<std::string>("NovaZagora");
    auto yambolN = new Node<std::string>("Yambol");
    auto karnobatN = new Node<std::string>("Karnobat");
    auto burgasN = new Node<std::string>("Burgas");

    sofiaN->next = pazardzhikN;
    pazardzhikN->next = plovdivN;
    plovdivN->next = dimitrovgradN;
    dimitrovgradN->next = staraZagoraN;
    staraZagoraN->next = novaZagoraN;
    novaZagoraN->next = yambolN;
    yambolN->next = karnobatN;
    karnobatN->next = burgasN;

    //Special connections
    sofiaN->spec = plovdivN;
    plovdivN->spec = novaZagoraN;
    dimitrovgradN->spec = novaZagoraN;
    staraZagoraN->spec = yambolN;
    novaZagoraN->spec = burgasN;

    auto normalList = SkipList<std::string>(sofiaN);
    auto copiedList = SkipList<std::string>(normalList);

    std::cout << normalList.toString();
    std::cout << copiedList.toString();
}

void copyConstructorTest2()
{
    auto sofiaN = new Node<std::string>("Sofia");
    auto pazardzhikN = new Node<std::string>("Pazardzhik");
    auto plovdivN = new Node<std::string>("Plovdiv");
    auto dimitrovgradN = new Node<std::string>("Dimitrovgrad");
    auto staraZagoraN = new Node<std::string>("StaraZagora");
    auto novaZagoraN = new Node<std::string>("NovaZagora");
    auto yambolN = new Node<std::string>("Yambol");
    auto karnobatN = new Node<std::string>("Karnobat");
    auto burgasN = new Node<std::string>("Burgas");

    sofiaN->next = pazardzhikN;
    pazardzhikN->next = plovdivN;
    plovdivN->next = dimitrovgradN;
    dimitrovgradN->next = staraZagoraN;
    staraZagoraN->next = novaZagoraN;
    novaZagoraN->next = yambolN;
    yambolN->next = karnobatN;
    karnobatN->next = burgasN;

    //Special connections
    sofiaN->spec = plovdivN;
    plovdivN->spec = novaZagoraN;
    dimitrovgradN->spec = novaZagoraN;
    staraZagoraN->spec = yambolN;
    novaZagoraN->spec = burgasN;

    yambolN->spec = dimitrovgradN;
    burgasN->spec = sofiaN;

    auto normalList = SkipList<std::string>(sofiaN);
    auto copiedList = normalList;

    
}

bool pathContainsAllRequired(std::vector<const Node<std::string>*> visited, std::vector<std::string> requiredCities)
{
    for (std::string required : requiredCities)
    {
        auto hasVisitedRequired = false;

        for (auto visitedCity : visited)
        {
            if (visitedCity->key == required)
            {
                hasVisitedRequired = true;
                break;
            }
        }

        if (!hasVisitedRequired) return false;
    }

    return true;
}

bool pathIsValid(std::vector<const Node<std::string>*> visited, std::vector<std::string> requiredCities,
    std::string startCity, std::string endCity)
{
    return visited.front()->key == startCity && visited.back()->key == endCity
        && pathContainsAllRequired(visited, requiredCities);
}

std::vector<std::vector<const Node<std::string>*>> getPathsDFS(const Node<std::string>* curCity, std::vector<const Node<std::string>*> visited, 
    std::vector<std::string> requiredCities, std::string startCity, std::string endCity, int maxSize)
{
    if (curCity->next == nullptr && curCity->spec == nullptr)
    {
        if (pathIsValid(visited, requiredCities, startCity, endCity))
        {
            return std::vector<std::vector<const Node<std::string>*>> { visited };
        }

        return std::vector<std::vector<const Node<std::string>*>>();
    }

    if (visited.size() == maxSize)
    {
        if (pathIsValid(visited, requiredCities, startCity, endCity))
        {
            return std::vector<std::vector<const Node<std::string>*>> { visited };
        }
        
        return std::vector<std::vector<const Node<std::string>*>>();
    }

    //Check if the current subpath contains useless moves (A --> B --> A --> B)
    if (visited.size() >= 4)
    {
        int index = visited.size() - 4;
        auto first = visited[index++];
        auto second = visited[index++];
        auto third = visited[index++];
        auto fourth = visited[index++];

        if (first == third && second == fourth)
        {
            return std::vector<std::vector<const Node<std::string>*>>();
        }
    }

    //Check if a current subpath is valid and add it
    auto validPaths = std::vector<std::vector<const Node<std::string>*>>();

    if (pathIsValid(visited, requiredCities, startCity, endCity))
    {
        validPaths.push_back(std::vector<const Node<std::string>*> { visited });
    }

    std::vector<std::vector<const Node<std::string>*>> pathsNext;
    if (curCity->next != nullptr)
    {
        visited.push_back(curCity->next);
        pathsNext = getPathsDFS(curCity->next, visited, requiredCities, startCity, endCity, maxSize);
        visited.pop_back();
    }

    std::vector<std::vector<const Node<std::string>*>> pathsSpec;
    if (curCity->spec != nullptr)
    {
        visited.push_back(curCity->spec);
        pathsSpec = getPathsDFS(curCity->spec, visited, requiredCities, startCity, endCity, maxSize);
        visited.pop_back();
    }

    validPaths.insert(validPaths.end(), pathsNext.begin(), pathsNext.end());
    validPaths.insert(validPaths.end(), pathsSpec.begin(), pathsSpec.end());

    return validPaths;
}

std::vector<std::vector<const Node<std::string>*>> getAllPaths(const SkipList<std::string>& list, std::vector<std::string> requiredCities,
    std::string startCity, std::string endCity)
{
    if (list.getHead() == nullptr) throw std::exception("There are no cities to get the paths for!");

    auto allPaths = getPathsDFS(list.getHead(), std::vector<const Node<std::string>*> { list.getHead() }, 
        requiredCities, startCity, endCity, list.getSize());

    return allPaths;
}

void task1(std::ostream& os, std::istream& is)
{
    int n = 0;
    os << "Count of cities: ";
    is >> n;

    std::map<std::string, Node<std::string>* > cities;
    std::string startCity = "";
    std::string endCity = "";

    os << "Names of cities: ";

    std::string cityName = "";
    for (int i = 0; i < n; i++)
    {
        auto prevNode = cities[cityName];
        is >> cityName;
        auto newNode = new Node<std::string>(cityName);
        
        if (startCity == "") startCity = cityName;
        else prevNode->next = newNode;

        newNode->prev = prevNode;

        if (i == n - 1) endCity = cityName;

        cities[cityName] = newNode;
    }

    os << "Direct lines:\n";
    is.ignore();
    while (true)
    {
        std::string directLine = "";
        std::getline(is, directLine);

        if (directLine == "Stop") break;

        std::vector<std::string> splitInput = StringManip::splitString(directLine, " ");
        std::string from = splitInput[0];
        std::string to = splitInput[1];

        cities[from]->spec = cities[to];
    }

    os << "Cities of Ana and Vankata: ";

    std::string citiesRequiredString = "";
    std::getline(is, citiesRequiredString);

    std::vector<std::string> citiesRequired = StringManip::splitString(citiesRequiredString, " ");

    auto citiesList = SkipList<std::string>(cities[startCity]);

    //Perform DFS and return all the routes from a to b
    auto pathsNodes = getAllPaths(citiesList, citiesRequired, startCity, endCity);

    std::vector<const Node<std::string>*> shortestPath = pathsNodes[0];

    for (int i = 1; i < pathsNodes.size(); i++)
    {
        auto& curPath = pathsNodes[i];

        if (curPath.size() < shortestPath.size())
        {
            shortestPath = curPath;
        }
    }

    os << std::endl << "The shortest path that visits each of the necessary cities is: ";

    //Print the result
    for (int i = 0; i < shortestPath.size(); i++)
    {
        os << shortestPath[i]->key << (i != shortestPath.size() - 1 ? " --> " : "");
    }
    os << std::endl;

    //9
    //Sofia Pazardzhik Plovdiv Dimitrovgrad StaraZagora NovaZagora Yambol Karnobat Burgas
    //Sofia Plovdiv
    //Plovdiv NovaZagora
    //Dimitrovgrad NovaZagora
    //StaraZagora Yambol
    //NovaZagora Burgas
    //Stop
    //Plovdiv StaraZagora Yambol

    //9
    //Sofia Pazardzhik Plovdiv Dimitrovgrad StaraZagora NovaZagora Yambol Karnobat Burgas
    //Sofia Plovdiv
    //Plovdiv NovaZagora
    //Dimitrovgrad NovaZagora
    //StaraZagora Yambol
    //NovaZagora Burgas
    //Karnobat Sofia
    //Yambol StaraZagora
    //Pazardzhik Yambol
    //Burgas Plovdiv
    //Stop
    //Plovdiv StaraZagora Yambol

    //9
    //Sofia Pazardzhik Plovdiv Dimitrovgrad StaraZagora NovaZagora Yambol Karnobat Burgas
    //Sofia Plovdiv
    //Plovdiv Burgas
    //Dimitrovgrad NovaZagora
    //StaraZagora Yambol
    //NovaZagora Burgas
    //Karnobat Sofia
    //Yambol StaraZagora
    //Pazardzhik Sofia
    //Burgas Plovdiv
    //Stop
    //Plovdiv

    //9
    //Sofia Pazardzhik Plovdiv Dimitrovgrad StaraZagora NovaZagora Yambol Karnobat Burgas
    //Stop
    //Plovdiv StaraZagora Yambol

    //9
    //Sofia Pazardzhik Plovdiv Dimitrovgrad StaraZagora NovaZagora Yambol Karnobat Burgas
    //Pazardzhik Burgas
    //Plovdiv Pazardzhik
    //Stop
    //Plovdiv

    //9
    //Sofia Pazardzhik Plovdiv Dimitrovgrad StaraZagora NovaZagora Yambol Karnobat Burgas
    //Pazardzhik Burgas
    //Burgas NovaZagora
    //NovaZagora Pazardzhik
    //Stop
    //NovaZagora
}

void constructorTest3()
{
    auto someGraph = UndirectedGraph<std::string>();
    someGraph.addEdge("Railstation", "RomanStadium", 20);
    someGraph.addEdge("Railstation", "ArtGallery", 26);
    someGraph.addEdge("RomanStadium", "DzhumayaSquare", 2);
    someGraph.addEdge("ArtGallery", "DzhumayaSquare", 5);
    someGraph.addEdge("ArtGallery", "AntiqueTheatre", 7);
    someGraph.addEdge("ArtGallery", "HistoricalMuseum", 14);
    someGraph.addEdge("DzhumayaSquare", "HistoricalMuseum", 18);
    someGraph.addEdge("HistoricalMuseum", "AntiqueTheatre", 12);
    //Repeating
    someGraph.addEdge("DzhumayaSquare", "HistoricalMuseum", 9);

    someGraph.print(std::cout);

    auto secondGraph = someGraph;
    secondGraph.print(std::cout);
}

std::vector<std::vector<GraphEdge<std::string>> > task2_getAllPathsInTime(const UndirectedGraph<std::string>& graph, std::string start, int maxTime)
{
    std::queue<std::vector<GraphEdge<std::string>> > curPaths;
    curPaths.push(std::vector<GraphEdge<std::string>>());

    auto allPaths = std::vector<std::vector<GraphEdge<std::string>> >();
    
    while (true)
    {
        auto something = graph.getVertexEdges();
        auto curPath = curPaths.front();

        std::string currentNode = (!curPath.empty() ? curPath.back().to : start);

        auto allConnected = graph.getVertexEdges()[currentNode];

        int curPathTime = 0;
        for (auto edge : curPath)
        {
            curPathTime += edge.weight;
        }

        for (auto edge : allConnected)
        {
            if (curPathTime + edge.weight <= maxTime)
            {
                auto curPathCopy = curPath;

                if (edge.to == currentNode)
                {
                    edge.to = edge.from;
                    edge.from = currentNode;
                }

                curPathCopy.push_back(edge);

                //Get last 3 edges from path and check if there are pointless movements. If there are, do not add this new path
                //This remove A LOT of unnecessary paths (in one of the tests, the total amount of paths changes from ~85,000 to 118).
                if (curPathCopy.size() >= 3)
                {
                    auto firstEdge = curPathCopy[curPathCopy.size() - 3];
                    auto secondEdge = curPathCopy[curPathCopy.size() - 2];
                    auto thirdEdge = curPathCopy[curPathCopy.size() - 1];

                    if (firstEdge.edgeDestinationsAreSame(secondEdge) && secondEdge.edgeDestinationsAreSame(thirdEdge) &&
                        firstEdge.from == thirdEdge.from && firstEdge.to == thirdEdge.to)
                    {
                        continue;
                    }
                    else if (firstEdge.edgeDestinationsAreSame(secondEdge) && secondEdge.edgeDestinationsAreSame(thirdEdge) &&
                        firstEdge.edgeDestinationsAreSame(thirdEdge))
                    {
                        //Debug shit
                        int z = 100;
                    }
                }

                curPaths.push(curPathCopy);
            }
        }

        if (curPath.size() >= 2)
        {
            auto toNode = curPath.back().to;

            if (toNode == start)
            {
                allPaths.push_back(curPath);
            }         
        }

        curPaths.pop();

        if (curPaths.empty())
        {
            break;
        }
    }

    return allPaths;
}

std::string task2(std::ifstream& in)
{
    const std::string RAILSTATION = "Railstation";

    std::string input = "";

    in >> input;
    long numberOfObjects = StringManip::parseToLong(input);

    in >> input;
    long numberOfEdges = StringManip::parseToLong(input);

    auto landmarkGraph = UndirectedGraph<std::string>();

    in.ignore();
    for (int i = 0; i < numberOfEdges; i++)
    {
        std::getline(in, input);
        auto splitInput = StringManip::splitString(input, " ");

        auto from = splitInput[0];
        auto to = splitInput[1];
        auto weight = StringManip::parseToLong(splitInput[2]);
        landmarkGraph.addEdge(from, to, weight);
    }

    int maxTime = -1;
    in >> input;
    maxTime = StringManip::parseToLong(input);

    auto allPaths = task2_getAllPathsInTime(landmarkGraph, RAILSTATION, maxTime);

    for (int i = 0; i < allPaths.size(); i++)
    {
        std::cout << "Path " << i << ": " << RAILSTATION << (0 != allPaths[i].size() ? " --> " : "");

        int pathTime = 0;
        for (int y = 0; y < allPaths[i].size(); y++)
        {
            pathTime += allPaths[i][y].weight;
            std::cout << allPaths[i][y].to << (y != allPaths[i].size() - 1 ? " --> " : "");
        }
        std::cout << " | TIME: " << pathTime;
        std::cout << std::endl;
    }

    if (allPaths.empty())
    {
        return RAILSTATION;
    }
    else
    {
        auto bestPath = std::vector<GraphEdge<std::string>>();
        int mostLandmarksVisited = 1;

        for (int i = 0; i < allPaths.size(); i++)
        {
            std::map<std::string, int> visitedLandmarks;
            visitedLandmarks[RAILSTATION] = 1;

            for (auto curEdge : allPaths[i])
            {
                if (visitedLandmarks.find(curEdge.to) == visitedLandmarks.end())
                {
                    visitedLandmarks[curEdge.to] = 1;
                }
            }

            int visitedLandmarksCount = visitedLandmarks.size();

            if (visitedLandmarksCount > mostLandmarksVisited)
            {
                bestPath = allPaths[i];
                mostLandmarksVisited = visitedLandmarksCount;
            }
        }

        std::string bestPathString = "";
        bestPathString += "Best Path: " + RAILSTATION + (0 != bestPath.size() ? " --> " : "");

        int pathTime = 0;

        for (int y = 0; y < bestPath.size(); y++)
        {
            bestPathString += bestPath[y].to + (y != bestPath.size() - 1 ? " --> " : "");
        }

        return bestPathString;
    }
}

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

int main()
{
    //TASK 1
    copyConstructorTest1();
    /*for (int i = 0; i < 1000000; i++)
    {
        copyConstructorTest2();
    }*/

    //task1(std::cout, std::cin);

    //TASK 2
    //constructorTest3();
    /*std::ifstream is("Plovdiv.txt");
    std::cout << task2(is);
    is.close();
    
    std::cout << std::endl;*/
    
    /*std::ifstream is2("test_task2.txt");
    std::cout << task2(is2);
    is2.close();*/

    //TASK3 
    /*for (int i = 0; i < 1000000; i++)
    {
        copyConstructorTest4();
    }  */
    /*copyConstructorTest4();*/

    /*std::ifstream is3("boxesList.txt");
    std::cout << task3(is3);
    is3.close();*/

    /*std::ifstream is4("test_task3_boxesList.txt");
    std::cout << task3(is4);
    is4.close();*/
}
