#include "Task 1.h"
#include <unordered_map>

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

void printToConsole(std::istream& is, std::string text)
{
    if (&is == &std::cin) std::cout << text;
}

void task1(std::ostream& os, std::istream& is)
{
    int n = 0;
    printToConsole(is, "Count of cities: ");
    is >> n;

    std::unordered_map<std::string, Node<std::string>* > cities;
    std::string startCity = "";
    std::string endCity = "";

    printToConsole(is, "Names of cities: ");

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

    printToConsole(is, "Direct lines:\n");
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

    printToConsole(is, "Cities of Ana and Vankata: ");

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
    printToConsole(is, "\n");
    os << "The shortest path that visits each of the necessary cities is: ";

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