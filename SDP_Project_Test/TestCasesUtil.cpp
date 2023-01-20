#include "TestCasesUtil.h"

const std::string TestCasesUtil::TESTS_TASK3 = "Tests_Task3";
const std::string TestCasesUtil::TESTS_BOX = "Tests_Box";

const std::unordered_map<std::string, TestCasesUtil::getTestCaseStringTemplate> TestCasesUtil::testCasesStrings =
{
	{TestCasesUtil::TESTS_TASK3, [](int i) -> const char* { return TestCasesUtil::getTestCaseString1(i); }},
	{TestCasesUtil::TESTS_BOX, [](int i) -> const char* { return TestCasesUtil::getTestCaseString2(i); }},
};