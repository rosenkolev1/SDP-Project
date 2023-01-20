#include "doctest.h"
#include "../SDP_Project_Source/UndirectedGraph.h"

TEST_CASE("Test adding edges to graph") 
{
    auto graph = UndirectedGraph<std::string>();
    graph.addEdge("Railstation", "RomanStadium", 20);
    graph.addEdge("Railstation", "ArtGallery", 26);
    graph.addEdge("RomanStadium", "DzhumayaSquare", 2);
    graph.addEdge("ArtGallery", "DzhumayaSquare", 5);
    graph.addEdge("ArtGallery", "AntiqueTheatre", 7);
    graph.addEdge("ArtGallery", "HistoricalMuseum", 14);
    graph.addEdge("DzhumayaSquare", "HistoricalMuseum", 18);
    graph.addEdge("HistoricalMuseum", "AntiqueTheatre", 12);

    CHECK_EQ(graph.getVertexesCount(), 6);
    
    auto vertexEdgesExpected = std::map<std::string, std::vector<GraphEdge<std::string>> >();

    vertexEdgesExpected["Railstation"] = std::vector<GraphEdge<std::string>> {
        GraphEdge<std::string>("Railstation", "RomanStadium", 20),
        GraphEdge<std::string>("Railstation", "ArtGallery", 26),
    };
    vertexEdgesExpected["RomanStadium"] = std::vector<GraphEdge<std::string>>{
        GraphEdge<std::string>("Railstation", "RomanStadium", 20),
        GraphEdge<std::string>("RomanStadium", "DzhumayaSquare", 2),
    };
    vertexEdgesExpected["ArtGallery"] = std::vector<GraphEdge<std::string>>{
        GraphEdge<std::string>("Railstation", "ArtGallery", 26),
        GraphEdge<std::string>("ArtGallery", "DzhumayaSquare", 5),
        GraphEdge<std::string>("ArtGallery", "AntiqueTheatre", 7),
        GraphEdge<std::string>("ArtGallery", "HistoricalMuseum", 14),
    };
    vertexEdgesExpected["DzhumayaSquare"] = std::vector<GraphEdge<std::string>>{
        GraphEdge<std::string>("RomanStadium", "DzhumayaSquare", 2),
        GraphEdge<std::string>("ArtGallery", "DzhumayaSquare", 5),
        GraphEdge<std::string>("DzhumayaSquare", "HistoricalMuseum", 18),
    };
    vertexEdgesExpected["HistoricalMuseum"] = std::vector<GraphEdge<std::string>>{ 
        GraphEdge<std::string>("ArtGallery", "HistoricalMuseum", 14),
        GraphEdge<std::string>("DzhumayaSquare", "HistoricalMuseum", 18),
        GraphEdge<std::string>("HistoricalMuseum", "AntiqueTheatre", 12),
    };
    vertexEdgesExpected["AntiqueTheatre"] = std::vector<GraphEdge<std::string>>{
        GraphEdge<std::string>("ArtGallery", "AntiqueTheatre", 7),
        GraphEdge<std::string>("HistoricalMuseum", "AntiqueTheatre", 12),
    };

    auto vertexEdgesActual = graph.getVertexEdges();

    for (auto kvPair : vertexEdgesActual) {
        auto actualEdges = kvPair.second;
        auto expectedEdges = vertexEdgesExpected[kvPair.first];

        CHECK_EQ(actualEdges.size(), expectedEdges.size());

        for (int i = 0; i < actualEdges.size(); i++) {
            CHECK(actualEdges[i].edgesAreEqual(expectedEdges[i]));
        }
    }
}

TEST_CASE("Test adding edges to graph with repeat")
{
    auto graph = UndirectedGraph<std::string>();
    graph.addEdge("Railstation", "RomanStadium", 20);
    graph.addEdge("Railstation", "ArtGallery", 26);
    graph.addEdge("RomanStadium", "DzhumayaSquare", 2);
    graph.addEdge("ArtGallery", "DzhumayaSquare", 5);
    graph.addEdge("ArtGallery", "AntiqueTheatre", 7);
    graph.addEdge("ArtGallery", "HistoricalMuseum", 14);
    graph.addEdge("DzhumayaSquare", "HistoricalMuseum", 18);
    graph.addEdge("HistoricalMuseum", "AntiqueTheatre", 12);

    //Repeating
    graph.addEdge("DzhumayaSquare", "HistoricalMuseum", 9);
    graph.addEdge("RomanStadium", "DzhumayaSquare", 46);

    CHECK_EQ(graph.getVertexesCount(), 6);

    auto vertexEdgesExpected = std::map<std::string, std::vector<GraphEdge<std::string>> >();

    vertexEdgesExpected["Railstation"] = std::vector<GraphEdge<std::string>>{
        GraphEdge<std::string>("Railstation", "RomanStadium", 20),
        GraphEdge<std::string>("Railstation", "ArtGallery", 26),
    };
    vertexEdgesExpected["RomanStadium"] = std::vector<GraphEdge<std::string>>{
        GraphEdge<std::string>("Railstation", "RomanStadium", 20),
        GraphEdge<std::string>("RomanStadium", "DzhumayaSquare", 2),
    };
    vertexEdgesExpected["ArtGallery"] = std::vector<GraphEdge<std::string>>{
        GraphEdge<std::string>("Railstation", "ArtGallery", 26),
        GraphEdge<std::string>("ArtGallery", "DzhumayaSquare", 5),
        GraphEdge<std::string>("ArtGallery", "AntiqueTheatre", 7),
        GraphEdge<std::string>("ArtGallery", "HistoricalMuseum", 14),
    };
    vertexEdgesExpected["DzhumayaSquare"] = std::vector<GraphEdge<std::string>>{
        GraphEdge<std::string>("RomanStadium", "DzhumayaSquare", 2),
        GraphEdge<std::string>("ArtGallery", "DzhumayaSquare", 5),
        GraphEdge<std::string>("DzhumayaSquare", "HistoricalMuseum", 18),
    };
    vertexEdgesExpected["HistoricalMuseum"] = std::vector<GraphEdge<std::string>>{
        GraphEdge<std::string>("ArtGallery", "HistoricalMuseum", 14),
        GraphEdge<std::string>("DzhumayaSquare", "HistoricalMuseum", 18),
        GraphEdge<std::string>("HistoricalMuseum", "AntiqueTheatre", 12),
    };
    vertexEdgesExpected["AntiqueTheatre"] = std::vector<GraphEdge<std::string>>{
        GraphEdge<std::string>("ArtGallery", "AntiqueTheatre", 7),
        GraphEdge<std::string>("HistoricalMuseum", "AntiqueTheatre", 12),
    };

    auto vertexEdgesActual = graph.getVertexEdges();

    for (auto kvPair : vertexEdgesActual) {
        auto actualEdges = kvPair.second;
        auto expectedEdges = vertexEdgesExpected[kvPair.first];

        CHECK_EQ(actualEdges.size(), expectedEdges.size());

        for (int i = 0; i < actualEdges.size(); i++) {
            CHECK(actualEdges[i].edgesAreEqual(expectedEdges[i]));
        }
    }
}

TEST_CASE("Test copy constructor") 
{
    auto graph = UndirectedGraph<std::string>();
    graph.addEdge("Railstation", "RomanStadium", 20);
    graph.addEdge("Railstation", "ArtGallery", 26);
    graph.addEdge("RomanStadium", "DzhumayaSquare", 2);
    graph.addEdge("ArtGallery", "DzhumayaSquare", 5);
    graph.addEdge("ArtGallery", "AntiqueTheatre", 7);
    graph.addEdge("ArtGallery", "HistoricalMuseum", 14);
    graph.addEdge("DzhumayaSquare", "HistoricalMuseum", 18);
    graph.addEdge("HistoricalMuseum", "AntiqueTheatre", 12);

    //Repeating
    graph.addEdge("DzhumayaSquare", "HistoricalMuseum", 9);
    graph.addEdge("RomanStadium", "DzhumayaSquare", 46);

    auto secondGraph = graph;

    CHECK_EQ(graph.getVertexesCount(), secondGraph.getVertexesCount());

    auto vertexEdgesFirst = graph.getVertexEdges();
    auto vertexEdgesSecond = secondGraph.getVertexEdges();

    for (auto kvPair : vertexEdgesFirst) {
        auto firstEdges = kvPair.second;
        auto secondEdges = vertexEdgesSecond[kvPair.first];

        CHECK_EQ(firstEdges.size(), secondEdges.size());

        for (int i = 0; i < firstEdges.size(); i++) {
            CHECK(firstEdges[i].edgesAreEqual(secondEdges[i]));
        }
    }
}