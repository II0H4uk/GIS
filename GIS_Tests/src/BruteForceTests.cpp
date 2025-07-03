#include "pch.h"
#include "BruteForce.h"
#include "GraphParser.h"

TEST(BruteForce, IsomorphicGraphs) {
    GIS_Data::Graph graph1 = GIS_Parser::Graph::Parse("../../GIS_Tests/Graph_Data/IsoGraph1_1.graph");
    GIS_Data::Graph graph2 = GIS_Parser::Graph::Parse("../../GIS_Tests/Graph_Data/IsoGraph1_2.graph");
    bool result = GIS_Algs::BruteForce::Start(graph1,graph2);
    EXPECT_EQ(result, true);
}

TEST(BruteForce, NotIsomorphicGraphs) {
    GIS_Data::Graph graph1 = GIS_Parser::Graph::Parse("../../GIS_Tests/Graph_Data/IsoGraph1_1.graph");
    GIS_Data::Graph graph2 = GIS_Parser::Graph::Parse("../../GIS_Tests/Graph_Data/NotIsoGraph1.graph");
    bool result = GIS_Algs::BruteForce::Start(graph1,graph2);
    EXPECT_EQ(result, false);
}
