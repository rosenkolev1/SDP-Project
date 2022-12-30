#include "Task 2.h"

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

        bool curPathEndAtRailstation = false;
        if (curPath.size() >= 2)
        {
            auto toNode = curPath.back().to;
            curPathEndAtRailstation = toNode == start;

            if (curPathEndAtRailstation)
            {
                allPaths.push_back(curPath);
            }
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
                }

                //Check if the new edge destination has already been visited N times, where N is the number of vertecies(landmarks) in the graph.
                //The worst case scenario for the number of times the best path(the one which visits the most landmarks) visits the new destination is N times.
                int timesVisited = 0;
                for (auto& visitedEdge : curPath)
                {
                    if (visitedEdge.to == edge.to) timesVisited++;
                }

                if (timesVisited == graph.getVertexesCount())
                {
                    continue;
                }


                timesVisited = 0;
                //Check if the new edge has already been visited twice. A third travel through any given edge is useless and therefore the path is not the shortest possible
                for (auto& visitedEdge : curPath)
                {
                    if (edge.edgeDestinationsAreSame(visitedEdge)) timesVisited++;
                }

                if (timesVisited == 2)
                {
                    continue;
                }

                curPaths.push(curPathCopy);
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