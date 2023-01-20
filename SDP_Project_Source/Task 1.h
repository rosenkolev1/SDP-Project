#pragma once
#include "SkipList.h"
#include "StringManip.h"

bool pathContainsAllRequired(std::vector<const Node<std::string>*> visited, std::vector<std::string> requiredCities);

bool pathIsValid(std::vector<const Node<std::string>*> visited, std::vector<std::string> requiredCities,
    std::string startCity, std::string endCity);

std::vector<std::vector<const Node<std::string>*>> getPathsDFS(const Node<std::string>* curCity, std::vector<const Node<std::string>*> visited,
    std::vector<std::string> requiredCities, std::string startCity, std::string endCity, int maxSize);

std::vector<std::vector<const Node<std::string>*>> getAllPaths(const SkipList<std::string>& list, std::vector<std::string> requiredCities,
    std::string startCity, std::string endCity);

void task1(std::ostream& os, std::istream& is);