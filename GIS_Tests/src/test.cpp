#include "pch.h"
#include "BruteForce.h"
#include "GraphParser.h"
TEST(TestCaseName, TestName) {
    EXPECT_EQ(1, 1);
}
TEST(BruteForce, Test1) {
    GIS_Data::Graph graph1 = GIS_Parser::Graph::Parse("../Graph_Data/inputGraph1.graph");
    GIS_Data::Graph graph2 = GIS_Parser::Graph::Parse("../Graph_Data/inputGraph2.graph");
    bool result = GIS_Algs::BruteForce::Start(graph1,graph2);
    EXPECT_EQ(result, true);
}
TEST(BruteForce, Test2) {
    GIS_Data::Graph graph1 = GIS_Parser::Graph::Parse("../Graph_Data/inputGraph1.graph");
    GIS_Data::Graph graph2 = GIS_Parser::Graph::Parse("../Graph_Data/inputGraph.graph");
    bool result = GIS_Algs::BruteForce::Start(graph1,graph2);
    EXPECT_EQ(result, false);
}
