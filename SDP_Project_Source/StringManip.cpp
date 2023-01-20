#include <stdexcept>
#include "StringManip.h"

std::vector<std::string> StringManip::parseIntoVector(std::string* arr, size_t size)
{
    std::vector<std::string> res;

    for (int i = 0; i < size; i++)
    {
        res.push_back(arr[i]);
    }

    delete[] arr;

    return res;
}

std::string StringManip::parseToString(int integer)
{
    if (integer == 0)
    {
        return std::string("0");
    }

    bool isNegativeInt = integer < 0;

    int integerCopy = integer;
    int digitsCount = 0;
    while (integerCopy != 0)
    {
        digitsCount++;
        integerCopy /= 10;
    }

    int charsCount = digitsCount + 1;
    if (isNegativeInt) charsCount++;

    std::string parsedInt;
    int positiveInteger = abs(integer);

    for (int i = charsCount - 2; i >= (isNegativeInt ? 1 : 0); i--)
    {
        int digit = positiveInteger % 10;
        parsedInt.insert(0, std::to_string((char)digit + '0'));
        positiveInteger /= 10;
    }

    if (isNegativeInt)  parsedInt.insert(0, std::to_string('-'));

    return parsedInt;
}

std::string StringManip::parseToString(size_t integer)
{
    if (integer == 0)
    {
        return std::string("0");
    }

    size_t integerCopy = integer;
    int digitsCount = 0;
    while (integerCopy != 0)
    {
        digitsCount++;
        integerCopy /= 10;
    }

    int charsCount = digitsCount + 1;

    std::string parsedInt;

    for (int i = charsCount - 2; i >= 0; i--)
    {
        int digit = integer % 10;
        parsedInt.insert(0, std::to_string((char)digit + '0'));
        integer /= 10;
    }

    return parsedInt;
}

long StringManip::parseToLong(std::string text)
{
    char* dataOfText = new char[text.size() + 1];
    for (size_t i = 0; i < text.size(); i++)
    {
        dataOfText[i] = text[i];
    }
    dataOfText[text.size()] = '\0';
    long number = std::strtol(dataOfText, nullptr, 10);

    delete[] dataOfText;

    return number;
}

std::vector<std::string> StringManip::splitString(const std::string& input, char delim)
{
    std::vector<std::string> stringResult = splitString(input, std::to_string(delim));

    return stringResult;
}

std::vector<std::string> StringManip::splitString(const std::string& input, const std::string& delim)
{
    //if the delim is empty, then just return an array of one string
    if (delim.size() == 0)
    {
        std::vector<std::string> newArray = { input, ""};
        return newArray;
    }

    size_t sizeOfInput = input.size();
    size_t numberOfStrings = 1;
    for (size_t i = 0; i < sizeOfInput; i++)
    {
        if (input[i] == delim[0])
        {
            bool foundDelim = true;
            if (sizeOfInput - i < delim.size()) foundDelim = false;
            else
            {
                for (size_t y = 1; y < delim.size(); y++)
                {
                    if (i + y >= input.size() - 1 && y + 1 < delim.size())
                    {
                        foundDelim = false;
                        break;
                    }
                    if (input[i + y] != delim[y])
                    {
                        foundDelim = false;
                        break;
                    }
                }
            }

            if (foundDelim)
            {
                numberOfStrings++;
                i += delim.size() - 1;
            }
        }
    }

    std::string* arrayOfStrings = new std::string[numberOfStrings];

    size_t currentStringIndex = 0;
    size_t delimStartIndex = 0;
    size_t delimEndIndex = 0;
    std::string modifiedInput = input;

    //Split the string
    for (size_t i = 0; i < modifiedInput.size(); i++)
    {
        if (modifiedInput[i] == delim[0])
        {
            bool foundDelim = true;
            delimStartIndex = i;
            delimEndIndex = delimStartIndex + delim.size() - 1;
            if (modifiedInput.size() - i < delim.size()) foundDelim = false;
            else
            {
                for (size_t y = 1; y < delim.size(); y++)
                {
                    if (i + y >= modifiedInput.size() - 1 && y + 1 < delim.size())
                    {
                        foundDelim = false;
                        break;
                    }
                    if (modifiedInput[i + y] != delim[y])
                    {
                        foundDelim = false;
                        break;
                    }
                }
            }

            if (foundDelim)
            {
                arrayOfStrings[currentStringIndex] = (delimStartIndex > 0 ? StringManip::getFrom(modifiedInput, 0, delimStartIndex - 1) : "");
                modifiedInput = StringManip::replaceFrom(modifiedInput, "", 0, delimEndIndex);
                i = -1;
                currentStringIndex++;
            }
        }
    }
    arrayOfStrings[currentStringIndex++] = modifiedInput;

    auto res = parseIntoVector(arrayOfStrings, numberOfStrings);
    return res;
}

std::string* StringManip::splitStringMany(const std::string& input, const std::string& delims, size_t& sizeOfArray)
{
    std::string* delimsStringArray = new std::string[delims.size()];

    for (size_t i = 0; i < delims.size(); i++)
    {
        delimsStringArray[i] = delims[i];
    }

    std::string* splitInput = splitStringMany(input, delimsStringArray, delims.size(), sizeOfArray);

    delete[] delimsStringArray;

    return splitInput;
}

std::string* StringManip::splitStringMany(const std::string& input, const std::string* delims, size_t sizeOfDelimsArrays, size_t& sizeOfArray)
{
    //If the sizeOfDelimsArray == 0 or if the input is an empty string, then just return the input
    if (sizeOfDelimsArrays == 0 || input.size() == 0)
    {
        std::string* splitInput = new std::string[1];
        splitInput[0] = input;
        sizeOfArray = 1;
        return splitInput;
    }

    sizeOfArray = StringManip::countOfMany(input, delims, sizeOfDelimsArrays) + 1;
    std::string* finalSplitInput = new std::string[sizeOfArray];
    size_t finalSplitInputIndex = 0;

    //For each word in delims, check where it's first occurance is. Split by the earliest occurance, then jump in the iteration by the length of the delim string.
    size_t startIndexSearch = 0;
    size_t endIndexSearch = input.size() - 1;

    while (true)
    {
        std::string earliestOccuranceWord = delims[0];
        int earliestOccuranceIndex = StringManip::findIndex(input, earliestOccuranceWord, startIndexSearch, endIndexSearch);

        for (size_t i = 1; i < sizeOfDelimsArrays; i++)
        {
            const std::string& delim = delims[i];
            int earliestOccuranceIndexOfDelim = StringManip::findIndex(input, delim, startIndexSearch, endIndexSearch);

            if ((earliestOccuranceIndexOfDelim < earliestOccuranceIndex && earliestOccuranceIndex > -1 && earliestOccuranceIndexOfDelim > -1)
                || (earliestOccuranceIndex == -1 && earliestOccuranceIndexOfDelim > -1))
            {
                earliestOccuranceIndex = earliestOccuranceIndexOfDelim;
                earliestOccuranceWord = delim;
            }
        }

        //If we run out of splitters, then get the last remaining split part of the string and break out of the loop
        if (earliestOccuranceIndex == -1)
        {
            //If there are no characters left to take after the last delim, then take an empty string
            size_t lastSplitPartIndex = startIndexSearch;
            if (lastSplitPartIndex > input.size() - 1 && lastSplitPartIndex > 0)
            {
                finalSplitInput[finalSplitInputIndex] = "";
                finalSplitInputIndex++;

                break;
            }

            //Get the split part of the input and store it in the final split string array
            std::string splitInput;
            for (size_t i = 0; i < input.size() - lastSplitPartIndex; i++)
            {
                splitInput += input[i + lastSplitPartIndex];
            }
            //splitInput += '\0';

            finalSplitInput[finalSplitInputIndex++] = splitInput;

            break;
        }

        //Get the split part of the input and store it in the final split string array
        std::string splitInput;
        for (size_t i = 0; i < earliestOccuranceIndex - startIndexSearch; i++)
        {
            splitInput += input[i + startIndexSearch];
        }

        //splitInput += '\0';

        finalSplitInput[finalSplitInputIndex++] = splitInput;

        //Change the starting point of the search in input for splitters
        startIndexSearch = earliestOccuranceIndex + earliestOccuranceWord.size();
    }

    sizeOfArray = finalSplitInputIndex;
    return finalSplitInput;
}

bool StringManip::stringContainsInvalidChars(const std::string& text, const std::string& invalidChars)
{
    for (size_t i = 0; i < text.size(); i++)
    {
        char textChar = text[i];
        if (stringContains(invalidChars, textChar)) return true;
    }

    //If we get to here, that means that the string passed the test and doesn't contain invalid chars.
    return false;
}

bool StringManip::stringContains(const std::string& text, const char other)
{
    for (size_t i = 0; i < text.size(); i++)
    {
        char textChar = text[i];
        if (textChar == other) return true;
    }
    return false;
}

bool StringManip::stringContains(const std::string& text, const std::string& other)
{
    for (size_t i = 0; i < text.size(); i++)
    {
        if (text[i] == other[0])
        {
            bool stringIsFound = true;
            if (text.size() - i < other.size()) stringIsFound = false;
            else
            {
                for (size_t y = 1; y < other.size(); y++)
                {
                    if (i + y >= text.size() - 1 && y + 1 < other.size())
                    {
                        stringIsFound = false;
                        break;
                    }
                    if (text[i + y] != other[y])
                    {
                        stringIsFound = false;
                        break;
                    }

                }
            }

            if (stringIsFound) return true;
        }
    }

    //If we get to here, then the string hasn't been found
    return false;
}

bool StringManip::stringStartsWith(const std::string& text, const std::string& other)
{
    if (text.size() < other.size()) return false;

    for (size_t i = 0; i < other.size(); i++)
    {
        if (text[i] != other[i]) return false;
    }

    //If we get to here, then the text starts with other
    return true;
}

bool StringManip::stringEndsWith(const std::string& text, const std::string& other)
{
    if (text.size() < other.size()) return false;

    size_t otherIndex = 0;
    for (size_t i = text.size() - other.size(); i < text.size(); i++)
    {
        if (text[i] != other[otherIndex++]) return false;
    }

    //If we get to here, then the text starts with other
    return true;
}

std::string StringManip::concatStrings(const std::string* strings, size_t stringsCount)
{
    std::string concatString;

    for (size_t i = 0; i < stringsCount; i++)
    {
        concatString += strings[i];
    }

    return concatString;
}

std::string StringManip::replaceAll(const std::string& text, const std::string& replaced, const std::string& replacement)
{
    size_t countOfStrings = 0;
    std::vector<std::string> textStrings = splitString(text, replaced);
    size_t finalTextStringsCount = countOfStrings * 2 - 1;
    std::string* finalTextStrings = new std::string[finalTextStringsCount];
    size_t textStringsIndex = 0;
    for (size_t i = 0; i < finalTextStringsCount; i++)
    {
        if (i % 2 == 0)
        {
            finalTextStrings[i] = textStrings[textStringsIndex++];
        }
        else
        {
            finalTextStrings[i] = replacement;
        }
    }
    std::string finalText = concatStrings(finalTextStrings, finalTextStringsCount);

    //Delete dynamic memory
    delete[] finalTextStrings;

    return finalText;
}

std::string StringManip::replaceFirst(const std::string& text, const std::string& replaced, const std::string& replacement)
{
    size_t countOfStrings = 0;
    std::vector<std::string> textStrings = splitString(text, replaced);
    size_t finalTextStringsCount = countOfStrings * 2 - 1;
    std::string* finalTextStrings = new std::string[finalTextStringsCount];
    size_t textStringsIndex = 0;

    if (finalTextStringsCount >= 2)
    {
        finalTextStrings[0] = textStrings[textStringsIndex++];
        finalTextStrings[1] = replacement;

        for (size_t i = 2; i < finalTextStringsCount; i++)
        {
            if (i % 2 == 0)
            {
                finalTextStrings[i] = textStrings[textStringsIndex++];
            }
            else
            {
                finalTextStrings[i] = replaced;
            }
        }
    }
    //If we get here, then there is nothing to replace so we return a copy of the text param
    else
    {
        return text;
    }

    std::string finalText = concatStrings(finalTextStrings, finalTextStringsCount);

    //Delete dynamic memory
    delete[] finalTextStrings;

    return finalText;
}

std::string StringManip::replaceFrom(const std::string& text, const std::string& replacement, size_t startIndex)
{
    return replaceFrom(text, replacement, startIndex, text.size() - 1);
}

std::string StringManip::replaceFrom(const std::string& text, const std::string& replacement, size_t startIndex, size_t endIndex)
{
    if (startIndex > endIndex) throw "Start index is higher than end index loool!";
    if (startIndex > text.size() - 1) throw "Start index is higher than the length of the text";

    size_t newTextSize = text.size() - (endIndex - startIndex + 1) + replacement.size();

    std::string newText;
    for (size_t i = 0; i < startIndex; i++)
    {
        newText += text[i];
    }
    for (size_t i = 0; i < replacement.size(); i++)
    {
        newText += replacement[i];
    }
    for (size_t i = endIndex + 1; i < text.size(); i++)
    {
        newText += text[i];
    }

    return newText;
}

int StringManip::findIndex(const std::string& text, const std::string& searchText)
{
    return findIndex(text, searchText, 0, text.size() - 1);
}

int StringManip::findIndex(const std::string& text, const std::string& searchText, size_t startIndex, size_t endIndex)
{
    if (endIndex >= text.size()) throw std::out_of_range("The end index is outside the range of the text");
    if (startIndex > endIndex) return -1;
    size_t sizeOfTextPart = endIndex - startIndex + 1;

    int searchTextFoundIndex = -1;
    for (size_t i = startIndex; i <= endIndex; i++)
    {
        if (text[i] == searchText[0])
        {
            bool stringIsFound = true;
            searchTextFoundIndex = i;
            if (sizeOfTextPart - (i - startIndex) < searchText.size()) stringIsFound = false;
            else
            {
                for (size_t y = 1; y < searchText.size(); y++)
                {
                    if (i + y >= text.size() - 1 && y + 1 < searchText.size())
                    {
                        stringIsFound = false;
                        break;
                    }
                    if (text[i + y] != searchText[y])
                    {
                        stringIsFound = false;
                        break;
                    }
                }
            }

            if (stringIsFound) return searchTextFoundIndex;
            else searchTextFoundIndex = -1;
        }
    }

    //If we get to here, then the string hasn't been found
    return searchTextFoundIndex;
}

int StringManip::findIndexLast(const std::string& text, const std::string& searchText)
{
    return findIndexLast(text, searchText, 0, text.size() - 1);
}

int StringManip::findIndexLast(const std::string& text, const std::string& searchText, size_t startIndex, size_t endIndex)
{
    if (endIndex >= text.size()) throw "The end index is outside the range of the text";
    if (startIndex > endIndex) return -1;

    std::string reverseText = StringManip::getReverse(text);
    std::string reverseSearchText = StringManip::getReverse(searchText);

    int deltaFromStart = startIndex;
    int deltaFromEnd = text.size() - 1 - endIndex;
    int indexWhenReversed = findIndex(reverseText, reverseSearchText, deltaFromEnd, text.size() - 1 - deltaFromStart);
    int correctIndex = text.size() - 1 - indexWhenReversed - searchText.size() + 1;

    return indexWhenReversed > -1 ? correctIndex : -1;
}

size_t StringManip::countOf(const std::string& text, char symbol)
{
    return countOf(text, symbol, 0, text.size() - 1);
}

size_t StringManip::countOf(const std::string& text, char symbol, size_t startIndex, size_t endIndex)
{
    size_t countOfSymbol = 0;
    for (size_t i = startIndex; i <= endIndex; i++)
    {
        char textChar = text[i];
        if (textChar == symbol) countOfSymbol++;
    }
    return countOfSymbol;
}

size_t StringManip::countOf(const std::string& text, const std::string& searchText)
{
    return countOf(text, searchText, 0, text.size() - 1);
}

size_t StringManip::countOf(const std::string& text, const std::string& searchText, size_t startIndex, size_t endIndex)
{
    if (endIndex >= text.size()) throw "The end index is outside the range of the text";
    if (startIndex > endIndex) return 0;

    size_t searchTextFoundCounter = 0;
    bool searchTextHasBeenFound = false;

    for (size_t i = startIndex; i <= endIndex; i++)
    {
        if (text[i] == searchText[0])
        {
            bool stringIsFound = true;
            if (text.size() - i < searchText.size()) stringIsFound = false;
            else
            {
                for (size_t y = 1; y < searchText.size(); y++)
                {
                    if (i + y >= text.size() - 1 && y + 1 < searchText.size())
                    {
                        stringIsFound = false;
                        break;
                    }
                    if (text[i + y] != searchText[y])
                    {
                        stringIsFound = false;
                        break;
                    }
                }
            }

            if (stringIsFound)
            {
                searchTextFoundCounter++;
            }
        }
    }

    return searchTextFoundCounter;
}

size_t StringManip::countOfMany(const std::string& text, const std::string& searchText)
{
    return countOfMany(text, searchText, 0, text.size() - 1);
}

size_t StringManip::countOfMany(const std::string& text, const std::string& searchText, size_t startIndex, size_t endIndex)
{
    if (endIndex >= text.size()) throw "The end index is outside the range of the text";
    if (searchText.size() == 0) throw "The search text is empty";

    //Get the unique symbols of searchText.
    std::string uniqueSymbolsFromSearchText = getUnique(searchText);

    size_t countOfAllSymbols = 0;

    for (size_t i = 0; i < uniqueSymbolsFromSearchText.size(); i++)
    {
        char searchTextSymbol = uniqueSymbolsFromSearchText[i];
        size_t countOfSymbol = countOf(text, searchTextSymbol, startIndex, endIndex);
        countOfAllSymbols += countOfSymbol;
    }

    return countOfAllSymbols;
}

size_t StringManip::countOfMany(const std::string& text, const std::string* searchStrings, size_t searchStringsSize)
{
    return countOfMany(text, searchStrings, searchStringsSize, 0, text.size() - 1);
}

size_t StringManip::countOfMany(const std::string& text, const std::string* searchStrings, size_t searchStringsSize, size_t startIndex, size_t endIndex)
{
    if (endIndex >= text.size()) throw "The end index is outside the range of the text";

    //Get the unique string of searchStrings.
    size_t uniqueStringsCount = searchStringsSize;
    std::string* uniqueStringsFromSearchText = getUnique(searchStrings, uniqueStringsCount);

    size_t countOfAllStrings = 0;

    for (size_t i = 0; i < uniqueStringsCount; i++)
    {
        const std::string& searchString = uniqueStringsFromSearchText[i];
        size_t countOfString = countOf(text, searchString, startIndex, endIndex);
        countOfAllStrings += countOfString;
    }

    delete[] uniqueStringsFromSearchText;

    return countOfAllStrings;
}

std::string StringManip::getUnique(const std::string& text)
{
    std::string uniqueSymbols;

    size_t uniqueSymbolsIndex = 0;

    for (size_t i = 0; i < text.size(); i++)
    {
        if (!stringContains(uniqueSymbols, text[i])) uniqueSymbols += text[i];
    }
    return uniqueSymbols;
}

std::string* StringManip::getUnique(const std::string* strings, size_t& arraySize)
{
    if (arraySize == 0) throw "Array size is 0 looool";

    std::string* uniqueStrings = new std::string[arraySize];

    size_t uniqueStringsIndex = 0;

    for (size_t i = 0; i < arraySize; i++)
    {
        const std::string& stringToCompare = strings[i];

        bool stringIsUnique = true;
        for (size_t y = 0; y < uniqueStringsIndex; y++)
        {
            if (stringToCompare == uniqueStrings[y])
            {
                stringIsUnique = false;
                break;
            }
        }

        if (stringIsUnique)
        {
            //Add the new string to uniqueStrings
            uniqueStrings[uniqueStringsIndex++] = stringToCompare;
        }
    }

    //Set array size
    arraySize = uniqueStringsIndex;

    return uniqueStrings;
}

std::string StringManip::getFrom(const std::string& source, size_t startIndex, size_t endIndex)
{
    if (startIndex < 0 || startIndex > source.size() - 1 || endIndex < 0 || endIndex > source.size() - 1)
        throw std::out_of_range("The start or end indexes are out of range");

    if (startIndex > endIndex) return "";

    std::string returnString;
    for (size_t i = startIndex; i <= endIndex; i++)
    {
        returnString += source[i];
    }

    return returnString;
}

std::string StringManip::getReverse(const std::string& source)
{
    std::string reversedSource;
    for (size_t i = 0; i < source.size(); i++)
    {
        reversedSource += source[source.size() - 1 - i];
    }

    return std::string(reversedSource);
}

std::string StringManip::getFilled(const std::string& filling, size_t count)
{
    std::string filled;
    for (size_t i = 0; i < count; i++)
    {
        filled += filling;
    }

    return filled;
}

bool StringManip::arraysOfStringsAreEqual(const std::string* stringsOne, const std::string* stringsTwo, size_t stringsOneSize, size_t stringsTwoSize)
{
    if (stringsOneSize != stringsTwoSize) return false;
    for (size_t i = 0; i < stringsOneSize; i++)
    {
        if (stringsOne[i] != stringsTwo[i]) return false;
    }

    return true;
}
