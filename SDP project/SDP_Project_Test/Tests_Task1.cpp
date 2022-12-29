#include "doctest.h"
#include <iostream>
#include "../SDP_Project_Source/Task 1.h"
#include <sstream>

TEST_CASE("Test SkipList copy constructor when the list is not empty!") {

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

    REQUIRE(normalList.getSize() == copiedList.getSize());

    auto normalListNode = normalList.getHead();
    auto copiedListNode = copiedList.getHead();

    while (normalListNode)
    {
        REQUIRE(normalListNode != copiedListNode);
        REQUIRE(normalListNode->key == copiedListNode->key);

        normalListNode = normalListNode->next;
        copiedListNode = copiedListNode->next;
    }

    REQUIRE(normalList.toString() == copiedList.toString());
}

TEST_CASE("Test task1 with default test")
{
    //9
    //Sofia Pazardzhik Plovdiv Dimitrovgrad StaraZagora NovaZagora Yambol Karnobat Burgas
    //Sofia Plovdiv
    //Plovdiv NovaZagora
    //Dimitrovgrad NovaZagora
    //StaraZagora Yambol
    //NovaZagora Burgas
    //Stop
    //Plovdiv StaraZagora Yambol
    std::string input = "9\nSofia Pazardzhik Plovdiv Dimitrovgrad StaraZagora NovaZagora Yambol Karnobat Burgas\n";
    input += "Sofia Plovdiv\nPlovdiv NovaZagora\nDimitrovgrad NovaZagora\nStaraZagora Yambol\nNovaZagora Burgas\nStop\nPlovdiv StaraZagora Yambol";

    std::istringstream inputStream(input);
    std::ostringstream outputStream;

    task1(outputStream, inputStream);

    std::string expectedOutput = "The shortest path that visits each of the necessary cities is: ";
    expectedOutput += "Sofia --> Plovdiv --> Dimitrovgrad --> StaraZagora --> Yambol --> Karnobat --> Burgas\n";

    std::string actualOutput = outputStream.str();

    REQUIRE(expectedOutput == actualOutput);
}

TEST_CASE("Test task1, where there are backwards direct connections and there is also a backwards direct connection from the end city, but no backtracking is needed for the fastest path")
{
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

    std::string input = "9\nSofia Pazardzhik Plovdiv Dimitrovgrad StaraZagora NovaZagora Yambol Karnobat Burgas\n";
    input += "Sofia Plovdiv\nPlovdiv NovaZagora\nDimitrovgrad NovaZagora\nStaraZagora Yambol\nNovaZagora Burgas\n";
    input += "NovaZagora Burgas\nKarnobat Sofia\nYambol StaraZagora\nPazardzhik Yambol\nBurgas Plovdiv\nStop\nPlovdiv StaraZagora Yambol";

    std::istringstream inputStream(input);
    std::ostringstream outputStream;

    task1(outputStream, inputStream);

    std::string expectedOutput = "The shortest path that visits each of the necessary cities is: ";
    expectedOutput += "Sofia --> Plovdiv --> Dimitrovgrad --> StaraZagora --> Yambol --> Karnobat --> Burgas\n";

    std::string actualOutput = outputStream.str();

    REQUIRE(expectedOutput == actualOutput);
}

TEST_CASE("Test task1 with many cyclical paths, but no backtracking is needed for the fastest path")
{
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

    std::string input = "9\nSofia Pazardzhik Plovdiv Dimitrovgrad StaraZagora NovaZagora Yambol Karnobat Burgas\n";
    input += "Sofia Plovdiv\nPlovdiv Burgas\nDimitrovgrad NovaZagora\nStaraZagora Yambol\nNovaZagora Burgas\n";
    input += "Karnobat Sofia\nYambol StaraZagora\nPazardzhik Sofia\nBurgas Plovdiv\nStop\nPlovdiv";

    std::istringstream inputStream(input);
    std::ostringstream outputStream;

    task1(outputStream, inputStream);

    std::string expectedOutput = "The shortest path that visits each of the necessary cities is: ";
    expectedOutput += "Sofia --> Plovdiv --> Burgas\n";

    std::string actualOutput = outputStream.str();

    REQUIRE(expectedOutput == actualOutput);
}

TEST_CASE("Test task1 without any special paths")
{
    //9
    //Sofia Pazardzhik Plovdiv Dimitrovgrad StaraZagora NovaZagora Yambol Karnobat Burgas
    //Stop
    //Plovdiv StaraZagora Yambol

    std::string input = "9\nSofia Pazardzhik Plovdiv Dimitrovgrad StaraZagora NovaZagora Yambol Karnobat Burgas\n";
    input += "Stop\nPlovdiv StaraZagora Yambol";

    std::istringstream inputStream(input);
    std::ostringstream outputStream;

    task1(outputStream, inputStream);

    std::string expectedOutput = "The shortest path that visits each of the necessary cities is: ";
    expectedOutput += "Sofia --> Pazardzhik --> Plovdiv --> Dimitrovgrad --> StaraZagora --> NovaZagora --> Yambol --> Karnobat --> Burgas\n";

    std::string actualOutput = outputStream.str();

    REQUIRE(expectedOutput == actualOutput);
}

TEST_CASE("Test task1, where the shortest path involves backtracking")
{
    //9
    //Sofia Pazardzhik Plovdiv Dimitrovgrad StaraZagora NovaZagora Yambol Karnobat Burgas
    //Pazardzhik Burgas
    //Plovdiv Pazardzhik
    //Stop
    //Plovdiv

    std::string input = "9\nSofia Pazardzhik Plovdiv Dimitrovgrad StaraZagora NovaZagora Yambol Karnobat Burgas\n";
    input += "Pazardzhik Burgas\nPlovdiv Pazardzhik\nStop\nPlovdiv";

    std::istringstream inputStream(input);
    std::ostringstream outputStream;

    task1(outputStream, inputStream);

    std::string expectedOutput = "The shortest path that visits each of the necessary cities is: ";
    expectedOutput += "Sofia --> Pazardzhik --> Plovdiv --> Pazardzhik --> Burgas\n";

    std::string actualOutput = outputStream.str();

    REQUIRE(expectedOutput == actualOutput);
}

TEST_CASE("Test task1, where the shortest path involves backtracking from the end city so we can skip forward to the end faster after reaching the required cities")
{
    //9
    //Sofia Pazardzhik Plovdiv Dimitrovgrad StaraZagora NovaZagora Yambol Karnobat Burgas
    //Pazardzhik Burgas
    //Burgas NovaZagora
    //NovaZagora Pazardzhik
    //Stop
    //NovaZagora

    std::string input = "9\nSofia Pazardzhik Plovdiv Dimitrovgrad StaraZagora NovaZagora Yambol Karnobat Burgas\n";
    input += "Pazardzhik Burgas\nBurgas NovaZagora\nNovaZagora Pazardzhik\nStop\nNovaZagora";

    std::istringstream inputStream(input);
    std::ostringstream outputStream;

    task1(outputStream, inputStream);

    std::string expectedOutput = "The shortest path that visits each of the necessary cities is: ";
    expectedOutput += "Sofia --> Pazardzhik --> Burgas --> NovaZagora --> Pazardzhik --> Burgas\n";

    std::string actualOutput = outputStream.str();

    REQUIRE(expectedOutput == actualOutput);
}