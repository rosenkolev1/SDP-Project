#include "Task 2.h"
#include "PathInfo.h"

PathInfo task2_getBestPathInTime(const UndirectedGraph<std::string>& graph, std::string start, int maxTime)
{
    std::queue<PathInfo> curPaths;
    curPaths.push(PathInfo(start));

    std::vector<PathInfo> tempCurPaths = std::vector<PathInfo>();

    auto allPaths = std::vector<PathInfo>();

    while (true)
    {
        auto curPathInfo = curPaths.front();

        std::string currentNode = curPathInfo.lastEdge;

        auto allConnected = graph.getVertexEdges()[currentNode];

        /*if (curPathInfo.lastEdge == start)
        {
            allPaths.push_back(curPathInfo);
        }*/
        allPaths.push_back(curPathInfo);

        for (auto edge : allConnected)
        {
            if (curPathInfo.timeTaken + edge.weight <= maxTime)
            {
                auto curPathInfoCopy = curPathInfo;

                if (edge.to == currentNode)
                {
                    edge.to = edge.from;
                    edge.from = currentNode;
                }

                curPathInfoCopy.addEdge(edge);

                if (curPathInfoCopy.visitedLandmarks.size() == graph.getVertexesCount() &&
                    curPathInfoCopy.lastEdge == start)
                {
                    return curPathInfoCopy;
                }

                //Check if we can remove the current path because it is useless
                bool uselessPath = false;
                for (auto pathInfo : allPaths)
                {
                    if (pathInfo.visitedLandmarks.size() >= curPathInfoCopy.visitedLandmarks.size() &&
                        pathInfo.lastEdge == curPathInfoCopy.lastEdge &&
                        pathInfo.timeTaken < curPathInfoCopy.timeTaken)
                    {
                        uselessPath = true;
                        break;
                    }
                }

                if (uselessPath) continue;

                //Check if we can remove any of the future BFS paths because they are useless

                std::vector<int> uselessTempCurPathsIndexes = std::vector<int>();
                for (int i = 0; i < tempCurPaths.size(); i++)
                {
                    auto pathInfo = tempCurPaths[i];
                    if (pathInfo.visitedLandmarks.size() >= curPathInfoCopy.visitedLandmarks.size() &&
                        pathInfo.lastEdge == curPathInfoCopy.lastEdge &&
                        pathInfo.timeTaken > curPathInfoCopy.timeTaken)
                    {
                        tempCurPaths[i] = tempCurPaths.back();
                        tempCurPaths.pop_back();
                        i--;
                    }
                }   

                //Check if an edge has been visited more than 3 times. If so, then that path is not the shortest path which visits
                //the same nodes and ends up at the same last node
                if (curPathInfoCopy.edgesVisitations[edge] == 3)
                {
                    continue;
                }

                tempCurPaths.push_back(curPathInfoCopy);
            }
        }

        curPaths.pop();

        if (curPaths.empty())
        {
            if (tempCurPaths.empty()) 
            {
                break;
            }
            else 
            {
                for (auto tempCurPath : tempCurPaths)
                {
                    curPaths.push(tempCurPath);
                }

                tempCurPaths.clear();
            }
        }
    }

    //Get the best path
    auto bestPath = allPaths[0];

    for (int i = 1; i < allPaths.size(); i++)
    {
        auto curPath = allPaths[i];

        if (curPath.lastEdge == start && curPath.visitedLandmarks.size() > bestPath.visitedLandmarks.size())
        {
            bestPath = curPath;
        }
    }
    return bestPath;
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

    PathInfo bestPath = task2_getBestPathInTime(landmarkGraph, RAILSTATION, maxTime);

    std::string bestPathString = "";
    bestPathString += "Best Path: " + RAILSTATION + (0 != bestPath.curPath.size() ? " --> " : "");

    int pathTime = 0;

    for (int y = 0; y < bestPath.curPath.size(); y++)
    {
        bestPathString += bestPath.curPath[y].to + (y != bestPath.curPath.size() - 1 ? " --> " : "");
    }

    return bestPathString;
}