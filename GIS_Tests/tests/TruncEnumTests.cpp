#include "pch.h"
#include "TruncEnum.h"
#include "GraphParser.h"

TEST(TruncEnum, IsomorphicGraphs) {
    GIS_Data::Graph graph1 = GIS_Parser::Graph::Parse("../../GIS_Tests/Graph_Data/IsoGraph1_1.graph");
    GIS_Data::Graph graph2 = GIS_Parser::Graph::Parse("../../GIS_Tests/Graph_Data/IsoGraph1_2.graph");
    bool result = GIS_Algs::TruncEnum::Start(graph1, graph2);
    EXPECT_EQ(result, true);
}

TEST(TruncEnum, NotIsomorphicGraphs) {
    GIS_Data::Graph graph1 = GIS_Parser::Graph::Parse("../../GIS_Tests/Graph_Data/IsoGraph1_1.graph");
    GIS_Data::Graph graph2 = GIS_Parser::Graph::Parse("../../GIS_Tests/Graph_Data/NotIsoGraph1.graph");
    bool result = GIS_Algs::TruncEnum::Start(graph1, graph2);
    EXPECT_EQ(result, false);
}
