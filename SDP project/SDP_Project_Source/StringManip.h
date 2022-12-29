#pragma once

#include <string>
#include <vector>

class StringManip
{
public:
	static std::vector<std::string> parseIntoVector(std::string* arr, size_t size);
	
	///Parse an int to string
	static std::string parseToString(int integer);

	///Parse an size_t to string
	static std::string parseToString(size_t integer);

	///Parse a string to long
	static long parseToLong(std::string text);

	///Split string by char delim. sizeOfArray returns the numbers of split strings. 
	static std::vector<std::string> splitString(const std::string& input, char delim);

	///Split string by string delim. sizeOfArray returns the numbers of split strings. 
	static std::vector<std::string> splitString(const std::string& input, const std::string& delim);

	///Split string by many char delims. sizeOfArray returns the numbers of split strings. 
	static std::string* splitStringMany(const std::string& input, const std::string& delims, size_t& sizeOfArray);

	///Split string by many string delims. sizeOfArray returns the numbers of split strings. 
	static std::string* splitStringMany(const std::string& input, const std::string* delims, size_t sizeOfDelimsArrays, size_t& sizeOfArray);

	///Checks if the text contains any of the invalid chars
	static bool stringContainsInvalidChars(const std::string& text, const std::string& invalidChars);

	///Checks if the text contains the given char
	static bool stringContains(const std::string& text, const char other);

	///Checks if the text contains the given string
	static bool stringContains(const std::string& text, const std::string& other);

	///Checks if the text starts with the given string
	static bool stringStartsWith(const std::string& text, const std::string& other);

	///Checks if the text ends with the given string
	static bool stringEndsWith(const std::string& text, const std::string& other);

	///Concatenates strings from a char of strings
	static std::string concatStrings(const std::string* strings, size_t stringsCount);

	///Replaces all instances of the replaced string in the text with the replacement string
	static std::string replaceAll(const std::string& text, const std::string& replaced, const std::string& replacement);

	///Replaces the first instance of the replaced string in the text with the replacement string
	static std::string replaceFirst(const std::string& text, const std::string& replaced, const std::string& replacement);

	///Replaces a part of the string, starting from startIndex, inclusive, with the replacement.
	static std::string replaceFrom(const std::string& text, const std::string& replacement, size_t startIndex);

	///Replaces a part of the string, starting from startIndex and ending in endIndex, both inclusive, with the replacement.
	static std::string replaceFrom(const std::string& text, const std::string& replacement, size_t startIndex, size_t endIndex);

	///Returns the index of the first occurance of searchText in text. Returns -1 if searchText isn't found inside text
	static int findIndex(const std::string& text, const std::string& searchText);

	///Returns the index of the first occurance of searchText in text, starting from startIndex and ending in endIndex, both inclusive. Returns -1 if searchText isn't found inside text
	static int findIndex(const std::string& text, const std::string& searchText, size_t startIndex, size_t endIndex);

	///Returns the index of the last occurance of searchText in text. Returns -1 if searchText isn't found inside text
	static int findIndexLast(const std::string& text, const std::string& searchText);

	///Returns the index of the last occurance of searchText in text, starting from startIndex and ending in endIndex, both inclusive. Returns -1 if searchText isn't found inside text
	static int findIndexLast(const std::string& text, const std::string& searchText, size_t startIndex, size_t endIndex);

	///Returns the count of symbol in text
	static size_t countOf(const std::string& text, char symbol);

	///Returns the count of symbol in text, starting from startIndex and ending in endIndex, both inclusive
	static size_t countOf(const std::string& text, char symbol, size_t startIndex, size_t endIndex);

	///Returns the count of searchText in text
	static size_t countOf(const std::string& text, const std::string& searchText);

	///Returns the count of searchText in text, starting from startIndex and ending in endIndex, both inclusive
	static size_t countOf(const std::string& text, const std::string& searchText, size_t startIndex, size_t endIndex);

	///Returns the count of all the symbols of searchText in text. For repeating symbols, only counts the symbol one time
	static size_t countOfMany(const std::string& text, const std::string& searchText);

	///Returns the count of all the symbols of searchText in text, starting from startIndex and ending in endIndex, both inclusive. For repeating symbols, only counts the symbol one time
	static size_t countOfMany(const std::string& text, const std::string& searchText, size_t startIndex, size_t endIndex);

	///Returns the count of all the string of searchStrings in text. For repeating strings, only counts the string one time
	static size_t countOfMany(const std::string& text, const std::string* searchStrings, size_t searchStringsSize);

	///Returns the count of all the string of searchStrings in text, starting from startIndex and ending in endIndex, both inclusive. For repeating strings, only counts the string one time
	static size_t countOfMany(const std::string& text, const std::string* searchStrings, size_t searchStringsSize, size_t startIndex, size_t endIndex);

	///Returns an array of chars where each char from text is unique, i.e. doesn't appear again.
	static std::string getUnique(const std::string& text);

	///Returns an array of strings where each string from strings is unique, i.e. doesn't appear again.
	static std::string* getUnique(const std::string* strings, size_t& arraySize);

	///Get the part of the source that start from startIndex and ends on endIndex, both inclusive. Return nullptr if the startIndex is > endIndex
	static std::string getFrom(const std::string& source, size_t startIndex, size_t endIndex);

	///Get the reverse of the source
	static std::string getReverse(const std::string& source);

	///Gets a string that is one character repeatedly concatted many times. Ex: ******
	static std::string getFilled(const std::string& filling, size_t count);

	///Compares 2 arrays of strings and says whether or not they are the same
	static bool arraysOfStringsAreEqual(const std::string* stringsOne, const std::string* stringsTwo, size_t stringsOneSize, size_t stringsTwoSize);
};


