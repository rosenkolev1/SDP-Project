#pragma once
#include <string>
#include <unordered_map>

class TestCasesUtil
{
	typedef const char* (*getTestCaseStringTemplate)(int);

private:
	static const char* getTestCaseString2(int i)
	{
		std::string testCase1 = "Testing task 3 with default test case";

		std::string testCase2 = std::string("Testing task 3 where there are many nested drawingsBoxes and souvenirsBoxes)") +
			"until a final box with only a single souvenir and the topmost bag contains a single souvenir and nested empty bags!";

		std::string testCase3 = std::string("Testing task 3 where there are many nested drawingsBoxes and souvenirsBoxes)") +
			"until a final box with only a single souvenir and the topmost bag contains a single souvenir and " +
			"one nested bag which contains a single souvenir and empty nested bags";

		std::string testCase4 = std::string("Testing task 3 where there are many nested drawingsBoxes and souvenirsBoxes)") +
			"until a final box with only a single souvenir and the topmost bag contains a single souvenir and " +
			"a nested bag which contains a nested bag with a single souvenir and an empty nested bag";

		std::string testCase5 = std::string("Testing task 3 where there are many nested drawingsBoxes and souvenirsBoxes)") +
			"until a final box with only a single souvenir and the topmost bag contains a single souvenir and " +
			"a nested bag which contains a single souvenir and a nested bag with a single souvenir and an empty nested bag";

		std::string testCase6 = std::string("Testing task 3 where there are many nested drawingsBoxes and souvenirsBoxes)") +
			"until a final box with only a single souvenir and the topmost bag contains a single bag and " +
			"that bag contains a single souvenir and a nested empty bag";

		std::string testCase7 = std::string("Testing task 3 where there are many nested drawingsBoxes and souvenirsBoxes)") +
			"until a final box with only a single souvenir and the topmost bag contains a single bag and " +
			"that bag contains a nested bag which contains a single souvenir and an empty nested bag";

		std::string testCase8 = std::string("Testing task 3 where there are many nested drawingsBoxes and souvenirsBoxes)") +
			"until a final box with only a single souvenir and the topmost bag contains a single bag and " +
			"that bag contains a single souvenir a nested bag which contains a single souvenir and an empty nested bag";

		std::string testCase9 = std::string("Testing task 3 where there are many nested drawingsBoxes and souvenirsBoxes)") +
			"until a final box with only a single souvenir and the topmost bag has no souvenirs and contains an empty nested bag";

		std::string testCase10 = std::string("Testing task 3 where there are many nested drawingsBoxes and the theatreBox)") +
			"contains only the theatreSouvenirs box which contains 3 boxes which are all nested empty boxes";

		std::string testCase11 = std::string("Testing task 3 where PlovdivBox contains a single souvenir and ") +
			"many nested empty boxes";

		std::string testCase12 = std::string("Testing task 3 where PlovdivBox contains only nested empty boxes");

		std::string testCases[] = {
			testCase1,
			testCase2,
			testCase3,
			testCase4,
			testCase5,
			testCase6,
			testCase7,
			testCase8,
			testCase9,
			testCase10,
			testCase11,
			testCase12
		};

		return testCases[i - 1].c_str();
	}

	static const char* getTestCaseString1(int i)
	{
		std::string testCase1 = "Testing task 3 with default test case";

		std::string testCase2 = std::string("Testing task 3 where there are many nested drawingsBoxes and souvenirsBoxes)") +
			"until a final box with only a single souvenir and the topmost bag contains a single souvenir and nested empty bags!";

		std::string testCase3 = std::string("Testing task 3 where there are many nested drawingsBoxes and souvenirsBoxes)") +
			"until a final box with only a single souvenir and the topmost bag contains a single souvenir and " +
			"one nested bag which contains a single souvenir and empty nested bags";

		std::string testCase4 = std::string("Testing task 3 where there are many nested drawingsBoxes and souvenirsBoxes)") +
			"until a final box with only a single souvenir and the topmost bag contains a single souvenir and " +
			"a nested bag which contains a nested bag with a single souvenir and an empty nested bag";

		std::string testCase5 = std::string("Testing task 3 where there are many nested drawingsBoxes and souvenirsBoxes)") +
			"until a final box with only a single souvenir and the topmost bag contains a single souvenir and " +
			"a nested bag which contains a single souvenir and a nested bag with a single souvenir and an empty nested bag";

		std::string testCase6 = std::string("Testing task 3 where there are many nested drawingsBoxes and souvenirsBoxes)") +
			"until a final box with only a single souvenir and the topmost bag contains a single bag and " +
			"that bag contains a single souvenir and a nested empty bag";

		std::string testCase7 = std::string("Testing task 3 where there are many nested drawingsBoxes and souvenirsBoxes)") +
			"until a final box with only a single souvenir and the topmost bag contains a single bag and " +
			"that bag contains a nested bag which contains a single souvenir and an empty nested bag";

		std::string testCase8 = std::string("Testing task 3 where there are many nested drawingsBoxes and souvenirsBoxes)") +
			"until a final box with only a single souvenir and the topmost bag contains a single bag and " +
			"that bag contains a single souvenir a nested bag which contains a single souvenir and an empty nested bag";

		std::string testCase9 = std::string("Testing task 3 where there are many nested drawingsBoxes and souvenirsBoxes)") +
			"until a final box with only a single souvenir and the topmost bag has no souvenirs and contains an empty nested bag";

		std::string testCase10 = std::string("Testing task 3 where there are many nested drawingsBoxes and the theatreBox)") +
			"contains only the theatreSouvenirs box which contains 3 boxes which are all nested empty boxes";

		std::string testCase11 = std::string("Testing task 3 where PlovdivBox contains a single souvenir and ") +
			"many nested empty boxes";

		std::string testCase12 = std::string("Testing task 3 where PlovdivBox contains only nested empty boxes");

		std::string testCases[] = {
			testCase1,
			testCase2,
			testCase3,
			testCase4,
			testCase5,
			testCase6,
			testCase7,
			testCase8,
			testCase9,
			testCase10,
			testCase11,
			testCase12
		};

		return testCases[i - 1].c_str();
	}
public:

	static const std::string TESTS_TASK3;
	static const std::string TESTS_BOX;

	static const std::unordered_map<std::string, getTestCaseStringTemplate> testCasesStrings;
};
